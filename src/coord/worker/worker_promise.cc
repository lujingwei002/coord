#include "coord/worker/worker_promise.h"
#include "coord/coord.h"
#include "coord/worker/worker.h"
#include "coord/worker/worker_slave.h"
#include "coord/component/script_component.h"
#include "coord/builtin/exception.h"
#include "coord/builtin/base_request.h"
namespace coord {

namespace worker {
CC_IMPLEMENT(Promise, "coord::worker::Promise")

Promise* newPromise(Coord* coord) {
    Promise* pomise = new Promise(coord);
    return pomise;
}

Promise::Promise(Coord* coord) {
    this->coord = coord;
    this->resolveFunc = nullptr;
    this->rejectFunc = nullptr;
    this->reqTime = uv_hrtime();
    this->resolveRef = 0;
    this->rejectRef = 0;
    this->requestUsing = nullptr;
}

Promise::~Promise() {
    this->coord->coreLogDebug("[worker::Promise] ~");
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
    }
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
    }
    if(this->requestUsing) {
        this->coord->Destory(this->requestUsing);
        this->requestUsing = nullptr;
    }
}

Promise* Promise::Then(PromiseResolveFunc resolveFunc){
    this->resolveFunc = resolveFunc;
    return this;    
} 

Promise* Promise::Else(PromiseRejectFunc rejectFunc){
    this->rejectFunc = rejectFunc;
    return this;
}

Promise* Promise::Using(BaseRequest* request) {
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

Promise* Promise::Then(ScriptComponent* object, int ref) {
    if(this->resolveRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->resolveRef);
        this->resolveRef = 0;
    }
    this->resolveRef = ref;
    this->resolveFunc = std::bind(&ScriptComponent::recvWorkerResult, object, std::placeholders::_1, std::placeholders::_2, "recvWorkerResult", ref);
    return this;   
}

Promise* Promise::Else(ScriptComponent* object, int ref) {
    if(this->rejectRef) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->rejectRef);
        this->rejectRef = 0;
    }
    this->rejectRef = ref;
    this->rejectFunc = std::bind(&ScriptComponent::recvWorkerResult, object, std::placeholders::_1, std::placeholders::_2, "recvWorkerResult", ref);
    return this;   
}

void Promise::resolve(Result* result) {
    //this->coord->coreLogDebug("[worker::Promise] resolve");
    if(this->resolveFunc == NULL) {
        this->coord->coreLogDebug("[worker::Promise] resolve failed, error='func not found'");
        return;
    }
    try{
        //printf("gggggggg %s\n", this->requestUsing->TypeName());
        //this->coord->recoverRequestPipeline(this->pipeline);
        //传递到逻辑层
        this->resolveFunc(result, this->requestUsing);
       // this->coord->popRequestPipeline();
    } catch(ScriptException& e){
    }
}

void Promise::reject(Result* result){
    //this->coord->coreLogDebug("[worker::Promise] reject");
    if(this->rejectFunc == NULL) {
        this->coord->coreLogDebug("[worker::Promise] reject failed, error='func not found'");
        return;
    }
    try{
       // this->coord->recoverRequestPipeline(this->pipeline);
        //传递到逻辑层
        this->rejectFunc(result, this->requestUsing);
        //this->coord->popRequestPipeline();
    } catch(ScriptException& e){
    }
}

int Promise::Then(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::worker::Promise",0,&tolua_err) ||
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
        Promise* tolua_ret = (Promise*)  this->Then(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::worker::Promise");
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Then'.",&tolua_err);
    return 0;
}

int Promise::Else(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::worker::Promise",0,&tolua_err) ||
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
        Promise* tolua_ret = (Promise*)  this->Else(object,ref);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::worker::Promise");
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Else'.",&tolua_err);
    return 0;
}

} 
}