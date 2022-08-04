#include "coord/http/http_server.h"
#include "coord/http/http_agent.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/http/http_router.h"
#include "coord/coord.h"
#include "coord/object/object.h"
#include "coord/builtin/slice.h"
#include "coord/log/log.h"
#include "coord/http/http_util.h"
#include "coord/scene/scene.h"
#include "coord/encrypt/base64.h"
#include "coord/encrypt/sha1.h"
#include "coord/encrypt/md5.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

namespace coord {
namespace http {
CC_IMPLEMENT(HttpServer, "coord::http::HttpServer")

HttpServer* newHttpServer(Coord* coord) {
    HttpServer* httpServer = new HttpServer(coord);
    return httpServer;
}

HttpServer::HttpServer(Coord* coord) : coord(coord) {
    this->handler = nullptr;
    this->listener = net::NewTcpListener(coord);
    this->Router = new HttpRouter(coord, this);
    this->sslCtx = nullptr;
}

HttpServer::~HttpServer(){
    delete this->Router;
    this->Router = nullptr;
    delete this->listener;
    this->listener = nullptr;
    if(this->sslCtx) {
        SSL_CTX_free(this->sslCtx);
        this->sslCtx = nullptr;
    }
} 

HttpServerConfig* HttpServer::DefaultConfig() {
    return &this->config;
}

int HttpServer::Start() {
    //this->coord->CoreLogDebug("[HttpServer] Listen, host=%s, port=%d, backlog=%d", host, port, backlog);
    this->listener->SetHandler(this);
    if (this->config.SSLEncrypt) {
        SSL_CTX* sslCtx = SSL_CTX_new(SSLv23_server_method());
        if (!SSL_CTX_use_certificate_file(sslCtx, this->config.SSLPemFile.c_str(), SSL_FILETYPE_PEM)) {
            this->coord->CoreLogError("[HttpServer] Listen failed, cert=%s, error='SSL_CTX_use_certificate_file'", this->config.SSLPemFile.c_str());
            ERR_print_errors_fp(stderr);
            return -1;
        }
        if (!SSL_CTX_use_PrivateKey_file(sslCtx, this->config.SSLKeyFile.c_str(), SSL_FILETYPE_PEM )) {
            this->coord->CoreLogError("[HttpServer] Listen failed, key=%s, error='SSL_CTX_use_PrivateKey_file'", this->config.SSLKeyFile.c_str());
            ERR_print_errors_fp(stderr);
            return -1;
        }
        if (!SSL_CTX_check_private_key(sslCtx)) {
            this->coord->CoreLogError("[HttpServer] Listen failed, error='SSL_CTX_check_private_key'");
            ERR_print_errors_fp(stderr);
            return -1;
        }
        this->sslCtx = sslCtx;
    }
    int err = this->listener->Listen(this->config.Host.c_str(), this->config.Port, this->config.Backlog);
    return err;
}

void HttpServer::SetHandler(IHttpHandler* handler) {
    this->handler = handler;
}

void HttpServer::recvHttpRequest(HttpAgent* agent, HttpRequest* request){
    int sessionId = agent->SessionId;
    this->coord->CoreLogDebug("[HttpServer] recvHttpRequest, sessionId=%d", sessionId);
    if(this->handler) {
        this->handler->recvHttpRequest(request);
    } else {
        this->Router->recvHttpRequest(request);
    }
}

void HttpServer::recvHttpUpgrade(HttpAgent* agent, HttpRequest* request){
    int sessionId = agent->SessionId;
    this->coord->CoreLogDebug("[HttpServer] recvHttpUpgrade, sessionId=%d", sessionId);
    if(this->handler) {
        this->handler->recvHttpUpgrade(agent, request);
    } else {
        throw HttpPageNotFoundException(request->Path.c_str());
    } 
}

void HttpServer::recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent){
    int sessionId = tcpAgent->sessionId;
    this->coord->CoreLogDebug("[HttpServer] recvTcpNew sessionId=%d, remoteAddr=%s", sessionId, tcpAgent->remoteAddr.c_str());
    tcpAgent->SetRecvBuffer(this->config.RecvBufferSize);
    HttpAgent *agent = new HttpAgent(this->coord, this, tcpAgent);
    agent->SessionId = sessionId;
    agent->RemoteAddr =  tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
}

void HttpServer::recvAgentClose(HttpAgent* agent){
    int sessionId = agent->SessionId;
    this->coord->CoreLogDebug("[HttpServer] recvAgentClose sessionId=%d, ref=%d", sessionId, agent->_ref);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->CoreLogDebug("[HttpServer] recvAgentClose failed, error='agent not found', sessionId=%d", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void HttpServer::Close() {
    
}

}
}
