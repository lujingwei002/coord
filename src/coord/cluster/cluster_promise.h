#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/cluster/cluster_message.h"
#include "coord/protobuf/declare.h"
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
class ScriptComponent;


namespace cluster {//tolua_export

class cluster_agent; 
class Cluster;
class Result;

typedef std::function<void (Result* result)> Promise_Resolve; 
typedef std::function<void (Result* result)> Promise_Reject; 

class Promise : public RcObject { //tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord* coord);
    virtual ~Promise();
public:
    void resolve(Result* result);
    void reject(Result* result);
    Promise* Then(Promise_Resolve func);
    Promise* Else(Promise_Reject func);
    int Then(lua_State* L);//tolua_export
    int Else(lua_State* L);//tolua_export
    Promise* Then(ScriptComponent* object, int ref);
    Promise* Else(ScriptComponent* object, int ref);
public:
    Promise_Resolve resolveFunc;
    Promise_Reject  rejectFunc;
    int             resolveRef;
    int             rejectRef;
    Coord*          coord;
    uint64_t        reqTime; 
    std::string     route;
};//tolua_export

Promise* newPromise(Coord* coord);

}//tolua_export
}//tolua_export


