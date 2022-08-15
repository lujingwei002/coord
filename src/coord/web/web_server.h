#pragma once 

#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/coordx.h"
#include "coord/web/web_config.h"
#include <map>
#include <string>

namespace coord {
    class Coord;
    namespace http {
        class HttpRequest;
        class HttpResponse;
        class HttpFrame;
        class HttpServer;
        class HttpRouter;
    }
    namespace web {
    }
}

namespace coord {//tolua_export
namespace web {//tolua_export


class IWebHandler {//tolua_export
public:
    
};//tolua_export

class WebServer : public http::IHttpHandler {//tolua_export
CC_CLASS(WebServer);
friend Coord;
private:
    WebServer(Coord* coord);
    virtual ~WebServer();
private:
    virtual void recvHttpRequest(http::HttpRequest* request);
    virtual void recvHttpUpgrade(http::HttpAgent* agent, http::HttpRequest* request);
private:
    void get_debug_index(const http::HttpRequestRef& request);
private:
    Coord*              coord;
    WebConfig           Config;
    IHttpHandler*       handler;
    http::HttpServer*   httpServer;

public:
    WebConfig* DefaultConfig();//tolua_export
    int Start();//tolua_export
public:
    /// 路由
    http::HttpRouter*   Router;         //tolua_export
};//tolua_export



}//tolua_export
}//tolua_export
