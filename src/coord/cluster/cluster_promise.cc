#include "coord/cluster/cluster_promise.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_server.h"
#include "coord/component/script_component.h"
#include "coord/builtin/exception.h"
#include "coord/script/script.h"

namespace coord {

namespace cluster {
CC_IMPLEMENT(Promise, "coord::cluster::Promise")

Promise* newPromise(Coord* coord) {
    Promise* pomise = new Promise(coord);
    return pomise;
}

Promise::Promise(Coord* coord) {
    this->coord = coord;
    this->resolveFunc = NULL;
    this->rejectFunc = NULL;
    this->reqTime = uv_hrtime();
    this->resolveRef = 0;
    this->rejectRef = 0;
}

Promise::~Promise() {
   this->coord->CoreLogDebug("[cluster::Promise] ~");
   if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
    }
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
    }
}

Promise* Promise::Then(ScriptComponent* object, int ref){
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    this->resolveFunc = std::bind(&ScriptComponent::recvClusterResult, object, std::placeholders::_1, "recvClusterResult", ref);
    return this;    
} 

Promise* Promise::Else(ScriptComponent* object, int ref){
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->resolveRef = ref;
    this->rejectFunc = std::bind(&ScriptComponent::recvClusterResult, object, std::placeholders::_1, "recvClusterResult", ref);
    return this;
}

Promise* Promise::Then(Promise_Resolve func){
    this->resolveFunc = func;
    return this;    
} 

Promise* Promise::Else(Promise_Reject func){
    this->rejectFunc = func;
    return this;    
} 

void Promise::resolve(Result* result) {
    this->coord->CoreLogDebug("[cluster::Promise] resolve");
    if(this->resolveFunc == NULL) {
        return;
    }
    try{
        //传递到逻辑层
        this->resolveFunc(result);
    } catch(ScriptException& e){
    }
}

void Promise::reject(Result* result){
    this->coord->CoreLogDebug("[cluster::Promise] reject");
    if(this->rejectFunc == NULL) {
        return;
        
    }
    try{
        //传递到逻辑层
        this->rejectFunc(result);
    } catch(ScriptException& e){
    }
}

int Promise::Then(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::cluster::Promise",0,&tolua_err) ||
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
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Then'.\nattempt to set a nil function", NULL);
            return 0;
        }
        Promise* tolua_ret = (Promise*)  this->Then(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::cluster::Promise");
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Then'.",&tolua_err);
    return 0;
#endif
}

int Promise::Else(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::cluster::Promise",0,&tolua_err) ||
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
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Else'.\nattempt to set a nil function", NULL);
            return 0;
        }
        Promise* tolua_ret = (Promise*)  this->Else(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::cluster::Promise"); 
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
