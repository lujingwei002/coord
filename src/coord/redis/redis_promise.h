#pragma once 

#include "coord/coordx.h"

#include "coord/base/base_promise.h"
#include "coord/redis/declare.h"
namespace coord {
    class Coord;
}

///
///
/// 回调结束后，promise就释放
/// promise生命周期由client管理 
///
///

namespace coord {//tolua_export
namespace redis {//tolua_export

typedef base_promise<AsyncClient*, const RedisResultRef&> base_redis_promise;
class RedisPromise: public base_redis_promise, public coordx::RcObject { //tolua_export
CC_CLASS(RedisPromise);
friend AsyncClient;
private:
    RedisPromise(Coord *coord);
    virtual ~RedisPromise();
};//tolua_export



}//tolua_export
}//tolua_export


