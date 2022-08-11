#include "coord/cache/cache_result.h"
#include "coord/redis/redis_result.h"
#include "coord/coord.h"
#include <cassert>

namespace coord {
namespace cache {
CC_IMPLEMENT(CacheResult, "coord::cache::CacheResult")



CacheResult::CacheResult(Coord *coord, redis::RedisResult* result) : 
    coord(coord), result(result) {
}

CacheResult::~CacheResult() {
}

bool CacheResult::operator== (std::nullptr_t v) const  {
    return this->result == nullptr;
}

bool CacheResult::operator!= (std::nullptr_t v) const  {
    return this->result != nullptr;
}

const char* CacheResult::String() {
    return this->result->String();
}

bool CacheResult::Empty() {return this->result->Empty();}
bool CacheResult::Error() {return this->result->Error();}
}
}        