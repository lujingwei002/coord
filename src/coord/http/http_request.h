#pragma once 

#include "coord/builtin/inc.h"
#include "coord/base/base_request.h"
#include "coord/http/declare.h"
#include "coord/http/http_response.h"
#include <uv.h>
#include <map>
#include <tuple>
#include "http-parser/http_parser.h"
#include "coord/builtin/slice.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {
    class Coord;
    namespace http {
        class HttpAgent;
        class HttpServer;
    }
}

namespace coord {//tolua_export
namespace http {//tolua_export

class HttpRequest : public base_request  { //tolua_export
CC_CLASS(HttpRequest);
friend HttpAgent;
friend HttpResponse;
private:
    HttpRequest(Coord* coord, HttpAgent* agent);
    virtual ~HttpRequest();
private:
    void initHttpParser();
    size_t recvData(char* data, size_t len);
    static int on_message_begin(http_parser* parser);
    static int on_url(http_parser* parser, const char *at, size_t length);
    static int on_status(http_parser* parser, const char *at, size_t length);
    static int on_header_field(http_parser* parser, const char *at, size_t length);
    static int on_header_value(http_parser* parser, const char *at, size_t length);
    static int on_headers_complete(http_parser* parser);
    static int on_body(http_parser* parser, const char *at, size_t length);
    static int on_message_complete(http_parser* parser);
    static int on_chunk_header(http_parser* parser);
    static int on_chunk_complete(http_parser* parser);
private:
    HttpServer*                         server;
    HttpAgent*                          agent;
    // 消息头
    std::map<std::string, std::string>  headerDict; 
    // 是否已经收到一个完整的请求
    bool                                isComplete; 
    // 临时变量
    std::string                         tempHeaderField;
    http_parser                         parser;
    http_parser_settings                setting;




/// ##export method
public:
    /// 获取消息头
    const char* GetHeader(const char* field);                   //tolua_export
    /// 是否有消息头
    bool HasHeader(const char* field, const char* value);       //tolua_export 
    /// 获取response接口
    virtual HttpResponse* GetResponse();                        //tolua_export
public:
    /// 请求方法 GET | POST | PUT | OPTION |
    std::string                         Method;             //tolua_export
    /// 完整的URL地址
    std::string                         Url;                //tolua_export
    /// 路径 如: /account/login
    std::string                         Path;               //tolua_export
    /// 查询字符串,不包含?号 如: username=xx
    std::string                         Query;              //tolua_export
    std::string                         Schema;             //tolua_export
    /// 域名
    std::string                         Host;               //tolua_export
    /// 是否upgrade请求
    bool                                IsUpgrade;    


};//tolua_export



}//tolua_export
}//tolua_export


