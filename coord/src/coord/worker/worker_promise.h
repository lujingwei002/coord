#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include <libuv/uv.h>
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
class RequestPipeline;
class BaseRequest;
class ScriptComponent;

namespace protobuf{
class Reflect;
}

namespace worker {//tolua_export
class Worker;
class Result;

typedef std::function<void (Result* result, BaseRequest* request)> PromiseResolveFunc; 
typedef std::function<void (Result* result, BaseRequest* request)> PromiseRejectFunc; 

class Promise : public Destoryable { //tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord* coord);
    virtual ~Promise();
public:
    Promise* Then(PromiseResolveFunc resolveFunc);
    Promise* Else(PromiseRejectFunc rejectFunc);
    int Then(lua_State* L);//tolua_export
    int Else(lua_State* L);//tolua_export
    Promise* Then(ScriptComponent* object, int ref);
    Promise* Else(ScriptComponent* object, int ref);
    Promise* Using(BaseRequest* request);//tolua_export
public:
    void resolve(Result* result);
    void reject(Result* result);
public:
    PromiseResolveFunc      resolveFunc;
    PromiseRejectFunc       rejectFunc;
    int                     resolveRef;
    int                     rejectRef;
    Coord*                  coord;
    uint64_t                reqTime; 
    std::string             route;
    BaseRequest*            requestUsing;
};//tolua_export

Promise* newPromise(Coord* coord);

}//tolua_export

}//tolua_export
