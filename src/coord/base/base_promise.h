#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include <uv.h>
#include <map>
#include <functional>
#include <any>
#include <tuple>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}


namespace coord {//tolua_export

class Coord;
class ScriptComponent;

template<typename TClient, typename TResult>
class base_promise { 
public:
typedef std::function<void (TClient client, TResult result)> ResolveFunc; 
typedef std::function<void (TClient client, TResult result)> RejectFunc; 
public:
    base_promise(Coord* coord);
    virtual ~base_promise();
public:
    virtual const char* TypeName() const { return nullptr;}
    int Then(lua_State* L);
    int Else(lua_State* L);
    base_promise* Then(ResolveFunc func);
    base_promise* Else(RejectFunc func);
    base_promise* Then(ScriptComponent* object, int ref);
    base_promise* Else(ScriptComponent* object, int ref);
    // package回调 或者 component回调
    base_promise* Then(int ref);
    // package回调 或者 component回调
    base_promise* Else(int ref);
public:
    void reject(TClient client, TResult result);
    void resolve(TClient client, TResult result);
private:
    void recvResult(TClient client, TResult result, int ref);
    int componentThen(lua_State* L);
    int packageThen(lua_State* L);
    int componentElse(lua_State* L);
    int packageElse(lua_State* L);
protected:
    Coord*              coord;
    int                 resolveRef;
    int                 rejectRef;
    ResolveFunc         resolveFunc;
    RejectFunc          rejectFunc;
public:
    std::string         route;
    uint64_t            reqTime; 
};

template<typename TClient, typename TResult>
base_promise<TClient, TResult>::base_promise(Coord* coord) {
    this->coord = coord;
    this->resolveFunc = nullptr;
    this->rejectFunc = nullptr;
    this->reqTime = uv_hrtime();
    this->resolveRef = 0;
    this->rejectRef = 0;
}

template<typename TClient, typename TResult>
base_promise<TClient, TResult>::~base_promise() {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
    }
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
    }
}

template<typename TClient, typename TResult>
base_promise<TClient, TResult>* base_promise<TClient, TResult>::Then(ResolveFunc func) {
    this->resolveFunc = func;
    return this;    
}

template<typename TClient, typename TResult>
base_promise<TClient, TResult>* base_promise<TClient, TResult>::Else(RejectFunc func) {
    this->rejectFunc = func;
    return this;    
}

template<typename TClient, typename TResult>
int base_promise<TClient, TResult>::Then(lua_State* L) {
    tolua_Error tolua_err;
    if (tolua_isusertype(L, 2, "coord::ScriptComponent", 0, &tolua_err)) {
        return this->componentThen(L);
    } else {
        return this->packageThen(L);
    }
}

template<typename TClient, typename TResult>
int base_promise<TClient, TResult>::packageThen(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L, 1, this->TypeName(), 0, &tolua_err) ||
        !tolua_isfunction(L, 2, 0,&tolua_err) ||
        !tolua_isnoobj(L, 3, &tolua_err)
    )
        goto tolua_lerror;
    else 
#endif
    {
        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Then'.\nattempt to set a nil function", NULL);
            return 0;
        }
        base_promise* tolua_ret = (base_promise*)  this->Then(ref);
        tolua_pushusertype(L, (void*)tolua_ret, this->TypeName());
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Then'.",&tolua_err);
    return 0;
#endif
}

template<typename TClient, typename TResult>
int base_promise<TClient, TResult>::componentThen(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L, 1, this->TypeName(), 0, &tolua_err) ||
        !tolua_isusertype(L, 2, "coord::ScriptComponent",0, &tolua_err) ||
        !tolua_isfunction(L, 3, 0,&tolua_err) ||
        !tolua_isnoobj(L, 4, &tolua_err)
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
        base_promise* tolua_ret = (base_promise*)  this->Then(object,ref);
        tolua_pushusertype(L, (void*)tolua_ret, this->TypeName());
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Then'.",&tolua_err);
    return 0;
#endif
}

