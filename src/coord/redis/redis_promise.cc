#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_result.h"
#include "coord/coord.h"

namespace coord {
namespace redis {

CC_IMPLEMENT(RedisPromise, "coord::redis::RedisPromise")

RedisPromise::RedisPromise(Coord *coord) : base_promise(coord)  {
}

RedisPromise::~RedisPromise() {
}


}
} 
