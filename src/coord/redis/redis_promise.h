#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/base/base_promise.h"

namespace coord {
    class Coord;
    namespace redis {
        class RedisResult;
        class AsyncClient;
    }
}


namespace coord {//tolua_export
namespace redis {//tolua_export

typedef base_promise<AsyncClient*, RedisResult*> base_redis_promise;
class RedisPromise: public base_redis_promise, public Destoryable { //tolua_export
CC_CLASS(RedisPromise);
friend AsyncClient;
private:
    RedisPromise(Coord *coord);
    virtual ~RedisPromise();
};//tolua_export



}//tolua_export
}//tolua_export


