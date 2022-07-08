#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_async_client.h"
#include "coord/redis/redis_reply.h"
#include "coord/component/script_component.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"

namespace coord {
namespace redis {

CC_IMPLEMENT(Promise, "coord::redis::Promise")

Promise* newPromise(Coord* coord) {
    Promise* promise = new Promise(coord);
    return promise;
}

Promise::Promise(Coord *coord)  {
    this->coord = coord;
    this->resolveFunc = nullptr;
    this->rejectFunc = nullptr;
    this->resolveRef = 0;
    this->rejectRef = 0;
}

Promise::~Promise() {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
    }
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
    }
}

Promise* Promise::Then(PromiseResolveFunction func){
    this->resolveFunc = func;
    return this;    
} 

Promise* Promise::Else(PromiseRejectFunction func){
    this->rejectFunc = func;
    return this;    
} 

Promise* Promise::then(ScriptComponent* object, int ref) {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    this->resolveFunc = std::bind(&ScriptComponent::recvRedisReply, object, std::placeholders::_1, std::placeholders::_2, "recvRedisReply", ref);
    return this;   
}

Promise* Promise::else_(ScriptComponent* object, int ref) {
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->rejectRef = ref;
    this->rejectFunc = std::bind(&ScriptComponent::recvRedisReply, object, std::placeholders::_1, std::placeholders::_2, "recvRedisReply", ref);
    return this;   
}

int Promise::Then(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::redis::Promise",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isfunction(L,3,0,&tolua_err) ||
        !tolua_isnoobj(L,4,&tolua_err)
    )
        goto tolua_lerror;
    else {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        lua_pushvalue(L, 3);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Then'.\nattempt to set a nil function", NULL);
            return 0;
        }
        Promise* tolua_ret = (Promise*)  this->then(object, ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::redis::Promise");
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Then'.",&tolua_err);
    return 0;
}

int Promise::Else(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::redis::Promise",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isfunction(L,3,0,&tolua_err) ||
        !tolua_isnoobj(L,4,&tolua_err)
    )
        goto tolua_lerror;
    else {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        lua_pushvalue(L, 3);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Else'.\nattempt to set a nil function", NULL);
            return 0;
        }
        Promise* tolua_ret = (Promise*)  this->else_(object, ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::redis::Promise");
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Else'.",&tolua_err);
    return 0;
}

void Promise::resolve(AsyncClient* client, Reply& reply) {
    //this->coord->CoreLogDebug("[RedisPromise] resolve");
    if(this->resolveFunc == nullptr) {
        return;
    }
    try{
        //传递到逻辑层
        this->resolveFunc(client, reply);
    } catch(ScriptException& e){
    }
}

void Promise::reject(AsyncClient* client, Reply& reply){
    //this->coord->CoreLogDebug("[RedisPromise] reject");
    if(this->rejectFunc == nullptr) {
        return;
    }
    try{
        //传递到逻辑层
        this->rejectFunc(client, reply);
    } catch(ScriptException& e){
    }
}

void Promise::reject(AsyncClient* client, std::nullptr_t) {
    if(this->rejectFunc == nullptr) {
        return;
    }
    static thread_local Reply reply(nullptr);
    try{
        //传递到逻辑层
        this->rejectFunc(client, reply);
    } catch(ScriptException& e){
    }
}

void Promise::resolve(AsyncClient* client, std::nullptr_t) {
    if(this->resolveFunc == nullptr) {
        return;
    }
    static thread_local Reply reply(nullptr);
    try{
        //传递到逻辑层
        this->resolveFunc(client, reply);
    } catch(ScriptException& e){
    }
}

}
} 
