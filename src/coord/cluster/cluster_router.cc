#include "coord/cluster/cluster_router.h"
#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_notify.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_response.h"
#include "coord/component/script_component.h"
#include "coord/coordx.h"
#include "coord/script/script.h"
#include "coord/coord.h"

namespace coord {
namespace cluster {

CC_IMPLEMENT(ClusterRouter, "coord::cluster::ClusterRouter")

ClusterRouter* newClusterRouter(Coord* coord) {
    ClusterRouter* router = new ClusterRouter(coord);
    return router;
}

cluster_router_handler::~cluster_router_handler() {
    if(this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = 0;
    }
}

void cluster_router_handler::recvClusterRequest(Request* request) {
    if(this->recvClusterRequestFunc != nullptr){
        this->recvClusterRequestFunc(request);
    } 
} 

void cluster_router_handler::recvClusterNotify(GateNotify* notify) {
    if(this->recvClusterNotifyFunc != nullptr){
        this->recvClusterNotifyFunc(notify);
    } 
} 

ClusterRouter::ClusterRouter(Coord* coord){
    this->coord = coord;
}

ClusterRouter::~ClusterRouter(){

}

cluster_router_handler* ClusterRouter::searchHandler(const char* event, const char* route) {
    cluster_router_tree* tree = this->getTree(event);
    auto it = tree->handlerDict.find(route);
    if (it == tree->handlerDict.end()){
        return NULL;
    } 
    return it->second;
}

void ClusterRouter::recvClusterNotify(cluster::GateNotify* notify) {
    this->coord->CoreLogDebug("[ClusterRouter] recvClusterNotify");
    cluster_router_handler* handler = this->searchHandler("NOTIFY", notify->Route.c_str());
    if(handler == NULL){
        this->coord->CoreLogDebug("[ClusterRouter] recvClusterNotify failed, error='router not found', path=%s", notify->Route.c_str());
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvClusterNotify(notify);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
} 

void ClusterRouter::recvClusterRequest(cluster::Request* request) {
    this->coord->CoreLogDebug("[ClusterRouter] recvClusterRequest");
    cluster_router_handler* handler = this->searchHandler("REQUEST", request->Route.c_str());
    if(handler == NULL){
        this->coord->CoreLogDebug("[ClusterRouter] recvClusterRequest failed, error='router not found', path=%s", request->Route.c_str());
        Response* response = request->GetResponse();
        response->String("Not Found");
        response->Reject(404);
    } else {
        uint64_t t1 = this->coord->NanoTime();
        handler->recvClusterRequest(request);
        handler->times++;
        handler->consumeTime += (this->coord->NanoTime() - t1);
    }
}

void ClusterRouter::Trace() {
    for(auto const& it : this->trees){
        auto event = it.first;
        auto tree = it.second;
        for(auto const& it1 : tree->handlerDict) {
            auto handler = it1.second;
            uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
            this->coord->CoreLogDebug("[ClusterRouter] %10s | %10d | %10s | %s", event.c_str(), handler->times, coordx::date::FormatNano(averageTime), it1.first.c_str());
        }
    }
}

bool ClusterRouter::Request(const char* route, ClusterRouter_RecvClusterRequest func){
    if(func == NULL) {
        return this->addRoute("REQUEST", route, NULL);
    } else {
        cluster_router_handler* handler = new cluster_router_handler(this->coord, func);
        return this->addRoute("REQUEST", route, handler);
    }
}

bool ClusterRouter::Request(const char* route, ScriptComponent* object, int ref) {
    if(object == NULL) {
        return this->addRoute("REQUEST", route, NULL);
    } else {
        cluster_router_handler* handler = new cluster_router_handler(this->coord, std::bind(&ScriptComponent::recvClusterRequest, object, std::placeholders::_1, "recvClusterRequest", ref), ref);
        return this->addRoute("REQUEST", route, handler);
    }
}

int ClusterRouter::Request(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::cluster::ClusterRouter",0,&tolua_err) ||
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
        bool result = this->Request(route, object, ref);
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

bool ClusterRouter::Notify(const char* path, ClusterRouter_RecvClusterNotify func){
    if(func == NULL) {
        return this->addRoute("NOTIFY", path, NULL);
    } else {
        cluster_router_handler* handler = new cluster_router_handler(this->coord, func);
        return this->addRoute("NOTIFY", path, handler);
    }
}

bool ClusterRouter::Notify(const char* path, ScriptComponent* object, int ref) {
    if(object == NULL) {
        return this->addRoute("NOTIFY", path, NULL);
    } else {
        cluster_router_handler* handler = new cluster_router_handler(this->coord, std::bind(&ScriptComponent::recvClusterNotify, object, std::placeholders::_1, "recvClusterNotify", ref), ref);
        return this->addRoute("NOTIFY", path, handler);
    }
}

int ClusterRouter::Notify(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::cluster::ClusterRouter",0,&tolua_err) ||
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
        bool result = this->Notify(route, object, ref);
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

bool ClusterRouter::addRoute(const char* event, const char* route, cluster_router_handler* handler) {
    cluster_router_tree* tree = this->getTree(event);
    //this->coord->CoreLogDebug("[ClusterRouter] add route, event=%-10s, route=%-64s, handler=0x%x", event, route, handler);
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

cluster_router_tree* ClusterRouter::getTree(const char* event) {
    const auto it = this->trees.find(event);
    if (it == this->trees.end()){
        cluster_router_tree* tree = new cluster_router_tree();
        this->trees[event] = tree;
        return tree;
    } else {
        return it->second;
    }
}



}
}  