template<typename TClient, typename TResult>
int base_promise<TClient, TResult>::Else(lua_State* L) {
    tolua_Error tolua_err;
    if (tolua_isusertype(L, 2, "coord::ScriptComponent", 0, &tolua_err)) {
        return this->componentElse(L);
    } else {
        return this->packageElse(L);
    }
}

template<typename TClient, typename TResult>
int base_promise<TClient, TResult>::packageElse(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L, 1, this->TypeName(), 0, &tolua_err) ||
        !tolua_isfunction(L, 2, 0, &tolua_err) ||
        !tolua_isnoobj(L, 3, &tolua_err)
    )
        goto tolua_lerror;
    else 
#endif
    {
        lua_pushvalue(L, 2);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Else'.\nattempt to set a nil function", NULL);
            return 0;
        }
        base_promise* tolua_ret = (base_promise*)  this->Else(ref);
        tolua_pushusertype(L,(void*)tolua_ret, this->TypeName()); 
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Else'.",&tolua_err);
    return 0;
#endif
}

template<typename TClient, typename TResult>
int base_promise<TClient, TResult>::componentElse(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L, 1, this->TypeName(), 0, &tolua_err) ||
        !tolua_isusertype(L, 2, "coord::ScriptComponent", 0, &tolua_err) ||
        !tolua_isfunction(L, 3, 0, &tolua_err) ||
        !tolua_isnoobj(L, 4, &tolua_err)
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
        base_promise* tolua_ret = (base_promise*)  this->Else(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret, this->TypeName()); 
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Else'.",&tolua_err);
    return 0;
#endif
}

template<typename TClient, typename TResult>
void base_promise<TClient, TResult>::recvResult(TClient client, TResult result, int ref) {

    this->coord->CoreLogDebug("[%s] recvResult ref=%d", this->TypeName(), ref);
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, client, client->TypeName());
    tolua_pushusertype(L, result, result->TypeName());
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[%s] recvResult failed, error=%s", this->TypeName(), lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

template<typename TClient, typename TResult>
base_promise<TClient, TResult>* base_promise<TClient, TResult>::Then(ScriptComponent* object, int ref) {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    //   this->rejectFunc = std::bind(&ScriptComponent::recvClusterResult, object, std::placeholders::_1, "recvClusterResult", ref);
    return this;
}


template<typename TClient, typename TResult>
base_promise<TClient, TResult>* base_promise<TClient, TResult>::Else(ScriptComponent* object, int ref) {
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->rejectRef = ref;
    //this->rejectFunc = std::bind(&ScriptComponent::recvClusterResult, object, std::placeholders::_1, "recvClusterResult", ref);
    return this;
}

template<typename TClient, typename TResult>
base_promise<TClient, TResult>* base_promise<TClient, TResult>::Then(int ref) {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    this->resolveFunc = std::bind(&base_promise<TClient, TResult>::recvResult, this, std::placeholders::_1, std::placeholders::_2, ref);
    return this;
}


template<typename TClient, typename TResult>
base_promise<TClient, TResult>* base_promise<TClient, TResult>::Else(int ref) {
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->rejectRef = ref;
    this->rejectFunc = std::bind(&base_promise<TClient, TResult>::recvResult, this, std::placeholders::_1, std::placeholders::_2, ref);
    return this;
}

template<typename TClient, typename TResult>
void base_promise<TClient, TResult>::reject(TClient client, TResult result) {
    this->coord->CoreLogDebug("[%s] reject", this->TypeName());
    if(this->rejectFunc == nullptr) {
        return;
    }
    try{
        //传递到逻辑层
        this->rejectFunc(client, result);
    } catch(ScriptException& e){
    }
}

template<typename TClient, typename TResult>
void base_promise<TClient, TResult>::resolve(TClient client, TResult result) {
    this->coord->CoreLogDebug("[%s] resolve", this->TypeName());
    if(this->resolveFunc == nullptr) {
        return;
    }
    try{
        //传递到逻辑层
        this->resolveFunc(client, result);
    } catch(ScriptException& e){
    }
}

}//tolua_export


