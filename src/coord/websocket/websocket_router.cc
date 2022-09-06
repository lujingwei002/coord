#include "coord/websocket/websocket_router.h"
#include "coord/websocket/websocket_agent.h"
#include "coord/websocket/websocket_server.h"
#include "coord/websocket/websocket_frame.h"
#include "coord/component/script_component.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include "coord/coordx.h"

namespace coord {
namespace websocket {

RC_IMPLEMENT(Router, "coord::websocket::Router")

Router* newRouter(Coord* coord) {
    Router* webSocketRouter = new Router(coord);
    return webSocketRouter;
}

router_handler::~router_handler() {
    if(this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = 0;
    }
}

void router_handler::recvWebSocketNew(Agent* agent) {
    if(this->recvWebSocketNewFunc != nullptr){
        this->recvWebSocketNewFunc(agent);
    } 
} 

void router_handler::recvWebSocketClose(Agent* agent) {
    if(this->recvWebSocketNewFunc != nullptr){
        this->recvWebSocketNewFunc(agent);
    } 
} 

void router_handler::recvWebSocketFrame(Agent* agent, Frame* frame) {
    if(this->recvWebSocketFrameFunc != nullptr){
        this->recvWebSocketFrameFunc(agent, frame);
    }
} 

Router::Router(Coord* coord){
    this->coord = coord;
}

Router::~Router(){

}

router_handler* Router::searchHandler(const char* event, const char* route) {
    router_tree* tree = this->getTree(event);
    auto it = tree->handlerDict.find(route);
    if (it == tree->handlerDict.end()){
        return nullptr;
    } 
    return it->second;
}

void Router::recvWebSocketFrame(Agent* agent, Frame* frame) {
    this->coord->CoreLogDebug("[websocket::Router] recvWebSocketFrame %s", frame->payload);
    router_handler* handler = this->searchHandler("MESSAGE", "/hello");
    if(handler == nullptr){
        this->coord->CoreLogDebug("[websocket::Router] recvWebSocketFrame failed, error='router not found', path=%s", "/hello");
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvWebSocketFrame(agent, frame);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}


void Router::recvWebSocketNew(Agent* agent){
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[websocket::Router] recvWebSocketNew, sessionId=%d", sessionId);
}

void Router::recvWebSocketClose(Agent* agent){
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[websocket::Router] recvWebSocketClose, sessionId=%d", sessionId);
}

void Router::Trace() {
    for(auto const& it : this->trees){
        auto event = it.first;
        auto tree = it.second;
        for(auto const& it1 : tree->handlerDict) {
            auto handler = it1.second;
            uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
            this->coord->CoreLogDebug("[websocket::Router] %10s | %10d | %10s | %s", event.c_str(), handler->times, coordx::date::FormatNano(averageTime), it1.first.c_str());
        }
    }
}

bool Router::Message(const char* route, RecvWebSocketFrameFunc func){
    if(func == NULL) {
        return this->addRoute("MESSAGE", route, NULL);
    } else {
        router_handler* handler = new router_handler(this->coord, func);
        return this->addRoute("MESSAGE", route, handler);
    }
}

bool Router::Message(const char* route, ScriptComponent* object, int ref) {
    if(object == NULL) {
        return this->addRoute("MESSAGE", route, NULL);
    } else {
        router_handler* handler = new router_handler(this->coord, std::bind(&ScriptComponent::recvWebSocketFrame, object, std::placeholders::_1, std::placeholders::_2, "recvWebSocketFrame", ref), ref);
        return this->addRoute("MESSAGE", route, handler);
    }
}

int Router::Message(lua_State* L) {
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
            tolua_error(L, "error in function 'Message'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->Message(route, object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Message'.",&tolua_err);
    return 0;
#endif
}

bool Router::addRoute(const char* event, const char* route, router_handler* handler) {
    router_tree* tree = this->getTree(event);
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

router_tree* Router::getTree(const char* event) {
    const auto it = this->trees.find(event);
    if (it == this->trees.end()){
        router_tree* tree = new router_tree();
        this->trees[event] = tree;
        return tree;
    } else {
        return it->second;
    }
}

}
}  
