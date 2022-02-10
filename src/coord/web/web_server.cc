#include "coord/web/web_server.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/coord.h"

namespace coord {
namespace web {

CC_IMPLEMENT(WebServer, "coord::web::WebServer")

WebServer* newWebServer(Coord* coord) {
    WebServer* webServer = new WebServer(coord);
    return webServer;
}

WebServer::WebServer(Coord* coord) : coord(coord) {
    this->handler = NULL;
    this->listener = http::newHttpServer(coord);
    this->listener->SetHandler(this);
}

WebServer::~WebServer(){

}

WebConfig* WebServer::DefaultConfig() {
    return &this->config;
}

bool WebServer::Start() {
    this->coord->coreLogDebug("[WebServer] Listen, host=%s, port=%d", this->config.Host.c_str(), this->config.Port);
    this->listener->SetHandler(this);
    this->listener->Listen(this->config.Host.c_str(), this->config.Port);
    return true;
}

void WebServer::recvHttpRequest(http::HttpRequest* request) {
    http::HttpResponse* response = request->GetResponse();
   // response->JSON("hello world");
}

void WebServer::recvHttpFrame(http::HttpFrame* frame){

}

}
}