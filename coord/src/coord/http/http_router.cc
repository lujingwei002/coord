#include "coord/http/http_router.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/component/script_component.h"
#include "coord/coord.h"
#include "util/os/path.h"
#include "util/date/date.h"

namespace coord {
namespace http {

CC_IMPLEMENT(HttpRouter, "coord::http::HttpRouter")

HttpRouter* newHttpRouter(Coord* coord, HttpServer* server) {
    HttpRouter* httpRouter = new HttpRouter(coord, server);
    return httpRouter;
}

http_router_handler::~http_router_handler() {
    if(this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
    }
}

void http_router_handler::recvHttpRequest(HttpRequest* request) {
    if(this->recvHttpRequestFunc != NULL){
        this->recvHttpRequestFunc(request);
    } 
} 

HttpRouter::HttpRouter(Coord* coord, HttpServer* server){
    this->coord = coord;
    this->server = server;
}

HttpRouter::~HttpRouter(){

}

HttpRouteNode* HttpRouter::searchNode(HttpRouteNode* root, int i, int argc, const char** argv) {
    const char* word = argv[i];
    if (root->path[0] == ':' && *word != 0) {
        if (root->nodeArr.size() <= 0 && i >= argc - 1 && root->handler != NULL) {
            return root;
        }
    } else if (root->path[0] == '*') {
        if (root->nodeArr.size() <= 0) {
            return root;
        }
    } else if (strcmp(root->path.c_str(), argv[i]) == 0) {
        if (i >= argc - 1 && root->handler != NULL) {
            return root;
        }
    } 
    if (i >= argc - 1) {
        return NULL;
    }
    word = argv[i + 1];
    HttpRouteNode* node = NULL;
    auto const it = root->nodeDict.find(word);
    if (it != root->nodeDict.end()) {
        node = this->searchNode(it->second, i + 1, argc, argv);
        if (node) {
            return node;
        }
    }
    if (root->requiredNode) {
        node = this->searchNode(root->requiredNode, i + 1, argc, argv);
        if (node) {
            return node;
        }
    }
    if (root->optionalNode) {
        node = this->searchNode(root->optionalNode, i + 1, argc, argv);
        if (node) {
            return node;
        }
    }
    return NULL;
}

HttpRouteNode* HttpRouter::searchNode(const char* method, const char* url) {
    RouterMethodTree* methodTree = this->getMethodTree(method);
    static thread_local int argc = 0;
    static thread_local const char* argv[16];
    static char buffer[1024];
    strncpy(buffer, url, sizeof(buffer));
    //非法的路径
    if (*buffer == 0 || buffer[0] != '/') {
        return NULL;
    }
    //  /a/b拆分成a和b  /a/b/拆分成a和b和空白
    argv[0] = buffer + 1;
    argc = 1;
    for (char *c = (char*)buffer + 1; *c != 0; c++) {
        if (*c == '/') {
            *c = 0;
            argv[argc] = c + 1;
            argc++;
            if (argc >= 16) {
                return NULL;
            }
        } 
    }
    const char* word = argv[0];
    HttpRouteNode* node = NULL;
    HttpRouteNode* root = methodTree->root;
    auto const it = root->nodeDict.find(word);
    if (it != root->nodeDict.end()) {
        node = this->searchNode(it->second, 0, argc, argv);
        if (node) {
            return node;
        }
    }
    if (root->requiredNode) {
        node = this->searchNode(root->requiredNode, 0, argc, argv);
        if (node) {
            return node;
        }
    }
    if (root->optionalNode) {
        node = this->searchNode(root->optionalNode, 0, argc, argv);
        if (node) {
            return node;
        }
    }
    return node;
}

http_router_handler* HttpRouter::searchHandler(const char* group, const char* url) {
    HttpRouteNode* node = this->searchNode(group, url);
    if (!node) {
        return NULL;
    }
    return node->handler;
}

void HttpRouter::recvHttpRequest(HttpRequest* request) {
    if (strcmp(request->Method.c_str(), "OPTIONS") == 0) {
        request->GetResponse()->Allow();
        return;
    }
    http_router_handler* handler = this->searchHandler(request->Method.c_str(), request->Path.c_str());
    if(handler == NULL){
        throw HttpPageNotFoundException(request->Path.c_str());
        return;
    }
    handler->recvHttpRequest(request);
}

void HttpRouter::Trace() {
    for(auto const it : this->trees){
        auto event = it.first;
        auto tree = it.second;
        for(auto const it1 : tree->root->nodeArr) {
            this->trace(event.c_str(), it1);
        }
    }
}

void HttpRouter::trace(const char* event, HttpRouteNode* node) {
    auto handler = node->handler;
    if (handler != NULL){
        uint64_t averageTime = handler->times <= 0 ? 0 : (handler->consumeTime/handler->times);
        this->coord->LogDebug("[HttpRouter] %10s | %10d | %10s | %s",  event, handler->times, date::FormatNano(averageTime), node->fullPath.c_str());

    }
    for(auto const it : node->nodeArr) {
        this->trace(event, it);
    }
}

bool HttpRouter::Get(const char* path, HttpRouter_RecvHttpRequest func){
    http_router_handler* handler = new http_router_handler(this->coord, func);
    return this->addRoute("GET", path, handler);
}
 
bool HttpRouter::Get(const char* path, ScriptComponent* object, int ref) {
    http_router_handler* handler = new http_router_handler(this->coord, std::bind(&ScriptComponent::recvHttpRequest, object, std::placeholders::_1, ref), ref);
    return this->addRoute("GET", path, handler);
}
 
bool HttpRouter::Post(const char* path, HttpRouter_RecvHttpRequest func){
    http_router_handler* handler = new http_router_handler(this->coord, func);
    return this->addRoute("POST", path, handler);
}

bool HttpRouter::Post(const char* path, ScriptComponent* object, int ref) {
    http_router_handler* handler = new http_router_handler(this->coord, std::bind(&ScriptComponent::recvHttpRequest, object, std::placeholders::_1, ref), ref);
    return this->addRoute("POST", path, handler);
}

bool HttpRouter::Static(const char* url, const char* dir) {
    http_router_handler* handler = new http_router_handler(this->coord, std::bind(&HttpRouter::recvStaticRequest, this, std::placeholders::_1, dir));
    return this->addRoute("GET", url, handler);
}

bool HttpRouter::StaticFile(const char* url, const char* path) {
    http_router_handler* handler = new http_router_handler(this->coord, std::bind(&HttpRouter::recvStaticFileRequest, this, std::placeholders::_1, path));
    return this->addRoute("GET", url, handler);
}

int HttpRouter::Get(lua_State* L) {
#ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::http::HttpRouter",0,&tolua_err) ||
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
                tolua_error(L, "error in function 'Get'.\nattempt to set a nil function", NULL);
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
        !tolua_isusertype(L,1,"coord::http::HttpRouter",0,&tolua_err) ||
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
                tolua_error(L, "error in function 'Post'.\nattempt to set a nil function", NULL);
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

void HttpRouter::recvStaticRequest(HttpRequest* request, const char* dir) {
    std::string path = dir;
    path = os::path::Join(path, request->Path);
    path = os::path::Join(this->server->config.AssetDir, path);
    request->GetResponse()->File(path.c_str());
}

void HttpRouter::recvStaticFileRequest(HttpRequest* request, const char* dir) {
    std::string path = dir;
    path = os::path::Join(this->server->config.AssetDir, path);
    request->GetResponse()->File(path.c_str());
}

bool HttpRouter::addRoute(const char* method, const char* path, http_router_handler* handler) {
    RouterMethodTree* methodTree = this->getMethodTree(method);
    this->coord->coreLogDebug("[HttpRouter] addRoute, method=%s, path=%s", method, path);
    HttpRouteNode* node = methodTree->root;
    int pathLen = strlen(path);

    if(pathLen == 0){
        return false;
    } else if(path[0] != '/') {
        return false;
    } else {
        int wordStart = 1;
        int wordEnd = wordStart;
        int i = wordStart;
        while(true) {
            for(i = wordStart; i < pathLen; i++){
                if(path[i] == '/') {
                    wordEnd = i - 1;
                    break;
                }
            }
            if (i >= pathLen){
                wordEnd = i - 1;
            }
            std::string word(path + wordStart, wordEnd - wordStart + 1);
            auto it = node->nodeDict.find(word);
            if (it == node->nodeDict.end()){
                HttpRouteNode* newNode = new HttpRouteNode(word.c_str());
                node->nodeDict[word] = newNode;
                node->nodeArr.push_back(newNode);
                if (word.size() > 0 && word[0] == ':') {
                    node->requiredNode = newNode;
                } else if (word.size() > 0 && word[0] == '*') {
                    node->optionalNode = newNode;
                }
                node = newNode;
            } else {
                node = it->second;
            }
            if (i >= pathLen){
                break;
            }
            wordStart = i + 1;
            wordEnd = wordStart;
        }
    }
    if(handler != NULL) {
        if(node->handler != NULL){
            return false;
        }
        node->handler = handler;
        node->fullPath = path;
    } else {
        node->handler = NULL;
    }
    //this->coord->coreLogDebug("bbb %s %s", node->path.c_str(), node->fullPath.c_str());
    return true;
} 

RouterMethodTree* HttpRouter::getMethodTree(const char* method) {
    const auto it = this->trees.find(method);
    if (it == this->trees.end()){
        RouterMethodTree* methodTree = new RouterMethodTree();
        this->trees[method] = methodTree;
        return methodTree;
    } else {
        return it->second;
    }
}



}
}  