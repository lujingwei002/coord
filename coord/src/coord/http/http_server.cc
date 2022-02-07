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
    this->handler = NULL;
    this->listener = net::NewTcpListener(coord);
    this->Router = newHttpRouter(coord, this);
    this->sslCtx = NULL;
}

HttpServer::~HttpServer(){
    delete this->Router;
    this->Router = NULL;
    delete this->listener;
    this->listener = NULL;
    if(this->sslCtx) {
        SSL_CTX_free(this->sslCtx);
        this->sslCtx = NULL;
    }
} 

HttpServerConfig* HttpServer::DefaultConfig() {
    return &this->config;
}

int HttpServer::Start() {
    //this->coord->coreLogDebug("[HttpServer] Listen, host=%s, port=%d, backlog=%d", host, port, backlog);
    this->listener->SetHandler(this);
    if (this->config.SSLEncrypt) {
        SSL_CTX* sslCtx = SSL_CTX_new(SSLv23_server_method());
        if (!SSL_CTX_use_certificate_file(sslCtx, this->config.SSLPemFile.c_str(), SSL_FILETYPE_PEM)) {
            this->coord->coreLogError("[HttpServer] Listen failed, cert=%s, error='SSL_CTX_use_certificate_file'", this->config.SSLPemFile.c_str());
            ERR_print_errors_fp(stderr);
            return -1;
        }
        if (!SSL_CTX_use_PrivateKey_file(sslCtx, this->config.SSLKeyFile.c_str(), SSL_FILETYPE_PEM )) {
            this->coord->coreLogError("[HttpServer] Listen failed, key=%s, error='SSL_CTX_use_PrivateKey_file'", this->config.SSLKeyFile.c_str());
            ERR_print_errors_fp(stderr);
            return -1;
        }
        if (!SSL_CTX_check_private_key(sslCtx)) {
            this->coord->coreLogError("[HttpServer] Listen failed, error='SSL_CTX_check_private_key'");
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

void HttpServer::recvHttpRequest(HttpRequest* request){
    HttpAgent* agent = request->agent;
    int sessionId = agent->sessionId;
    this->coord->coreLogDebug("[HttpServer] recvHttpRequest, sessionId=%d", sessionId);
    if(this->handler) {
        this->handler->recvHttpRequest(request);
    } else {
        this->Router->recvHttpRequest(request);
    }
}

void HttpServer::recvHttpUpgrade(HttpAgent* agent, HttpRequest* request){
    int sessionId = agent->sessionId;
    this->coord->coreLogDebug("[HttpServer] recvHttpUpgrade, sessionId=%d", sessionId);
    if(this->handler) {
        this->handler->recvHttpUpgrade(agent, request);
    } else {
        throw HttpPageNotFoundException(request->Path.c_str());
    } 
}

void HttpServer::recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent){
    int sessionId = tcpAgent->sessionId;
    this->coord->coreLogDebug("[HttpServer] recvTcpNew sessionId=%d, remoteAddr=%s", sessionId, tcpAgent->remoteAddr.c_str());
    tcpAgent->SetRecvBuffer(this->config.RecvBufferSize);
    HttpAgent *agent = HttpAgent::New(this->coord, this, tcpAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr =  tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
}

void HttpServer::recvAgentClose(HttpAgent* agent){
    int sessionId = agent->sessionId;
    this->coord->coreLogDebug("[HttpServer] recvAgentClose sessionId=%d, ref=%d", sessionId, agent->_ref);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->coreLogDebug("[HttpServer] recvAgentClose failed, error='agent not found', sessionId=%d", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void HttpServer::Close() {
    
}

}
}