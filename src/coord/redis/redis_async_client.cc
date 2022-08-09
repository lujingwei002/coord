#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_reply.h"
#include "coord/redis/redis_promise.h"
#include "coord/builtin/slice.h"
#include "coord/redis/redis_mgr.h"
#include "coord/coord.h"
#include <hiredis/adapters/libuv.h>

namespace coord {
namespace redis {

CC_IMPLEMENT(AsyncClient, "coord::redis::AsyncClient")

enum redis_client_status {
    redis_client_status_nil = 0,
    redis_client_status_connected = 1,
    redis_client_status_connecting = 2,
    redis_client_status_error = 3,
    redis_client_status_closing = 4,
    redis_client_status_closed = 5,
};

void AsyncClient::connectCallback(const redisAsyncContext* c, int status) {
    AsyncClient* client = (AsyncClient*)c->data;
    if (status != REDIS_OK) {
        client->recvConnectError(c->errstr);
        return;
    }
    client->recvConnect();
}

void AsyncClient::disconnectCallback(const redisAsyncContext* c, int status) {
    AsyncClient* client = (AsyncClient*)c->data;
    if (status != REDIS_OK) {
        client->recvDisconnectError(c->errstr);
        return;
    }
    client->recvDisconnect();
}

void AsyncClient::getCallback(redisAsyncContext *c, void *data, void *privdata) {
    AsyncClient* client = (AsyncClient*)c->data;
    RedisPromise* promise = (RedisPromise*)privdata;
    redisReply* r = (redisReply*)data;

    Reply* reply = new Reply(client->coord, r);
    client->recvGetCallback(promise, reply);
}

AsyncClient::AsyncClient(Coord *coord, RedisMgr* redisMgr) {
    this->coord = coord;
    this->status = redis_client_status_nil;
    this->connectPromise = nullptr;
    this->redisMgr = redisMgr;
}   

AsyncClient::~AsyncClient() {
    if(this->context) {
        redisAsyncFree(this->context);
        this->context = nullptr;
    }
    if(this->connectPromise != nullptr) {
        this->connectPromise->reject(this, nullptr);
        delete this->connectPromise;
        this->connectPromise = nullptr;
    }
    auto it = this->promiseDict.begin();
    for(; it != this->promiseDict.end(); ){
        delete it->second;
        this->promiseDict.erase(it++);
    }
    this->promiseDict.clear();
    this->redisMgr->free(this);
}

RedisConfig* AsyncClient::DefaultConfig() {
    return &this->config;
}

void AsyncClient::Close() {
    if(!this->context) {
        return;
    }
    if(this->status == redis_client_status_closing || this->status == redis_client_status_closed) {
        return;
    }
    this->status = redis_client_status_closing;
    redisAsyncDisconnect(this->context);
}

void AsyncClient::recvConnectError(const char* error) {
    this->coord->CoreLogError("[RedisAsyncClient] recvConnectError, error='%s'", error);
    this->status = redis_client_status_error;
    this->connectPromise->reject(this, nullptr);
    delete this->connectPromise;
    this->connectPromise = nullptr;
}

void AsyncClient::resolveConnect() {
    this->status = redis_client_status_connected;
    this->connectPromise->resolve(this, nullptr);
    delete this->connectPromise;
    this->connectPromise = nullptr;
    return;
}

void AsyncClient::rejectConnect() {
    this->status = redis_client_status_error;
    this->connectPromise->reject(this, nullptr);
    delete this->connectPromise;
    this->connectPromise = nullptr;
    this->Close();
}

void AsyncClient::recvConnect() {
    this->coord->CoreLogDebug("[RedisAsyncClient] recvConnect");
    if (this->config.Password.length() <= 0) {
        this->resolveConnect();
        return;
    }
    //验证密码, 当前状态为连接中
    RedisPromise* promise = this->auth(this->config.Password.c_str());
    if (promise == NULL){
        this->rejectConnect();
        return;
    }
    promise->Then([this](auto client, auto reply){
        this->coord->CoreLogDebug("[RedisAsyncClient] authResolve");
        //密码验证成功
        if (this->config.DB.length() <= 0) {
            this->resolveConnect();
            return;
        }
        RedisPromise* promise = this->select(this->config.DB.c_str());
        if (promise == NULL){
            this->rejectConnect();
            return;
        }  
        promise->Then([this](auto client, auto reply){
            this->resolveConnect();
            return;
        });        
        promise->Else([this](auto client, auto reply){
            this->coord->CoreLogDebug("[RedisAsyncClient] recvConnect failed, error='SELECT'");
            //密码验证失败，断开链接
            this->rejectConnect();
        });
    });
    promise->Else([this](auto client, auto reply){
        this->coord->CoreLogDebug("[RedisAsyncClient] recvConnect failed, error='AUTH'");
        //密码验证失败，断开链接
        this->rejectConnect();
    });
}

void AsyncClient::recvGetCallback(RedisPromise* promise, Reply* reply) {
    if (reply->Error()) {
        promise->reject(this, reply);
    } else {
        promise->resolve(this, reply);
    }
    this->promiseDict.erase(promise);
    this->coord->Destory(promise);
    this->coord->Destory((Reply* )reply);
}

void AsyncClient::recvDisconnectError(const char* error) {
    this->coord->CoreLogError("[RedisAsyncClient] recvDisconnectError, error='%s'", error);
    this->status = redis_client_status_error;
}

void AsyncClient::recvDisconnect() {
    this->coord->CoreLogWarn("[RedisAsyncClient] recvDisconnect");
    this->status = redis_client_status_error;
}

RedisPromise* AsyncClient::Connect() {
    if(this->status != redis_client_status_nil) {
        return nullptr;
    }
    redisAsyncContext* c = redisAsyncConnect(this->config.Host.c_str(), this->config.Port);
    if(c == nullptr) {
        this->coord->CoreLogError("[RedisAsyncClient] connect failed, error='out of memory'");
        return nullptr;
    }
    if (c->err) {
        redisAsyncFree(c);
        this->coord->CoreLogError("[RedisAsyncClient] Connect failed, error=%s", c->errstr);
        return nullptr;
    }
    c->data = this;
    this->status = redis_client_status_connecting;
    RedisPromise* promise = new RedisPromise(this->coord);
    redisLibuvAttach(c, &this->coord->loop);
    redisAsyncSetConnectCallback(c, AsyncClient::connectCallback);
    redisAsyncSetDisconnectCallback(c, AsyncClient::disconnectCallback);
    this->context = c;
    this->connectPromise = promise;
    return promise;
}

RedisPromise * AsyncClient::select(const char* db) {
    if(this->status != redis_client_status_connecting) {
        return nullptr;
    }
    RedisPromise* promise = new RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "SELECT %s", db);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] SELECT failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::SELECT(const char* db) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "SELECT %s", db);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] SELECT failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise * AsyncClient::auth(const char* password) {
    if(this->status != redis_client_status_connecting) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "AUTH %s", password);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] AUTH failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise * AsyncClient::AUTH(const char* password) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "AUTH %s", password);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] AUTH failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::EXPIRE(const char* key, uint64_t expire) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "EXPIRE %s %ld", key, expire);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::GET(const char* key) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "GET %s", key);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::SCRIPT_LOAD(const char* str) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "SCRIPT LOAD %s", str);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, command=%s, error='%s'", str, this->context->errstr);
        this->coord->Destory(promise);
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::EVALSHA(const char* sha1, const char* format, ...) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    static thread_local byte_slice buffer;
    buffer.Reserve(10 + strlen(sha1) + strlen(format));
    sprintf(buffer.Data(), "EVALSHA %s %s",  sha1, format);
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    va_list args;
    va_start(args, format);
    int err = redisvAsyncCommand(this->context, AsyncClient::getCallback, promise, buffer.Data(), args);
    va_end(args);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, command=%s, error='%s'", buffer.Data(), this->context->errstr);
        this->coord->Destory(promise);
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::HGETALL(const char* key) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "HGETALL %s", key);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] HGETALL failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::HDEL(const char* key, const char* field) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "HDEL %s %s", key, field);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] HDEL failed, key=%s, field=%s, error='%s'", key, field, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::HMSET(const char* key, const char* field, const char* value) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "HMSET %s %s %s", key, field, value);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] HMSET failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::HMSET(const char* key, const char* field, uint64_t value) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    static thread_local char buffer[64];
    snprintf(buffer, sizeof(buffer), "%ld", value);
    return this->HMSET(key, field, buffer);
}

