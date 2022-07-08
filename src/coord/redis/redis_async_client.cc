#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_reply.h"
#include "coord/redis/redis_promise.h"
#include "coord/builtin/slice.h"
#include "coord/coord.h"
#include <hiredis/adapters/libuv.h>

namespace coord {
namespace redis {

CC_IMPLEMENT(AsyncClient, "coord::redis::AsyncClient")

AsyncClient* newAsyncClient(Coord *coord) {
    auto client = new AsyncClient(coord);
    return client;
}

static void connectCallback(const redisAsyncContext* c, int status) {
    AsyncClient* client = (AsyncClient*)c->data;
    if (status != REDIS_OK) {
        client->recvConnectError(c->errstr);
        return;
    }
    client->recvConnect();
}

static void disconnectCallback(const redisAsyncContext* c, int status) {
    AsyncClient* client = (AsyncClient*)c->data;
    if (status != REDIS_OK) {
        client->recvDisconnectError(c->errstr);
        return;
    }
    client->recvDisconnect();
}

static void getCallback(redisAsyncContext *c, void *data, void *privdata) {
    AsyncClient* client = (AsyncClient*)c->data;
    Promise* promise = (Promise*)privdata;
    redisReply* r = (redisReply*)data;

    Reply reply(client->coord, r, false);
    client->recvGetCallback(promise, reply);
}

AsyncClient::AsyncClient(Coord *coord) {
    this->coord = coord;
    this->status = redis_client_status_nil;
    this->connectPromise = nullptr;
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
    Promise* promise = this->auth(this->config.Password.c_str());
    if (promise == NULL){
        this->rejectConnect();
        return;
    }
    promise->Then([this](AsyncClient* client, Reply& reply){
        this->coord->CoreLogDebug("[RedisAsyncClient] authResolve");
        //密码验证成功
        if (this->config.DB.length() <= 0) {
            this->resolveConnect();
            return;
        }
        Promise* promise = this->select(this->config.DB.c_str());
        if (promise == NULL){
            this->rejectConnect();
            return;
        }  
        promise->Then([this](AsyncClient* client, Reply& reply){
            this->resolveConnect();
            return;
        });        
        promise->Else([this](AsyncClient* client, Reply& reply){
            this->coord->CoreLogDebug("[RedisAsyncClient] recvConnect failed, error='SELECT'");
            //密码验证失败，断开链接
            this->rejectConnect();
        });
    });
    promise->Else([this](AsyncClient* client, Reply& reply){
        this->coord->CoreLogDebug("[RedisAsyncClient] recvConnect failed, error='AUTH'");
        //密码验证失败，断开链接
        this->rejectConnect();
    });
}

void AsyncClient::recvGetCallback(Promise* promise, Reply& reply) {
    if (reply.Error()) {
        promise->reject(this, reply);
    } else {
        promise->resolve(this, reply);
    }
    this->promiseDict.erase(promise);
    this->coord->Destory(promise);
    //this->coord->Destory(reply);
}

void AsyncClient::recvDisconnectError(const char* error) {
    this->coord->CoreLogError("[RedisAsyncClient] recvDisconnectError, error='%s'", error);
    this->status = redis_client_status_error;
}

void AsyncClient::recvDisconnect() {
    this->coord->CoreLogWarn("[RedisAsyncClient] recvDisconnect");
    this->status = redis_client_status_error;
}

Promise* AsyncClient::Connect() {
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
    Promise* promise = redis::newPromise(this->coord);
    redisLibuvAttach(c, &this->coord->loop);
    redisAsyncSetConnectCallback(c, connectCallback);
    redisAsyncSetDisconnectCallback(c, disconnectCallback);
    this->context = c;
    this->connectPromise = promise;
    return promise;
}

Promise * AsyncClient::select(const char* db) {
    if(this->status != redis_client_status_connecting) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "SELECT %s", db);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] SELECT failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::SELECT(const char* db) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "SELECT %s", db);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] SELECT failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise * AsyncClient::auth(const char* password) {
    if(this->status != redis_client_status_connecting) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "AUTH %s", password);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] AUTH failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise * AsyncClient::AUTH(const char* password) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "AUTH %s", password);
    if (err != REDIS_OK) {
        this->coord->CoreLogError("[RedisAsyncClient] AUTH failed, error='%s'", this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::EXPIRE(const char* key, uint64_t expire) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "EXPIRE %s %ld", key, expire);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::GET(const char* key) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "GET %s", key);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::SCRIPT_LOAD(const char* str) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "SCRIPT LOAD %s", str);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, command=%s, error='%s'", str, this->context->errstr);
        this->coord->Destory(promise);
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::EVALSHA(const char* sha1, const char* format, ...) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    static thread_local byte_slice buffer;
    buffer.Reserve(10 + strlen(sha1) + strlen(format));
    sprintf(buffer.Data(), "EVALSHA %s %s",  sha1, format);
    Promise* promise = redis::newPromise(this->coord);
    va_list args;
    va_start(args, format);
    int err = redisvAsyncCommand(this->context, getCallback, promise, buffer.Data(), args);
    va_end(args);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] Get failed, command=%s, error='%s'", buffer.Data(), this->context->errstr);
        this->coord->Destory(promise);
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::HGETALL(const char* key) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "HGETALL %s", key);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] HGETALL failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::HDEL(const char* key, const char* field) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "HDEL %s %s", key, field);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] HDEL failed, key=%s, field=%s, error='%s'", key, field, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::HMSET(const char* key, const char* field, const char* value) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "HMSET %s %s %s", key, field, value);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] HMSET failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::HMSET(const char* key, const char* field, uint64_t value) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    static thread_local char buffer[64];
    snprintf(buffer, sizeof(buffer), "%ld", value);
    return this->HMSET(key, field, buffer);
}

Promise* AsyncClient::SET(const char* key, const char* value) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "SET %s %s", key, value);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SET failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::SET(const char* key, const char* data, size_t len) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    const char *argv[3] = {"SET", key, data};
    const size_t argvlen[3] = {3, strlen(key), len};
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommandArgv(this->context, getCallback, promise, 3, argv, argvlen);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SET failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::SETEX(const char* key, const char* data, size_t len, size_t expire) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    static thread_local char expireBuffer[64];
    int expireBufferLen = sprintf(expireBuffer, "%ld", expire);
    const char *argv[4] = {"SETEX", key, expireBuffer, data};
    const size_t argvlen[4] = {5, strlen(key), (size_t)expireBufferLen, len};

    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommandArgv(this->context, getCallback, promise, 4, argv, argvlen);
    if(err != REDIS_OK){
        this->coord->CoreLogError("[RedisAsyncClient] SETEX failed, key=%s, error='%s'", key, this->context->errstr);
        this->coord->Destory(promise);
        return nullptr;
    }
    this->promiseDict[promise] = promise;
    return promise;
}

Promise* AsyncClient::SETEX(const char* key, const char* data, size_t expire) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    return this->SETEX(key, data, strlen(data), expire);
}

Promise * AsyncClient::DEL(const char* key) {
    if(this->status != redis_client_status_connected) {
        return nullptr;
    }
    Promise* promise = redis::newPromise(this->coord);
    int err = redisAsyncCommand(this->context, getCallback, promise, "DEL %s", key);
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
