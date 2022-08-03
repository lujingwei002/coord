#include "coord/websocket/websocket_server.h"
#include "coord/websocket/websocket_agent.h"
#include "coord/websocket/websocket_router.h"
#include "coord/websocket/websocket_frame.h"
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
namespace websocket {

CC_IMPLEMENT(Server, "coord::websocket::Server")

Server* newWebSocketServer(Coord* coord) {
    Server* webSocketServer = new Server(coord);
    return webSocketServer;
}

Server::Server(Coord* coord) : coord(coord) {
    this->handler = NULL;
    this->httpServer = http::newHttpServer(coord);
    this->httpServer->SetHandler(this);
    this->Router = newRouter(coord);
}

Server::~Server(){
    delete this->Router;
    this->Router = NULL;
    delete this->httpServer;
    this->httpServer = NULL;
} 

WebSocketServerConfig* Server::DefaultConfig() {
    return &this->config;
}

int Server::Start() {
    this->coord->CoreLogDebug("[websocket::Server] Listen, host=%s, port=%d, backlog=%d", this->config.Host.c_str(), this->config.Port, this->config.Backlog);
    http::HttpServerConfig* config = this->httpServer->DefaultConfig();
    config->Host = this->config.Host;
    config->Port = this->config.Port;
    config->Backlog = this->config.Backlog;
    config->SSLEncrypt = this->config.SSLEncrypt;
    config->SSLPemFile = this->config.SSLPemFile;
    config->SSLKeyFile = this->config.SSLKeyFile;
    config->RecvBufferSize = this->config.RecvBufferSize;
    return this->httpServer->Start();
}

void Server::SetHandler(IWebSocketHandler* handler) {
    this->handler = handler;
}

void Server::recvHttpRequest(http::HttpRequest* request){
    
}

void Server::recvHttpUpgrade(http::HttpAgent* httpAgent, http::HttpRequest* request){
    int sessionId = httpAgent->SessionId;
    this->coord->CoreLogDebug("[websocket::Server] recvHttpUpgrade sessionId=%d, remoteAddr=%s", sessionId, httpAgent->RemoteAddr.c_str());
    Agent *agent = newAgent(this->coord, this, httpAgent);
    agent->sessionId = sessionId;
    agent->remoteAddr =  httpAgent->RemoteAddr;
    this->agentDict[sessionId] = agent;
    this->recvWebSocketNew(agent);
}

void Server::recvAgentClose(Agent* agent){
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[websocket::Server] recvAgentClose sessionId=%d, ref=%d", sessionId, agent->_ref);
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->CoreLogDebug("[websocket::Server] recvAgentClose failed, error='agent not found', sessionId=%d", sessionId);
        return;
    }
    this->agentDict.erase(it);
    this->coord->Destory(agent);
}

void Server::recvWebSocketNew(Agent* agent){
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[websocket::Server] recvWebSocketNew, sessionId=%d", sessionId);
    if(this->handler){
        this->handler->recvWebSocketNew(agent);
    } else {
        this->Router->recvWebSocketNew(agent); 
    }
}

void Server::recvWebSocketClose(Agent* agent){
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[websocket::Server] recvWebSocketClose, sessionId=%d", sessionId);
    this->Router->recvWebSocketClose(agent);
}

void Server::recvWebSocketFrame(Agent* agent, Frame* frame) {
    int sessionId = agent->sessionId;
    this->coord->CoreLogDebug("[websocket::Server] recvWebSocketFrame, sessionId=%d", sessionId);
    this->Router->recvWebSocketFrame(agent, frame);
}

void Server::Close() {
    
}

}
}
