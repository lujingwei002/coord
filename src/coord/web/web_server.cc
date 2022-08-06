#include "coord/web/web_server.h"
#include "coord/http/http_server.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/http/http_router.h"
#include "coord/coord.h"

namespace coord {
namespace web {

CC_IMPLEMENT(WebServer, "coord::web::WebServer")



WebServer::WebServer(Coord* coord) {
    this->coord = coord;
    this->handler = nullptr;
    this->httpServer = this->coord->NewHttpServer();
    this->httpServer->SetHandler(this);
    this->Router = new http::HttpRouter(coord, this->httpServer);
}

WebServer::~WebServer(){
    if (nullptr != this->Router){
        this->coord->Destory(this->Router);
        this->Router = nullptr;
    }
}

WebConfig* WebServer::DefaultConfig() {
    return &this->Config;
}

int WebServer::Start() {
    http::HttpServerConfig* config = this->httpServer->DefaultConfig();
    config->Host = this->Config.Host;
    config->Port = this->Config.Port;
    config->Backlog = this->Config.Backlog;
    config->AssetDir = this->Config.AssetDir;
    config->RecvBufferSize = this->Config.RecvBuffer;
    config->SSLEncrypt = this->Config.SSLEncrypt;
    config->SSLPemFile = this->Config.SSLPemFile;
    config->SSLKeyFile = this->Config.SSLKeyFile;
    config->UseEtag = this->Config.UseEtag;

    this->coord->CoreLogDebug("[WebServer] Listen, host=%s, port=%d", this->Config.Host.c_str(), this->Config.Port);
    int err =this->httpServer->Start();

    auto router = this->Router;
    router->Get("/debug/index", std::bind(&WebServer::get_debug_index, this, std::placeholders::_1));
    return err;
}

void WebServer::recvHttpRequest(http::HttpRequest* request) {
    //http::HttpResponse* response = request->GetResponse();
    //response->Text("hello world");
    this->Router->recvHttpRequest(request);
}

void WebServer::recvHttpUpgrade(http::HttpAgent* agent, http::HttpRequest* request){

}


void WebServer::get_debug_index(http::HttpRequest* request) {
    http::HttpResponse* response = request->GetResponse();
    response->Text("debug");
}

}
}