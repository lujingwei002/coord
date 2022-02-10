#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/builtin/slice.h"
#include "coord/http/http_base.h"
#include <map>
#include <string>
#include <functional>
namespace coord {//tolua_export

class Coord;

class ScriptComponent;

namespace http {//tolua_export

class HttpRequest;
class HttpFrame;
class HttpServer;
typedef std::function<void (HttpRequest* request)> HttpRouter_RecvHttpRequest; 

class http_router_handler {
public:
    //http_router_handler(){}
    http_router_handler(Coord* coord, HttpRouter_RecvHttpRequest recvHttpRequestFunc, int ref = LUA_NOREF): 
        coord(coord), recvHttpRequestFunc(recvHttpRequestFunc), ref(ref) {
        this->init();    
    }
    ~http_router_handler();
public:
    void recvHttpRequest(HttpRequest* request);
    void init() {
        this->times = 0;
        this->consumeTime = 0;
    }
public:
    Coord*                      coord;
    HttpRouter_RecvHttpRequest  recvHttpRequestFunc;
    int                         ref;
    int                         times;              //处理次数
    int                         consumeTime;        //耗时
};

class HttpRouteNode {
public:
    HttpRouteNode(const char* path):handler(NULL){
        this->path = path;
        this->optionalNode = NULL;
        this->requiredNode = NULL;
    }
public:
    std::string fullPath;
    std::string path;
    http_router_handler* handler;
    std::map<std::string, HttpRouteNode*> nodeDict;
    std::vector<HttpRouteNode*> nodeArr;
    HttpRouteNode* optionalNode;//*
    HttpRouteNode* requiredNode;//:
};

class RouterMethodTree {
public:
    RouterMethodTree() {
        this->root = new HttpRouteNode("/");
    }
public:
    HttpRouteNode* root;
};

typedef std::map<std::string, http_router_handler> RouterHandlerMap;

class HttpRouter {//tolua_export
CC_CLASS(HttpRouter);
public:
    HttpRouter(Coord* coord, HttpServer* server);
    virtual ~HttpRouter();
public:
    int Get(lua_State* L);  //tolua_export
    int Post(lua_State* L); //tolua_export
    bool Get(const char* url, ScriptComponent* object, int ref);
    bool Post(const char* url, ScriptComponent* object, int ref);

    bool Get(const char* url, HttpRouter_RecvHttpRequest method);
    bool Post(const char* url, HttpRouter_RecvHttpRequest method);
    bool Static(const char* url, const char* dir);//tolua_export
    bool StaticFile(const char* url, const char* path);//tolua_export
    void Trace();//tolua_export
public:
    void trace(const char* event, HttpRouteNode* node);
    void recvStaticRequest(HttpRequest* request, const char* dir);
    void recvStaticFileRequest(HttpRequest* request, const char* path);
    void recvHttpRequest(HttpRequest* request);
public:
    HttpRouteNode* searchNode(HttpRouteNode* root, int i, int argc, const char** argv);
    HttpRouteNode* searchNode(const char* method, const char* path);
    http_router_handler* searchHandler(const char* method, const char* path);
    bool addRoute(const char* method, const char* path, http_router_handler* handler);
    RouterMethodTree* getMethodTree(const char* method);
public:
    Coord*                                      coord;
    HttpServer*                                 server;
    std::map<std::string, RouterMethodTree*>    trees;
};//tolua_export

HttpRouter* newHttpRouter(Coord* coord, HttpServer* server);

}//tolua_export
}//tolua_export
 