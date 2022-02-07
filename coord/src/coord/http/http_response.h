#pragma once 

#include "coord/builtin/type.h"
#include <libuv/uv.h>
#include <map>
#include <string>
#include <tuple>
#include "http-parser/http_parser.h"
#include "coord/builtin/slice.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}


namespace coord {//tolua_export
class Coord;
namespace json {
class Reflect;
}
namespace http {//tolua_export
class HttpAgent;
class HttpServer;
class HttpRequest;
class HttpResponse  { //tolua_export
CC_CLASS(HttpResponse);
public:
    HttpResponse(HttpRequest* request);
    virtual ~HttpResponse();  
    int Text(lua_State* L);//tolua_export
    bool Text(const char* content);//tolua_export
    bool Json(json::Reflect& json);//tolua_export
    int Upgrade();//tolua_export
    void PageNotFound();//tolua_export
    void Exception(const char* msg);//tolua_export
    void SetStatusCode(int code);//tolua_export
    bool File(const char* path);//tolua_export
    bool Allow();
public:
    void flush();
public:
    HttpRequest*                        request;
    HttpServer*                         server;
    Coord*                              coord;
    std::map<std::string, std::string>  headerDict;
    byte_slice                          body;
    byte_slice                          response;
    std::string                         contentType;
    int                                 statusCode;
};//tolua_export

 HttpResponse* newHttpResponse(HttpRequest* request);

}//tolua_export
}//tolua_export


