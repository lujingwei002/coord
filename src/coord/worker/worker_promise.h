#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/base/base_promise.h"
#include <uv.h>
#include <map>
#include <functional>
#include <tuple>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}


namespace coord {//tolua_export

class Coord;

namespace worker {//tolua_export

class Result;
class Worker;

typedef base_promise<Worker, Result> base_worker_promise;
class Promise: public base_worker_promise, public Destoryable { //tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord *coord);
    virtual ~Promise();
private:
};//tolua_export

}//tolua_export

}//tolua_export
