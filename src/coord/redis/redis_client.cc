#include "coord/redis/redis_client.h"
#include "coord/redis/redis_result.h"
#include "coord/redis/redis_mgr.h"
#include "coord/builtin/error.h"
#include "coord/coord.h"

namespace coord {
namespace redis {

CC_IMPLEMENT(Client, "coord::redis::Client")


Client::Client(Coord *coord, RedisMgr* redisMgr) {
    this->coord = coord;
    this->redisMgr = redisMgr;
    this->context = nullptr;
}   

Client::~Client() {
    if(nullptr != this->context) {
        redisFree(this->context);
        this->context = nullptr;
    }
    this->redisMgr->free(this);
}

void Client::onDestory() {
    this->Close();
}

RedisConfig* Client::DefaultConfig() {
    return &this->config;
}

void Client::Close() {
    if(!this->context) {
        return;
    }
    redisFree(this->context);
    this->context = nullptr;
}

int Client::Connect() {
    redisContext* c = redisConnect(this->config.Host.c_str(), this->config.Port);
    if(c == nullptr) {
        this->coord->CoreLogError("[%s] Connect failed", this->TypeName());
        return ErrorConnect;
    }
    if (c->err != 0) {
        redisFree(c);
        this->coord->CoreLogError("[%s] Connect failed, host='%s', port=%d, error='%s'", this->TypeName(), this->config.Host.c_str(), this->config.Port, ""/*c->errstr */);
        return ErrorConnect;
    }
    if(!(c->flags & REDIS_CONNECTED)){
        redisFree(c);
        this->coord->CoreLogError("[%s] Connect failed, host='%s', port=%d, error='%s'", this->TypeName(), this->config.Host.c_str(), this->config.Port, ""/* c->errstr */);
        return ErrorConnect;
    }
    this->context = c;
    if (this->config.Password.length() > 0) {
        RedisResult result = this->AUTH(this->config.Password.c_str());
        if(result.Error()) {
            this->coord->CoreLogError("[%s] Connect failed, function='AUTH', password='%s', error='%s'", this->TypeName(), this->config.Password.c_str(), ""/* c->errstr */);
            this->Close();
            return ErrorInvalidPassword;
        }
    }
    if (this->config.DB.length() > 0) {
        RedisResult result = this->SELECT(this->config.DB.c_str());
        if(result.Error()) {
            this->coord->CoreLogError("[%s] Connect failed, function='SELECT', db='%s', error='%s'", this->TypeName(), this->config.DB.c_str(), ""/* c->errstr */);
            this->Close();
            return ErrorInvalidDb;
        }
    }
    return 0;
}

RedisResult Client::SELECT(const char* db) {
    if (!this->context) {
        return nullptr;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "SELECT %s", db);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SELECT failed, error='%s'", this->TypeName(), this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::AUTH(const char* password) {
    if (!this->context) {
        return nullptr;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "AUTH %s", password);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] AUTH failed, error='%s'", this->TypeName(), this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

int Client::EXPIRE(const char* key, uint64_t expire) {
    if (!this->context) {
        return -1;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "EXPIRE %s %ld", key, expire);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] Get failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return -1;
    }
    if (reply->type == REDIS_REPLY_ERROR) {
        return -1;
    }
    freeReplyObject(reply);
    return 0;
}

RedisResult Client::GET(const char* key) {
    if (!this->context) {
        return nullptr;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "GET %s", key);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] Get failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::HGETALL(const char* key) {
    if (!this->context) {
        return nullptr;
    }
    redisReply * reply = (redisReply *)redisCommand(this->context, "HGETALL %s", key);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] HGETALL failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

int Client::HDEL(const char* key, const char* field) {
    if (!this->context) {
        return ErrorNotConnected;
    }
    redisReply * reply = (redisReply *)redisCommand(this->context, "HDEL %s %s", key, field);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] HDEL failed, key='%s', field='%s', error='%s'", this->TypeName(), key, field, this->context->errstr);
        return -1;
    }
    if (reply->type == REDIS_REPLY_ERROR) {
        return -1;
    }
    if (reply->type != REDIS_REPLY_INTEGER) {
        return -1;
    }
    int count = reply->integer;
    freeReplyObject(reply);
    return count;
}

RedisResult Client::HMSET(const char* key, const char* field, const char* value) {
    if (!this->context) {
        return nullptr;
    }
    redisReply * reply = (redisReply *)redisCommand(this->context, "HMSET %s %s %s", key, field, value);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] HMSET failed, key='%s', error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::HMSET(const char* key, const char* field, uint64_t value) {
    if (!this->context) {
        return nullptr;
    }
    static thread_local char buffer[64];
    snprintf(buffer, sizeof(buffer), "%ld", value);
    return this->HMSET(key, field, buffer);
}

RedisResult Client::SET(const char* key, const char* value) {
    if (!this->context) {
        return nullptr;
    }
    redisReply * reply = (redisReply *)redisCommand(this->context, "SET %s %s", key, value);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SET failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::SET(const char* key, const char* data, size_t len) {
    if (!this->context) {
        return nullptr;
    }
    const char* argv[3] = {"SET", key, data};
    const size_t argvlen[3] = {3, strlen(key), len};
    redisReply* reply = (redisReply *)redisCommandArgv(this->context, 3, argv, argvlen);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SET failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::SETEX(const char* key, const char* data, size_t len, size_t expire) {
    if (!this->context) {
        return nullptr;
    }
    static thread_local char expireBuffer[64];
    int expireBufferLen = sprintf(expireBuffer, "%ld", expire);
    const char* argv[4] = {"SETEX", key, expireBuffer, data};
    const size_t argvlen[4] = {5, strlen(key), (size_t)expireBufferLen, len};
    redisReply* reply = (redisReply *)redisCommandArgv(this->context, 4, argv, argvlen);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SETEX failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::SETEX(const char* key, const char* data, size_t expire) {
    if (!this->context) {
        return nullptr;
    }
    return this->SETEX(key, data, strlen(data), expire);
}

RedisResult Client::DEL(const char* key) {
    if (!this->context) {
        return nullptr;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "DEL %s", key);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SETEX failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

uint64_t Client::TIME() {
    if (!this->context) {
        return 0;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "TIME");
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] TIME failed, error='%s'", this->TypeName(), this->context->errstr);
        return 0;
    }
    if (reply->type == REDIS_REPLY_ERROR) {
        return 0;
    }
    if (reply->type != REDIS_REPLY_ARRAY) {
        return 0;
    }
    if (reply->elements != 2) {
        return 0;
    }
    uint64_t microsecond = atoi(reply->element[1]->str);
    uint64_t second = atoi(reply->element[0]->str);
    freeReplyObject(reply);
    return second * 1000000 + microsecond;
}

RedisResult Client::SADD(const char* key, const char* value) {
    if (!this->context) {
        return nullptr;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "SADD %s %s", key, value);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SADD failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

RedisResult Client::SREM(const char* key, const char* value) {
    if (!this->context) {
        return nullptr;
    }
    redisReply* reply = (redisReply *)redisCommand(this->context, "SREM %s %s", key, value);
    if(reply == nullptr){
        this->coord->CoreLogError("[%s] SREM failed, key=%s, error='%s'", this->TypeName(), key, this->context->errstr);
        return nullptr;
    }
    return RedisResult(this->coord, reply);
}

}
}         
