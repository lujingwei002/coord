#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
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
typedef std::function<void (TClient* client, TResult* result)> ResolveFunc; 
typedef std::function<void (TClient* client, TResult* result)> RejectFunc; 
public:
    base_promise(Coord* coord) {
        this->coord = coord;
        this->resolveFunc = nullptr;
        this->rejectFunc = nullptr;
        this->reqTime = uv_hrtime();
        this->resolveRef = 0;
        this->rejectRef = 0;
    }
    virtual ~base_promise() {
        if(this->resolveRef) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        }
        if(this->rejectRef) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        }
    }
public:
    virtual const char* TypeName() const {
        return nullptr;
    }
    base_promise* Then(ResolveFunc func) {
        this->resolveFunc = func;
        return this;    
    }
    base_promise* Else(RejectFunc func) {
        this->rejectFunc = func;
        return this;    
    }
    int Then(lua_State* L) {
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
            int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
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
    int Else(lua_State* L) {
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
    base_promise* Then(ScriptComponent* object, int ref) {
        if(this->rejectRef) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
            this->rejectRef = 0;
        }
        this->resolveRef = ref;
        //   this->rejectFunc = std::bind(&ScriptComponent::recvClusterResult, object, std::placeholders::_1, "recvClusterResult", ref);
        return this;
    }
    base_promise* Else(ScriptComponent* object, int ref) {
        if(this->rejectRef) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
            this->rejectRef = 0;
        }
        this->rejectRef = ref;
        //   this->rejectFunc = std::bind(&ScriptComponent::recvClusterResult, object, std::placeholders::_1, "recvClusterResult", ref);
        return this;
    }
public:
    void reject(TClient* client, TResult* result) {
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
    void resolve(TClient* client, TResult* result) {
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
protected:
    Coord*              coord;
    int                 resolveRef;
    int                 rejectRef;
    ResolveFunc         resolveFunc;
    RejectFunc          rejectFunc;
public:
    std::string         route;
    uint64_t            reqTime; 
private:
};

}


