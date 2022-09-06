#include "coord/http/http_router.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/component/script_component.h"
#include "coord/coord.h"
#include "coord/script/script.h"
#include "coord/coordx.h"

namespace coord {
namespace http {

RC_IMPLEMENT(HttpRouter, "coord::http::HttpRouter")


HttpRouter::http_router_handler::http_router_handler(Coord* coord, const std::string& path, HttpRouter_RecvHttpRequest recvHttpRequestFunc, int ref) {
    this->coord = coord;
    this->path = path;
    this->recvHttpRequestFunc = recvHttpRequestFunc;
    this->ref = ref;
    this->times = 0;
    this->consumeTime = 0;
}

HttpRouter::http_router_handler::~http_router_handler() {
    if(this->ref != LUA_NOREF) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
    }
}

void HttpRouter::http_router_handler::move(http_router_handler* handler) {
    if (nullptr == handler) {
        if(this->ref != LUA_NOREF) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        }
        this->ref = LUA_NOREF;
        this->recvHttpRequestFunc = nullptr;
    } else {
        if(this->ref != LUA_NOREF) {
            luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        }
        this->ref = handler->ref;
        this->recvHttpRequestFunc = handler->recvHttpRequestFunc;
    }
}

void HttpRouter::http_router_handler::recvHttpRequest(HttpRequest* request) {
    if(this->recvHttpRequestFunc != nullptr){
        this->recvHttpRequestFunc(request);
    } 
} 

HttpRouter::HttpRouter(Coord* coord, HttpServer* server){
    this->coord = coord;
    this->server = server;
}

HttpRouter::~HttpRouter(){

}

HttpRouter::http_router_handler* HttpRouter::searchHandler(const char* method, const char* path) {
    auto it = this->trees.find(method);
    if (it == this->trees.end()) {
        return nullptr;
    }
    r3::Tree* tree = it->second;
    r3::MatchEntry entry(path);
    r3::Node node = tree->match_entry(entry);
    if (node.is_null()) {
        return nullptr;
    }
    return (http_router_handler*)node.data();
}

bool HttpRouter::IsMatch(const char* method, const char* path) {
    auto handler = this->searchHandler(method, path);
    return handler != nullptr;
}
const char* HttpRouter::Match(const char* method, const char* path) {
    auto handler = this->searchHandler(method, path);
    if (nullptr == handler) {
        return nullptr;
    } else {
        return handler->path.c_str();
    }
}

void HttpRouter::recvHttpRequest(HttpRequest* request) {
    if (strcmp(request->Method.c_str(), "OPTIONS") == 0) {
        request->GetResponse()->Allow();
        return;
    }
    http_router_handler* handler = this->searchHandler(request->Method.c_str(), request->Path.c_str());
    if(handler == nullptr){
        throw HttpPageNotFoundException(request->Path.c_str());
        return;
    }
    handler->recvHttpRequest(request);
}

void HttpRouter::Trace() {
    for(auto const& it : this->methodDict){
        for(auto const& it1 : it.second) {
            this->trace(it.first.c_str(), it1.second);
        }
    }
    for(auto const& it : this->trees){
        it.second->dump(0);
    }
}

void HttpRouter::trace(const char* method, http_router_handler* handler) {
    uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
    this->coord->LogDebug("[HttpRouter] %10s | %10d | %10s | %s",  method, handler->times, coordx::date::FormatNano(averageTime), handler->path.c_str());
}

bool HttpRouter::Get(const char* path, HttpRouter_RecvHttpRequest func){
    HttpRouter::http_router_handler* handler = new http_router_handler(this->coord, path, func);
    return this->addRoute("GET", path, handler);
}
 
bool HttpRouter::Get(const char* path, ScriptComponent* object, int ref) {
    HttpRouter::http_router_handler* handler = new http_router_handler(this->coord, path, std::bind(&ScriptComponent::recvHttpRequest, object, std::placeholders::_1, ref), ref);
    return this->addRoute("GET", path, handler);
}
 
bool HttpRouter::Post(const char* path, HttpRouter_RecvHttpRequest func){
    HttpRouter::http_router_handler* handler = new http_router_handler(this->coord, path, func);
    return this->addRoute("POST", path, handler);
}

bool HttpRouter::Post(const char* path, ScriptComponent* object, int ref) {
    HttpRouter::http_router_handler* handler = new http_router_handler(this->coord, path, std::bind(&ScriptComponent::recvHttpRequest, object, std::placeholders::_1, ref), ref);
    return this->addRoute("POST", path, handler);
}

