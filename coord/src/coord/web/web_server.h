#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/builtin/slice.h"
#include "coord/web/web_config.h"
#include <map>
#include <string>
namespace coord {//tolua_export

class Coord;
namespace http {
    class HttpRequest;
    class HttpResponse;
    class HttpFrame;
    class HttpServer;
}

namespace web {//tolua_export

class IWebHandler {//tolua_export
public:
    
};//tolua_export

class WebServer : public http::IHttpHandler {//tolua_export
CC_CLASS(WebServer);
public:
    WebServer(Coord* coord);
    virtual ~WebServer();
public:
    WebConfig* DefaultConfig();//tolua_export
    bool Start();//tolua_export
    virtual void recvHttpRequest(http::HttpRequest* request);
    virtual void recvHttpFrame(http::HttpFrame* frame);
public:
    Coord*              coord;
    WebConfig           config;
    IHttpHandler*       handler;
    http::HttpServer*   listener;
};//tolua_export

WebServer* newWebServer(Coord* coord);

}//tolua_export
}//tolua_export
