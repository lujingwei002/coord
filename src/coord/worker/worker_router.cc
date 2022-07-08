#include "coord/worker/worker_router.h"
#include "coord/worker/worker.h"
#include "coord/worker/worker_request.h"
#include "coord/worker/worker_response.h"
#include "coord/worker/worker_notify.h"
#include "coord/component/script_component.h"
#include "util/date/date.h"
#include "coord/coord.h"

namespace coord {
namespace worker {
CC_IMPLEMENT(WorkerRouter, "coord::worker::WorkerRouter")

WorkerRouter* newWorkerRouter(Coord* coord) {
    WorkerRouter* router = new WorkerRouter(coord);
    return router;
}

worker_router_handler::~worker_router_handler() {
    if(this->ref) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = 0;
    }
}

void worker_router_handler::recvWorkerRequest(Request* request) {
    if(this->recvWorkerRequestFunc != NULL){
        this->recvWorkerRequestFunc(request);
    } 
} 

void worker_router_handler::recvWorkerNotify(Notify* notify) {
    if(this->recvWorkerNotifyFunc != NULL){
        this->recvWorkerNotifyFunc(notify);
    } 
} 

WorkerRouter::WorkerRouter(Coord* coord){
    this->coord = coord;
}

WorkerRouter::~WorkerRouter(){

}

worker_router_handler* WorkerRouter::searchHandler(const char* event, const char* route) {
    worker_router_tree* tree = this->getTree(event);
    auto it = tree->handlerDict.find(route);
    if (it == tree->handlerDict.end()){
        return NULL;
    } 
    return it->second;
}

void WorkerRouter::recvWorkerRequest(worker::Request* request) {
    this->coord->CoreLogDebug("[WorkerRouter] recvWorkerRequest");
    worker_router_handler* handler = this->searchHandler("REQUEST", request->route.c_str());
    if(handler == NULL){
        this->coord->CoreLogDebug("[WorkerRouter] recvWorkerRequest failed, error='router not found', route=%s", request->route.c_str());
        Response* response = request->GetResponse();
        response->String("Not Found");
        response->Reject(404);
    } else {
        uint64_t t1 = this->coord->NanoTime();
        handler->recvWorkerRequest(request);
        handler->times++;
        handler->consumeTime += (this->coord->NanoTime() - t1);
    }
}

void WorkerRouter::recvWorkerNotify(worker::Notify* notify) {
    this->coord->CoreLogDebug("[WorkerRouter] recvWorkerNotify");
    worker_router_handler* handler = this->searchHandler("NOTIFY", notify->route.c_str());
    if(handler == NULL){
        this->coord->CoreLogDebug("[WorkerRouter] recvWorkerNotify failed, error='router not found', route=%s", notify->route.c_str());
    } else {
        uint64_t t1 = this->coord->NanoTime();
        handler->recvWorkerNotify(notify);
        handler->times++;
        handler->consumeTime += (this->coord->NanoTime() - t1);
    }
}

void WorkerRouter::Trace() {
    for(auto const& it : this->trees){
        auto event = it.first;
        auto tree = it.second;
        for(auto const& it1 : tree->handlerDict) {
            auto handler = it1.second;
            uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
            this->coord->CoreLogDebug("[WorkerRouter] %10s | %10d | %10s | %s", event.c_str(), handler->times, date::FormatNano(averageTime), it1.first.c_str());
        }
    }
}

bool WorkerRouter::Request(const char* route, RecvRequestFunc func){
    if(func == NULL) {
        return this->addRoute("REQUEST", route, NULL);
    } else {
        worker_router_handler* handler = new worker_router_handler(this->coord, func);
        return this->addRoute("REQUEST", route, handler);
    }
}

bool WorkerRouter::request(const char* route, ScriptComponent* object, int ref) {
    if(object == NULL) {
        return this->addRoute("REQUEST", route, NULL);
    } else {
        worker_router_handler* handler = new worker_router_handler(this->coord, std::bind(&ScriptComponent::recvWorkerRequest, object, std::placeholders::_1, "recvWorkerRequest", ref), ref);
        return this->addRoute("REQUEST", route, handler);
    }
}

int WorkerRouter::Request(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::worker::WorkerRouter",0,&tolua_err) ||
        !tolua_isstring(L,2,0,&tolua_err) ||
        !tolua_isusertype(L,3,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isfunction(L,4,0,&tolua_err) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        const char* route = (const char*) tolua_tostring(L, 2, 0);
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,3,0));
        lua_pushvalue(L, 4);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Request'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->request(route, object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Request'.",&tolua_err);
    return 0;
#endif
}

bool WorkerRouter::Notify(const char* path, RecvNotifyFunc func){
    if(func == NULL) {
        return this->addRoute("NOTIFY", path, NULL);
    } else {
        worker_router_handler* handler = new worker_router_handler(this->coord, func);
        return this->addRoute("NOTIFY", path, handler);
    }
}

bool WorkerRouter::notify(const char* path, ScriptComponent* object, int ref) {
    if(object == NULL) {
        return this->addRoute("NOTIFY", path, NULL);
    } else {
        worker_router_handler* handler = new worker_router_handler(this->coord, std::bind(&ScriptComponent::recvWorkerNotify, object, std::placeholders::_1, "recvWorkerNotify", ref), ref);
        return this->addRoute("NOTIFY", path, handler);
    }
}

int WorkerRouter::Notify(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::worker::WorkerRouter",0,&tolua_err) ||
        !tolua_isstring(L,2,0,&tolua_err) ||
        !tolua_isusertype(L,3,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isfunction(L,4,0,&tolua_err) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        const char* route = (const char*) tolua_tostring(L, 2, 0);
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,3,0));
        lua_pushvalue(L, 4);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'Notify'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->notify(route, object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Notify'.",&tolua_err);
    return 0;
#endif
}

bool WorkerRouter::addRoute(const char* event, const char* route, worker_router_handler* handler) {
    worker_router_tree* tree = this->getTree(event);
    //this->coord->CoreLogDebug("[WorkerRouter] addRoute, event=%-10s, route=%-64s, handler=0x%x", event, route, handler);
    auto it = tree->handlerDict.find(route);
    if (it != tree->handlerDict.end()) {
        delete it->second;
        tree->handlerDict.erase(it);
        tree->handlerDict[route] = handler;
    } else {
        tree->handlerDict[route] = handler;
    }
    return true;
} 

worker_router_tree* WorkerRouter::getTree(const char* event) {
    const auto it = this->trees.find(event);
    if (it == this->trees.end()){
        worker_router_tree* tree = new worker_router_tree();
        this->trees[event] = tree;
        return tree;
    } else {
        return it->second;
    }
}



}
}  
