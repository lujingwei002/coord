#include "coord/redis/redis_result.h"
#include "coord/coord.h"
#include <cassert>

namespace coord {
namespace redis {

CC_IMPLEMENT(RedisResult, "coord::redis::RedisResult")

RedisResult::RedisResult(Coord *coord, redisReply* reply)  {
    this->coord = coord;
    this->reply = reply;
}

RedisResult::~RedisResult() {
    if(this->reply) {
        freeReplyObject(this->reply);
        this->reply = nullptr;
    }
}

bool RedisResult::Error() const {
    if (this->reply == nullptr){
        return true;
    }
    if (this->reply->type == REDIS_REPLY_ERROR){
        return true;
    }
    return false;
}

bool RedisResult::Empty() const {
    if (this->reply == nullptr){
        return true;
    }
    if (this->reply->type == REDIS_REPLY_NIL) {
        return true;
    }
    return false;
}

bool RedisResult::Array() const {
    if (this->reply == nullptr){
        return true;
    }
    if (this->reply->type == REDIS_REPLY_ARRAY) {
        return true;
    }
    return false;
}

int RedisResult::ArrayCount() const {
    if (this->reply == nullptr){
        return 0;
    }
    if (this->reply->type != REDIS_REPLY_ARRAY) {
        return 0;
    }
    return this->reply->elements;
}

const char* RedisResult::String() const {
    if(this->reply == nullptr){
        return nullptr;
    }
    if (this->reply->type != REDIS_REPLY_STRING && this->reply->type != REDIS_REPLY_STATUS && this->reply->type != REDIS_REPLY_ERROR ) {
        return nullptr;
    }
    return this->reply->str;
}

long long RedisResult::Integer() const {
    if(this->reply == nullptr){
        return 0;
    }
    if (this->reply->type != REDIS_REPLY_INTEGER) {
        return 0;
    }
    return this->reply->integer;
}

long long RedisResult::Integer(size_t index) const {
   if(this->reply == nullptr){
        return 0;
    }
    if (this->reply->type != REDIS_REPLY_ARRAY) {
        return 0;
    }
    if (index < 0 || index >= this->reply->elements) {
        return 0;
    }
    redisReply* element = this->reply->element[index];
    if (element->type != REDIS_REPLY_INTEGER ) {
        return 0;
    }
    return element->integer;
}

bool RedisResult::Empty(size_t index) const {
   if(this->reply == nullptr){
        return true;
    }
    if (this->reply->type != REDIS_REPLY_ARRAY) {
        return true;
    }
    if (index < 0 || index >= this->reply->elements) {
        return true;
    }
    redisReply* element = this->reply->element[index];
    if (element->type == REDIS_REPLY_NIL ) {
        return true;
    }
    return false;
}

const char* RedisResult::String(size_t index) const {
    if(this->reply == nullptr){
        return nullptr;
    }
    if (this->reply->type != REDIS_REPLY_ARRAY) {
        return nullptr;
    }
    if (index < 0 || index >= this->reply->elements) {
        return nullptr;
    }
    redisReply* element = this->reply->element[index];
    if (element->type != REDIS_REPLY_STRING && element->type != REDIS_REPLY_STATUS && element->type != REDIS_REPLY_ERROR ) {
        return nullptr;
    }
    return element->str;
}


}
}        
