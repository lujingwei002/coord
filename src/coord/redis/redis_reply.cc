#include "coord/redis/redis_reply.h"
#include "coord/coord.h"
#include "coord/builtin/ref_manager.h"
#include <cassert>

namespace coord {
namespace redis {

CC_IMPLEMENT(Reply, "coord::redis::Reply")

Reply::Reply(std::nullptr_t) {
    this->coord = coorda;
    this->reply = nullptr;
}

Reply::Reply(Coord *coord, redisReply* reply)  {
    this->coord = coord;
    this->reply = reply;
    if(this->reply) {
        refManager.reference(this->reply);
    }
}

Reply::Reply(const Reply& other) {
    this->coord = other.coord;
    this->reply = other.reply;
    if(this->reply) {
        refManager.reference(this->reply);
    }
}

Reply::Reply(const Reply* other) {
    if (nullptr == other) {
        this->coord = nullptr;
        this->reply = nullptr;
    } else {
        this->coord = other->coord;
        this->reply = other->reply;
        if(this->reply) {
            refManager.reference(this->reply);
        }
    }
}

Reply& Reply::operator=(const Reply& other) {
    if(this->reply) {
        if (refManager.release(this->reply) == 0) {
            freeReplyObject(this->reply);
            this->reply = nullptr;
        }
    }
    this->coord = other.coord;
    this->reply = other.reply;
    if(this->reply) {
        refManager.reference(this->reply);
    }
    return *this;
}

bool Reply::operator== (std::nullptr_t v) const  {
    return this->reply == nullptr;
}

bool Reply::operator!= (std::nullptr_t v) const  {
    return this->reply != nullptr;
}

Reply::~Reply() {
    if(this->reply) {
        if (refManager.release(this->reply) == 0) {
            printf("freeReplyObject\n");
            freeReplyObject(this->reply);
        }
        this->reply = nullptr;
    }
}

bool Reply::Error() const {
    if (this->reply == nullptr){
        return true;
    }
    if (this->reply->type == REDIS_REPLY_ERROR){
        return true;
    }
    return false;
}

bool Reply::Empty() const {
    if (this->reply == nullptr){
        return true;
    }
    if (this->reply->type == REDIS_REPLY_NIL) {
        return true;
    }
    return false;
}

bool Reply::Array() const {
    if (this->reply == nullptr){
        return true;
    }
    if (this->reply->type == REDIS_REPLY_ARRAY) {
        return true;
    }
    return false;
}

int Reply::ArrayCount() const {
    if (this->reply == nullptr){
        return 0;
    }
    if (this->reply->type != REDIS_REPLY_ARRAY) {
        return 0;
    }
    return this->reply->elements;
}

const char* Reply::String() const {
    if(this->reply == nullptr){
        return nullptr;
    }
    if (this->reply->type != REDIS_REPLY_STRING && this->reply->type != REDIS_REPLY_STATUS && this->reply->type != REDIS_REPLY_ERROR ) {
        return nullptr;
    }
    return this->reply->str;
}

long long Reply::Integer() const {
    if(this->reply == nullptr){
        return 0;
    }
    if (this->reply->type != REDIS_REPLY_INTEGER) {
        return 0;
    }
    return this->reply->integer;
}

long long Reply::Integer(size_t index) const {
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

bool Reply::Empty(size_t index) const {
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

const char* Reply::String(size_t index) const {
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
