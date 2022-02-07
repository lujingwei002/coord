#pragma once 

#include "coord/builtin/init.h"
#include "coord/builtin/base_request.h"
#include <libuv/uv.h>
#include <map>
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

namespace http {//tolua_export
class HttpAgent;
class HttpServer;
class HttpResponse;
class HttpRequest : public BaseRequest  { //tolua_export
CC_CLASS(HttpRequest);
public:
    HttpRequest(Coord* coord, HttpAgent* agent);
    virtual ~HttpRequest();
    const char* GetHeader(const char* field);//tolua_export
    bool HasHeader(const char* field, const char* value);//tolua_export 
    
    HttpResponse* GetResponse();//tolua_export
public:
    size_t parse(char* data, size_t len);
    int send(byte_slice& data);
    virtual void onDestory();
public:
    std::string         Method;             //tolua_export
    std::string         Url;                //tolua_export
    std::string         Path;               //tolua_export
    std::string         Query;              //tolua_export
    std::string         Schema;             //tolua_export
    std::string         Host;               //tolua_export
    std::string         RemoteAddr;         //tolua_export
public:
    HttpAgent*                          agent; 
    HttpServer*                         server;
    HttpResponse*                       response;
    //Coord*                              coord;
    bool                                isComplete; 
    std::string                         headerField;
    http_parser                         parser;
    http_parser_settings                setting;
    bool                                isUpgrade;   
    int                                 sessionId;  
    std::map<std::string, std::string>  headerDict; 
    uint64_t                            reqTime; 
};//tolua_export

HttpRequest* newHttpRequest(Coord* coord, HttpAgent* agent);

}//tolua_export
}//tolua_export


