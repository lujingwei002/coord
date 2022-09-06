#include "coord/gate/gate_router.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_request.h"
#include "coord/gate/gate_response.h"
#include "coord/gate/gate_notify.h"
#include "coord/gate/gate_session.h"
#include "coord/component/script_component.h"
#include "coord/coordx.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include <cstdio>

namespace coord {
namespace gate {

RC_IMPLEMENT(GateRouter, "coord::gate::GateRouter")

GateRouter* newGateRouter(Coord* coord) {
    GateRouter* gateRouter = new GateRouter(coord);
    return gateRouter;
}

gate_router_handler::~gate_router_handler() {
    if(this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
    }
}

void gate_router_handler::recvGateRequest(GateSession* session, GateRequest* request) {
    if(this->recvGateRequestFunc != NULL){
        this->recvGateRequestFunc(session, request);
    } 
} 

void gate_router_handler::recvGateAuth(GateSession* session, GateRequest* request) {
    if(this->recvGateRequestFunc != NULL){
        this->recvGateRequestFunc(session, request);
    } 
} 

void gate_router_handler::recvGateNotify(GateSession* session, GateNotify* notify) {
    if(this->recvGateNotifyFunc != NULL){
        this->recvGateNotifyFunc(session, notify);
    } 
} 

void gate_router_handler::recvGateSessionNew(GateSession* session) {
    if(this->recvGateSessionFunc != NULL){
        this->recvGateSessionFunc(session);
    } 
} 

void gate_router_handler::recvGateSessionClose(GateSession* session) {
    if(this->recvGateSessionFunc != NULL){
        this->recvGateSessionFunc(session);
    }
} 

void gate_router_handler::recvGateUserLogin(GateSession* session) {
    if(this->recvGateSessionFunc != NULL){
        this->recvGateSessionFunc(session);
    }
} 

void gate_router_handler::recvGateUserLogout(GateSession* session) {
    if(this->recvGateSessionFunc != NULL){
        this->recvGateSessionFunc(session);
    }
} 

void gate_router_handler::recvGateUserInstead(GateSession* session) {
    if(this->recvGateSessionFunc != NULL){
        this->recvGateSessionFunc(session);
    }
} 

GateRouter::GateRouter(Coord* coord){
    this->coord = coord;
}

GateRouter::~GateRouter(){

}

gate_router_handler* GateRouter::searchHandler(const char* event, const char* route) {
    gate_router_tree* tree = this->getTree(event);
    auto it = tree->handlerDict.find(route);
    if (it == tree->handlerDict.end()){
        return NULL;
    } 
    return it->second;
}

void GateRouter::recvGateNotify(GateSession* session, GateNotify* notify) {
    this->coord->CoreLogDebug("[GateRouter] recvGateNotify");
    gate_router_handler* handler = this->searchHandler("NOTIFY", notify->Route.c_str());
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateNotify failed, error='router not found', route=%s", notify->Route.c_str());
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateNotify(session, notify);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
} 

void GateRouter::recvGateRequest(GateSession* session, GateRequest* request) {
    if (!session->IsAuth()) {
        this->recvGateAuth(session, request);
        return;
    }
    this->coord->CoreLogDebug("[GateRouter] recvGateRequest");
    gate_router_handler* handler = this->searchHandler("REQUEST", request->Route.c_str());
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateRequest failed, error='router not found', route=%s", request->Route.c_str());
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateRequest(session, request);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::recvGateAuth(GateSession* session, GateRequest* request) {
    this->coord->CoreLogDebug("[GateRouter] recvGateAuth");
    gate_router_handler* handler = this->searchHandler("AUTH", request->Route.c_str());
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateAuth failed, error='router not found', route=%s", request->Route.c_str());
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateAuth(session, request);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::recvGateSessionNew(GateSession* session) {
    this->coord->CoreLogDebug("[GateRouter] recvGateSessionNew, sessionId=%ld", session->Id);
    gate_router_handler* handler = this->searchHandler("NEW", "*");
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateSessionNew failed, error='router not found'");
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateSessionNew(session);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::recvGateSessionClose(GateSession* session) {
    this->coord->CoreLogDebug("[GateRouter] recvGateSessionClose, sessionId=%ld", session->Id);
    gate_router_handler* handler = this->searchHandler("CLOSE", "*");
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateSessionClose failed, error='router not found'");
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateSessionClose(session);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::recvGateUserLogin(GateSession* session) {
    this->coord->CoreLogDebug("[GateRouter] recvGateUserLogin, sessionId=%ld", session->Id);
    gate_router_handler* handler = this->searchHandler("LOGIN", "*");
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateUserLogin failed, error='router not found'");
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateUserLogin(session);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::recvGateUserLogout(GateSession* session) {
    this->coord->CoreLogDebug("[GateRouter] recvGateUserLogout, sessionId=%ld", session->Id);
    gate_router_handler* handler = this->searchHandler("LOGOUT", "*");
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateUserLogout failed, error='router not found'");
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateUserLogout(session);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::recvGateUserInstead(GateSession* session) {
    this->coord->CoreLogDebug("[GateRouter] recvGateUserInstead, sessionId=%ld", session->Id);
    gate_router_handler* handler = this->searchHandler("INSTEAD", "*");
    if(handler == NULL){
        this->coord->CoreLogError("[GateRouter] recvGateUserInstead failed, error='router not found'");
        return;
    }
    uint64_t t1 = this->coord->NanoTime();
    handler->recvGateUserInstead(session);
    handler->times++;
    handler->consumeTime += (this->coord->NanoTime() - t1);
}

void GateRouter::Trace() {
    for(auto const& it : this->trees){
        auto event = it.first;
        auto tree = it.second;
        for(auto const& it1 : tree->handlerDict) {
            auto handler = it1.second;
            uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
            this->coord->LogDebug("[GateRouter] %10s | %10d | %10s | %s", 
                event.c_str(), handler->times, coordx::date::FormatNano(averageTime), it1.first.c_str());
        }
    }
}

bool GateRouter::Request(const char* path, GateRouter_RecvGateRequest func){
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("REQUEST", path, handler);
}

bool GateRouter::Request(const char* path, ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, std::bind(&ScriptComponent::recvGateRequest, object, std::placeholders::_1, std::placeholders::_2, "recvGateRequest", ref), ref);
    return this->addRoute("REQUEST", path, handler);
}

int GateRouter::Request(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
        !tolua_isstring(L,2,0,&tolua_err) ||
        !tolua_isusertype(L,3,"coord::ScriptComponent",0,&tolua_err) ||
        (!tolua_isfunction(L,4,0,&tolua_err) && !tolua_istable(L,4,0,&tolua_err)) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        const char* route = (const char*) tolua_tostring(L, 2, 0);
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,3,0));
        if(tolua_isfunction(L,4,0,&tolua_err)) {
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
        } else if(tolua_istable(L,4,0,&tolua_err)) {
            bool result = true;
            lua_pushnil(L);  /* first key */
            while (lua_next(L, 4) != 0) {
                static thread_local char fullRoute[128];
                snprintf(fullRoute, sizeof(fullRoute), "%s.%s", route, lua_tostring(L, -2));
                char* c = NULL;
                for(char* i = fullRoute; *i != 0; i++) {
                    if(*i == '.') {
                        c = i + 1;
                    } else if (c != NULL) {
                        *i = tolower(*i);
                    }
                }
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                if(tolua_isfunction(L,-1,0,&tolua_err)) {
                    int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
                    if (ref < 0) {
                        return 0;
                    }
                    bool result = this->Request(fullRoute, object, ref);
                    if(!result) {
                        luaL_unref(L, LUA_REGISTRYINDEX, ref);
                    }
                } else {
                    /* removes 'value'; keeps 'key' for next iteration */
                    lua_pop(L, 1);
                }
            }
            tolua_pushboolean(L, result);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Request'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::Notify(const char* path, GateRouter_RecvGateNotify func){
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("NOTIFY", path, handler);
}

bool GateRouter::Notify(const char* path, ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, std::bind(&ScriptComponent::recvGateNotify, object, std::placeholders::_1, std::placeholders::_2, "recvGateNotify", ref), ref);
    return this->addRoute("NOTIFY", path, handler);
}

int GateRouter::Notify(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
        !tolua_isstring(L,2,0,&tolua_err) ||
        !tolua_isusertype(L,3,"coord::ScriptComponent",0,&tolua_err) ||
        (!tolua_isfunction(L,4,0,&tolua_err) && !tolua_istable(L,4,0,&tolua_err)) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else
#endif
    {
        const char* route = (const char*) tolua_tostring(L, 2, 0);
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,3,0));
        if(tolua_isfunction(L,4,0,&tolua_err)) {
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
        } else if(tolua_istable(L,4,0,&tolua_err)) {
            bool result = true;
            lua_pushnil(L);  /* first key */
            while (lua_next(L, 4) != 0) {
                static thread_local char fullRoute[128];
                snprintf(fullRoute, sizeof(fullRoute), "%s.%s", route, lua_tostring(L, -2));
                char* c = NULL;
                for(char* i = fullRoute; *i != 0; i++) {
                    if(*i == '.') {
                        c = i + 1;
                    } else if (c != NULL) {
                        *i = tolower(*i);
                    }
                }
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                if(tolua_isfunction(L,-1,0,&tolua_err)) {
                    int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
                    if (ref < 0) {
                        return 0;
                    }
                    bool result = this->Notify(fullRoute, object, ref);
                    if(!result) {
                        luaL_unref(L, LUA_REGISTRYINDEX, ref);
                    }
                } else {
                    /* removes 'value'; keeps 'key' for next iteration */
                    lua_pop(L, 1);
                }
            }
            tolua_pushboolean(L, result);
        }
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Notify'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::SessionNew(GateRouter_RecvGateSession func) {
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("NEW", "*", handler);
}

bool GateRouter::SessionNew(ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, (GateRouter_RecvGateSession)std::bind(&ScriptComponent::recvGateSession, object, std::placeholders::_1, "recvGateSessionNew", ref), ref);
    return this->addRoute("NEW", "*", handler);
}

int GateRouter::SessionNew(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
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
            tolua_error(L, "error in function 'SessionNew'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->SessionNew(object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'SessionNew'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::SessionClose(GateRouter_RecvGateSession func) {
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("CLOSE", "*", handler);
}

bool GateRouter::SessionClose(ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, (GateRouter_RecvGateSession)std::bind(&ScriptComponent::recvGateSession, object, std::placeholders::_1, "recvGateSessionClose", ref), ref);
    return this->addRoute("CLOSE", "*", handler);
}

int GateRouter::SessionClose(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
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
            tolua_error(L, "error in function 'SessionClose'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->SessionClose(object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'SessionClose'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::Login(GateRouter_RecvGateSession func) {
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("LOGIN", "*", handler);
}

bool GateRouter::Login(ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, (GateRouter_RecvGateSession)std::bind(&ScriptComponent::recvGateSession, object, std::placeholders::_1, "recvGateUserLogin", ref), ref);
    return this->addRoute("LOGIN", "*", handler);
}

int GateRouter::Login(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
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
            tolua_error(L, "error in function 'Login'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->Login(object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Login'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::Logout(GateRouter_RecvGateSession func) {
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("LOGOUT", "*", handler);
}

bool GateRouter::Logout(ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, (GateRouter_RecvGateSession)std::bind(&ScriptComponent::recvGateSession, object, std::placeholders::_1, "recvGateUserLogout", ref), ref);
    return this->addRoute("LOGOUT", "*", handler);
}

int GateRouter::Logout(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
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
            tolua_error(L, "error in function 'Logout'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->Logout(object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Logout'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::Instead(GateRouter_RecvGateSession func) {
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("INSTEAD", "*", handler);
}

bool GateRouter::Instead(ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, (GateRouter_RecvGateSession)std::bind(&ScriptComponent::recvGateSession, object, std::placeholders::_1, "recvGateUserInstead", ref), ref);
    return this->addRoute("INSTEAD", "*", handler);
}

int GateRouter::Instead(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
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
            tolua_error(L, "error in function 'Instead'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->Instead(object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Instead'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::Auth(const char* path, GateRouter_RecvGateRequest func){
    gate_router_handler* handler = new gate_router_handler(this->coord, func);
    return this->addRoute("AUTH", path, handler);
}

bool GateRouter::Auth(const char* path, ScriptComponent* object, int ref) {
    gate_router_handler* handler = new gate_router_handler(this->coord, std::bind(&ScriptComponent::recvGateRequest, object, std::placeholders::_1, std::placeholders::_2, "recvGateAuth", ref), ref);
    return this->addRoute("AUTH", path, handler);
}

int GateRouter::Auth(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::gate::GateRouter",0,&tolua_err) ||
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
            tolua_error(L, "error in function 'Auth'.\nattempt to set a nil function", NULL);
            return 0;
        }
        bool result = this->Auth(route, object, ref);
        if(!result) {
            luaL_unref(L, LUA_REGISTRYINDEX, ref);
        }
        tolua_pushboolean(L, result);
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Auth'.",&tolua_err);
    return 0;
#endif
}

bool GateRouter::addRoute(const char* event, const char* route, gate_router_handler* handler) {
    gate_router_tree* tree = this->getTree(event);
    //this->coord->CoreLogDebug("[GateRouter] add route, event=%-10s, route=%-64s, handler=0x%x", event, route, handler);
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

gate_router_tree* GateRouter::getTree(const char* event) {
    const auto it = this->trees.find(event);
    if (it == this->trees.end()){
        gate_router_tree* tree = new gate_router_tree();
        this->trees[event] = tree;
        return tree;
    } else {
        return it->second;
    }
}



}
}  
