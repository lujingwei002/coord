#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/builtin/slice.h"
#include "coord/http/http_base.h"
#include <map>
#include <string>
#include <functional>

namespace coord {
    class Coord;
    class ScriptComponent;
    namespace http {
        class HttpRequest;
        class HttpFrame;
        class HttpServer;
    }
}

namespace coord {//tolua_export
namespace http {//tolua_export

///
///
///
///

typedef std::function<void (HttpRequest* request)> HttpRouter_RecvHttpRequest; 





class HttpRouter {//tolua_export
CC_CLASS(HttpRouter);
friend HttpServer;

private:
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

class http_router_node {
public:
    http_router_node(const char* path):handler(nullptr){
        this->path = path;
        this->optionalNode = nullptr;
        this->requiredNode = nullptr;
    }
public:
    std::string                                 fullPath;
    std::string                                 path;
    http_router_handler*                        handler;
    std::map<std::string, http_router_node*>    nodeDict;
    std::vector<http_router_node*>              nodeArr;
    http_router_node*                           optionalNode;//*
    http_router_node*                           requiredNode;//:
};

class router_method_tree {
public:
    router_method_tree() {
        this->root = new http_router_node("/");
    }
public:
    http_router_node* root;
};








private:
    HttpRouter(Coord* coord, HttpServer* server);
    virtual ~HttpRouter();
private:
    void trace(const char* event, http_router_node* node);
    void recvStaticRequest(HttpRequest* request, const char* dir);
    void recvStaticFileRequest(HttpRequest* request, const char* path);
    void recvHttpRequest(HttpRequest* request);
private:
    http_router_node* searchNode(http_router_node* root, int i, int argc, const char** argv);
    http_router_node* searchNode(const char* method, const char* path);
    http_router_handler* searchHandler(const char* method, const char* path);
    bool addRoute(const char* method, const char* path, http_router_handler* handler);
    router_method_tree* getMethodTree(const char* method);
private:
    Coord*                                      coord;
    HttpServer*                                 server;
    std::map<std::string, router_method_tree*>  trees;





public:
    /// ##export method
    int Get(lua_State* L);  //tolua_export
    int Post(lua_State* L); //tolua_export
    bool Get(const char* url, ScriptComponent* object, int ref);
    bool Post(const char* url, ScriptComponent* object, int ref);

    bool Get(const char* url, HttpRouter_RecvHttpRequest method);
    bool Post(const char* url, HttpRouter_RecvHttpRequest method);
    bool Static(const char* url, const char* dir);//tolua_export
    bool StaticFile(const char* url, const char* path);//tolua_export
    void Trace();//tolua_export
};//tolua_export

}//tolua_export
}//tolua_export
 