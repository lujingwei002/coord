#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
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
class RequestPipeline;
class BaseRequest;
namespace gate {//tolua_export


class GateSession;

typedef std::function<void (GateSession* session, BaseRequest* request)> GatePromise_Resolve; 
typedef std::function<void (GateSession* session, BaseRequest* request)> GatePromise_Reject; 

class GatePromise : public Destoryable { //tolua_export
CC_CLASS(GatePromise);
public:
    GatePromise(Coord* coord);
    virtual ~GatePromise();
public:
    void resolve(GateSession* session);
    void reject(GateSession* session);
    GatePromise* Then(GatePromise_Resolve resolveFunc);
    GatePromise* Else(GatePromise_Reject rejectFunc);
    int Then(lua_State* L);//tolua_export
    int Else(lua_State* L);//tolua_export

    GatePromise* Then(ScriptComponent* object, int ref);
    GatePromise* Else(ScriptComponent* object, int ref);
    GatePromise* Using(BaseRequest* request);//tolua_export
public:
    GatePromise_Resolve resolveFunc;
    GatePromise_Reject  rejectFunc;
    int                 resolveRef;
    int                 rejectRef;
    Coord*              coord;
    uint64_t            reqTime; 
    std::string         route;
    //RequestPipeline*    pipeline;
    BaseRequest*        requestUsing;
};//tolua_export

GatePromise* newGatePromise(Coord* coord);

}//tolua_export
}//tolua_export