bool HttpRouter::Static(const char* path, const char* dir) {
    HttpRouter::http_router_handler* handler = new http_router_handler(this->coord, path, std::bind(&HttpRouter::recvStaticRequest, this, std::placeholders::_1, dir));
    return this->addRoute("GET", path, handler);
}

bool HttpRouter::StaticFile(const char* path, const char* filePath) {
    http_router_handler* handler = new http_router_handler(this->coord, path, std::bind(&HttpRouter::recvStaticFileRequest, this, std::placeholders::_1, filePath));
    return this->addRoute("GET", path, handler);
}

int HttpRouter::Get(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,this->TypeName(),0,&tolua_err) ||
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
                tolua_error(L, "error in function 'Get'.\nattempt to set a nil function", nullptr);
                return 0;
            }
            bool result = this->Get(route, object, ref);
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
                char* c = nullptr;
                for(char* i = fullRoute; *i != 0; i++) {
                    if(*i == '.') {
                        c = i + 1;
                    } else if (c != nullptr) {
                        *i = tolower(*i);
                    }
                }
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                if(tolua_isfunction(L,-1,0,&tolua_err)) {
                    int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
                    if (ref < 0) {
                        return 0;
                    }
                    bool result = this->Get(fullRoute, object, ref);
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
    tolua_error(L,"#ferror in function 'Get'.",&tolua_err);
    return 0;
#endif
}

int HttpRouter::Post(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,this->TypeName(),0,&tolua_err) ||
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
                tolua_error(L, "error in function 'Post'.\nattempt to set a nil function", nullptr);
                return 0;
            }
            bool result = this->Post(route, object, ref);
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
                char* c = nullptr;
                for(char* i = fullRoute; *i != 0; i++) {
                    if(*i == '.') {
                        c = i + 1;
                    } else if (c != nullptr) {
                        *i = tolower(*i);
                    }
                }
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                if(tolua_isfunction(L,-1,0,&tolua_err)) {
                    int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
                    if (ref < 0) {
                        return 0;
                    }
                    bool result = this->Post(fullRoute, object, ref);
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
    tolua_error(L,"#ferror in function 'Post'.",&tolua_err);
    return 0;
#endif
}

void HttpRouter::recvStaticRequest(const HttpRequestRef& request, const char* dir) {
    std::string realPath = coordx::path::PathJoin(dir, request->Path);
    realPath = coordx::path::PathJoin(this->server->config.AssetDir, realPath);
    request->GetResponse()->File(realPath.c_str());
}

void HttpRouter::recvStaticFileRequest(const HttpRequestRef& request, const char* filePath) {
    std::string realPath = coordx::path::PathJoin(this->server->config.AssetDir, filePath);
    request->GetResponse()->File(realPath.c_str());
}

bool HttpRouter::addRoute(const char* method, const char* path, http_router_handler* handler) {
    this->coord->CoreLogDebug("[HttpRouter] addRoute, method=%s, path=%s", method, path);
    r3::Tree* tree = this->getMethodTree(method);
    if (nullptr == tree) {
        return false;
    }
    const auto& it1 = this->methodDict.find(method);
    if (it1 == this->methodDict.end()) {
        return false;
    }
    auto handlerDict = it1->second;
    auto it = handlerDict.find(path);
    http_router_handler* lastHandler = nullptr;
    if (it != handlerDict.end()) {
        lastHandler = it->second;
    }
    if (nullptr == lastHandler) {
        if (nullptr == handler) {
            return false;
        } else {
            char *errstr;
            r3::Node node = tree->insert_path(path, handler, &errstr);
            if (node.is_null()) {
                return false;
            }
            handlerDict[path] = handler;
            return true;
        }
    } else {
        if (nullptr == handler) {
            lastHandler->move(nullptr);
            return true;
        } else {
            lastHandler->move(handler);
            delete handler;
            return true;
        }
    }
    return true;
} 

r3::Tree* HttpRouter::getMethodTree(const char* method) {
    auto it = this->trees.find(method);
    if (it == this->trees.end()) {
        r3::Tree* tree = new r3::Tree(10);
        if (nullptr == tree) {
            return nullptr;
        }
        this->trees[method] = tree;
        this->methodDict[method] = std::map<std::string, http_router_handler*>();
        return tree;
    } else {
        return it->second;
    }
}



}
}  
