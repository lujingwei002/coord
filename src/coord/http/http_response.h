#pragma once 

#include "coord/builtin/type.h"
#include <uv.h>
#include <map>
#include <string>
#include <tuple>
#include "http-parser/http_parser.h"
#include "coord/builtin/slice.h"
#include "coord/base/base_response.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {
    class Coord;
    namespace json {
        class Reflect;
    }
    namespace http {
        class HttpAgent;
        class HttpServer;
        class HttpRequest;
    }
}


namespace coord {//tolua_export
namespace http {//tolua_export

class HttpResponse : public base_response { //tolua_export
CC_CLASS(HttpResponse);
friend HttpRequest;
private:
    HttpResponse(Coord* coord, HttpServer* server, HttpAgent* agent, HttpRequest* request);
    virtual ~HttpResponse();  
private:
    HttpRequest*                        request;
    HttpServer*                         server;
    // 响应头
    std::map<std::string, std::string>  headerDict;
    std::string                         contentType;



/// ##export method
public:
    int Text(lua_State* L);             //tolua_export
    bool Text(const char* content);     //tolua_export
    bool Json(json::Reflect& json);     //tolua_export
    int Upgrade();                      //tolua_export
    void PageNotFound();                //tolua_export
    void Exception(const char* msg);    //tolua_export
    void SetStatusCode(int code);       //tolua_export
    bool File(const char* path);        //tolua_export
    bool Allow();
    virtual int Flush();


};//tolua_export

}//tolua_export
}//tolua_export