RedisPromise* AsyncClient::SET(const char* key, const char* value) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "SET %s %s", key, value);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SET failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::SET(const char* key, const char* data, size_t len) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    const char *argv[3] = {"SET", key, data};
    const size_t argvlen[3] = {3, strlen(key), len};
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommandArgv(this->context, AsyncClient::getCallback, promise, 3, argv, argvlen);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SET failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::SETEX(const char* key, const char* data, size_t len, size_t expire) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    static thread_local char expireBuffer[64];
    int expireBufferLen = sprintf(expireBuffer, "%ld", expire);
    const char *argv[4] = {"SETEX", key, expireBuffer, data};
    const size_t argvlen[4] = {5, strlen(key), (size_t)expireBufferLen, len};

    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommandArgv(this->context, AsyncClient::getCallback, promise, 4, argv, argvlen);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SETEX failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

RedisPromise* AsyncClient::SETEX(const char* key, const char* data, size_t expire) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    return this->SETEX(key, data, strlen(data), expire);
}

RedisPromise * AsyncClient::DEL(const char* key) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    RedisPromise* promise = new redis::RedisPromise(this->coord);
    int err = redisAsyncCommand(this->context, AsyncClient::getCallback, promise, "DEL %s", key);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SETEX failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}


}
} 
