#include "coord/builtin/promise.h"
#include "coord/coord.h"
#include "coord/component/script_component.h"
#include "coord/builtin/exception.h"

namespace coord {

CC_IMPLEMENT(Promise, "coord::Promise")

Promise* newPromise(Coord* coord) {
    Promise* pomise = new Promise(coord);
    return pomise;
}

Promise::Promise(Coord* coord) {
    this->coord = coord;
    this->resolveFunc = NULL;
    this->rejectFunc = NULL;
    this->resolveRef = 0;
    this->rejectRef = 0;
}

Promise::~Promise() {
   this->coord->coreLogDebug("[Promise] ~");
   if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
    }
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
    }
}

void Promise::resolve() {
    this->coord->coreLogDebug("[Promise] resolve");
    if(this->resolveFunc == NULL) {
        return;
    }
    try{
        //传递到逻辑层
        this->resolveFunc();
    } catch(ScriptException& e){
    }
}

void Promise::reject() {
    this->coord->coreLogDebug("[Promise] reject");
    if(this->rejectFunc == NULL) {
        return;
        
    }
    try{
        //传递到逻辑层
        this->rejectFunc();
    } catch(ScriptException& e){
    }
}

Promise* Promise::Then(ScriptComponent* object, int ref){
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    this->resolveFunc = std::bind(&ScriptComponent::recvPromise, object, "recvPromise", ref);
    return this;    
} 

Promise* Promise::Else(ScriptComponent* object, int ref){
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->resolveRef = ref;
    this->rejectFunc = std::bind(&ScriptComponent::recvPromise, object, "recvPromise", ref);
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

int Promise::Then(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::Promise",0,&tolua_err) ||
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
        tolua_pushusertype(L,(void*)tolua_ret,"coord::Promise");
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
        !tolua_isusertype(L,1,"coord::Promise",0,&tolua_err) ||
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
        tolua_pushusertype(L,(void*)tolua_ret,"coord::Promise"); 
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Else'.",&tolua_err);
    return 0;
#endif
}


} 