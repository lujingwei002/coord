#include "coord/cache/cache_reader.h"
#include "coord/redis/redis_result.h"
#include "coord/coord.h"
#include <cassert>

namespace coord {
namespace cache {
CC_IMPLEMENT(CacheReader, "coord::cache::CacheReader")

CacheReader* newCacheReader(Coord* coord, const redis::RedisResult* reply) {
    auto self = new CacheReader(coord, reply);
    return self;
}

CacheReader::CacheReader(std::nullptr_t) : coord(coorda), reply(nullptr) {
    assert(coorda);
}

CacheReader::CacheReader(Coord *coord, const redis::RedisResult* reply) : 
    coord(coord), reply(reply) {
}

CacheReader::CacheReader(Coord *coord, const redis::RedisResult& reply) : 
    coord(coord), reply(reply) {
}

CacheReader::~CacheReader() {
}

bool CacheReader::operator== (std::nullptr_t v) const  {
    return this->reply == nullptr;
}

bool CacheReader::operator!= (std::nullptr_t v) const  {
    return this->reply != nullptr;
}

const char* CacheReader::String() {
    return this->reply.String();
}


}
}        