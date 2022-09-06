#include "coord/gate/gate_promise.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_cluster.h"
#include "coord/component/script_component.h"
#include "coord/coordx.h"
#include "coord/base/base_request.h"
#include "coord/script/script.h"
namespace coord {

namespace gate {

RC_IMPLEMENT(GatePromise, "coord::gate::GatePromise")

GatePromise* newGatePromise(Coord* coord) {
    GatePromise* pomise = new GatePromise(coord);
    return pomise;
}

GatePromise::GatePromise(Coord* coord) {
    this->coord = coord;
    this->resolveFunc = NULL;
    this->rejectFunc = NULL;
    this->reqTime = uv_hrtime();
    this->resolveRef = 0;
    this->rejectRef = 0;
   this->requestUsing = NULL;
}

GatePromise::~GatePromise() {
    this->coord->CoreLogDebug("[GatePromise] ~GatePromise");
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
    }
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
    }
    if(this->requestUsing) {
        this->coord->Destory(this->requestUsing);
        this->requestUsing = NULL;
    }
}

GatePromise* GatePromise::Then(GatePromise_Resolve resolveFunc){
    this->resolveFunc = resolveFunc;
    return this;    
} 

GatePromise* GatePromise::Else(GatePromise_Reject rejectFunc){
    this->rejectFunc = rejectFunc;
    return this;
}

GatePromise* GatePromise::Using(base_request* request) {
    if(this->requestUsing) {
        this->coord->Destory(this->requestUsing);
        this->requestUsing = NULL;
    }
    this->requestUsing = request;
    if(this->requestUsing) {
        this->coord->DontDestory(this->requestUsing);
    }
    return this;
}

GatePromise* GatePromise::Then(ScriptComponent* object, int ref) {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    this->resolveFunc = std::bind(&ScriptComponent::recvGatePromise, object, std::placeholders::_1, std::placeholders::_2, "recvGatePromise", ref);
    return this;   
}

GatePromise* GatePromise::Else(ScriptComponent* object, int ref) {
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->rejectRef = ref;
    this->rejectFunc = std::bind(&ScriptComponent::recvGatePromise, object, std::placeholders::_1, std::placeholders::_2, "recvGatePromise", ref);
    return this;   
}

void GatePromise::resolve(GateSession* session) {
    //this->coord->CoreLogDebug("[GatePromise] resolve");
    if(this->resolveFunc == NULL) {
        this->coord->CoreLogDebug("[GatePromise] resolve failed, error='func not found'");
        return;
    }
    try{
       // this->coord->recoverRequestPipeline(this->pipeline);
        //传递到逻辑层
        this->resolveFunc(session, this->requestUsing);
       // this->coord->popRequestPipeline();
    } catch(ScriptException& e){
    }
}

void GatePromise::reject(GateSession* session){
    //this->coord->CoreLogDebug("[GatePromise] reject");
    if(this->rejectFunc == NULL) {
        this->coord->CoreLogDebug("[GatePromise] reject failed, error='func not found'");
        return;
    }
    try{
       // this->coord->recoverRequestPipeline(this->pipeline);
        //传递到逻辑层
        this->rejectFunc(session, this->requestUsing);
      //  this->coord->popRequestPipeline();
    } catch(ScriptException& e){
    }
}

int GatePromise::Then(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GatePromise",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isfunction(L,3,0,&tolua_err) ||
        !tolua_isnoobj(L,4,&tolua_err)
    )
        goto tolua_lerror;
    else 
#endif
    {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        lua_pushvalue(L, 3);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Then'.\nattempt to set a nil function", NULL);
            return 0;
        }
        GatePromise* tolua_ret = (GatePromise*)  this->Then(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::gate::GatePromise");
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Then'.",&tolua_err);
    return 0;
#endif
}

int GatePromise::Else(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GatePromise",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isfunction(L,3,0,&tolua_err) ||
        !tolua_isnoobj(L,4,&tolua_err)
    )
        goto tolua_lerror;
    else 
#endif
    {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        lua_pushvalue(L, 3);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Else'.\nattempt to set a nil function", NULL);
            return 0;
        }
        GatePromise* tolua_ret = (GatePromise*)  this->Else(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::gate::GatePromise");
        
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Else'.",&tolua_err);
    return 0;
#endif
}

} 
}
