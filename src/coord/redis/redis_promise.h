#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/base/base_promise.h"
#include "coord/redis/redis_result.h"
namespace coord {
    class Coord;
    namespace redis {
        class RedisResult;
        class AsyncClient;
    }
}

///
///
/// 回调结束后，promise就释放
/// promise生命周期由client管理 
///
///

namespace coord {//tolua_export
namespace redis {//tolua_export

typedef base_promise<AsyncClient*, const RedisResultPtr&> base_redis_promise;
class RedisPromise: public base_redis_promise, public Destoryable { //tolua_export
CC_CLASS(RedisPromise);
friend AsyncClient;
private:
    RedisPromise(Coord *coord);
    virtual ~RedisPromise();
};//tolua_export



}//tolua_export
}//tolua_export


