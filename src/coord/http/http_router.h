#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/memory/type.h"
#include "coord/coordx.h"
#include "coord/http/http_base.h"
#include "coord/http/http_request.h"
#include <map>
#include <string>
#include <functional>
#include "r3/r3.hpp"

namespace coord {
    class Coord;
    class ScriptComponent;
    namespace http {
        class HttpRequest;
        class HttpFrame;
        class HttpServer;
    }
    namespace web {
        class WebServer;
    }
}

namespace coord {//tolua_export
namespace http {//tolua_export

///
///     * 
///
///  /a/b/c
///
///  /a/:b/c
///
///
///  /a/*b/c
///
///

typedef std::function<void (const HttpRequestRef& request)> HttpRouter_RecvHttpRequest; 



class HttpRouter : public coord::RcObject {//tolua_export
RC_CLASS(HttpRouter);
friend HttpServer;
friend web::WebServer;
private:
class http_router_handler {
public:
    //http_router_handler(){}
    http_router_handler(Coord* coord, const std::string& path, HttpRouter_RecvHttpRequest recvHttpRequestFunc, int ref = LUA_NOREF);
    ~http_router_handler();
public:
    void recvHttpRequest(HttpRequest* request);
    void move(http_router_handler* handler);
public:
    Coord*                      coord;
    std::string                 path;
    HttpRouter_RecvHttpRequest  recvHttpRequestFunc;
    int                         ref;
    int                         times;              //处理次数
    int                         consumeTime;        //耗时
};


private:
    HttpRouter(Coord* coord, HttpServer* server);
    virtual ~HttpRouter();
private:
    void trace(const char* method, http_router_handler* handler);
    void recvStaticRequest(const HttpRequestRef& request, const char* dir);
    void recvStaticFileRequest(const HttpRequestRef& request, const char* path);
    void recvHttpRequest(HttpRequest* request);
private:
    http_router_handler* searchHandler(const char* method, const char* path);
    bool addRoute(const char* method, const char* path, http_router_handler* handler);
    r3::Tree* getMethodTree(const char* method);
private:
    Coord*                                                              coord;
    HttpServer*                                                         server;
    std::map<std::string, r3::Tree*>                                    trees;
    std::map<std::string, std::map<std::string, http_router_handler*>>  methodDict;




public:
    /// ##export method
    bool IsMatch(const char* method, const char* path);
    const char* Match(const char* method, const char* path);
    int Get(lua_State* L);  //tolua_export
    int Post(lua_State* L); //tolua_export
    bool Get(const char* path, ScriptComponent* object, int ref);
    bool Post(const char* path, ScriptComponent* object, int ref);

    bool Get(const char* path, HttpRouter_RecvHttpRequest method);
    bool Post(const char* path, HttpRouter_RecvHttpRequest method);
    bool Static(const char* path, const char* dir);//tolua_export
    bool StaticFile(const char* path, const char* filePath);//tolua_export
    void Trace();//tolua_export
};//tolua_export

}//tolua_export
}//tolua_export
 
