#include "consoled/consoled_agent.h"
#include "consoled.h"
#include "consoled/consoled_server.h"
#include "consoled/consoled_request.h"
#include "coord/config/config.h"
#include "coord/net/init.h"
#include "coord/coord.h"

namespace consoled {

CC_IMPLEMENT(ConsoledAgent, "consoled::ConsoledAgent")

ConsoledAgent* newConsoledAgent(coord::Coord* coord, Consoled* consoled,  ConsoledServer* server, coord::net::TcpAgent* tcpAgent) {
    auto self = new ConsoledAgent(coord, consoled, server, tcpAgent);
    return self;
}

ConsoledAgent::ConsoledAgent(coord::Coord *coord, Consoled* consoled,  ConsoledServer* server, coord::net::TcpAgent* tcpAgent) {
    this->coord = coord;
    this->consoled = consoled;
    this->server = server;
    this->tcpAgent = tcpAgent;
    this->status = ConsoledAgentStatus_Start;
    this->tcpAgent->SetHandler(this);
}

ConsoledAgent::~ConsoledAgent() {
    this->coord->LogDebug("[ConsoledAgent] ~ConsoledAgent");
    this->coord->Destory(this->tcpAgent);
}

void ConsoledAgent::recvTcpNew(coord::net::TcpAgent* tcpAgent){
    this->coord->LogDebug("[ConsoledAgent] recvTcpNew");
    this->coord->DontDestory(this->tcpAgent);
    this->Response("welcome");
}

void ConsoledAgent::recvTcpClose(coord::net::TcpAgent* agent){
    this->coord->LogDebug("[ConsoledAgent] recvTcpClose sessionId=%d", this->sessionId);
    this->server->recvTcpClose(this);
}

void ConsoledAgent::recvTcpError(coord::net::TcpAgent* agent){
    this->coord->LogDebug("[ConsoledAgent] recvTcpError sessionId=%d", this->sessionId);
}

int ConsoledAgent::recvTcpData(coord::net::TcpAgent* agent, char* data, size_t len){
    this->coord->LogDebug("[ConsoledAgent] recvTcpData, len=%ld", len);
    int byteRead = 0;
    while(true) {
        char* delimiter = strstr(data, "\r\n");
        if(delimiter == NULL){
            break;
        }
        *delimiter = 0;
        byteRead = (delimiter - data) + 2;
        char* packet = data;
        data = data + byteRead;
        this->recvPacket(packet, byteRead - 2);
    }
    return byteRead;
}

void ConsoledAgent::recvPacket(const char* data, size_t len) {
    this->coord->LogDebug("[ConsoledAgent] recvPacket, data=%s", data);
    ConsoledRequest* request = newConsoledRequest(this->coord, this);
    int err = request->parse(data, len);
    if (err) {
        this->coord->LogDebug("[ConsoledAgent] recvPacket failed, error=%d", err);
        this->coord->Destory(request);
        return;
    }
    this->recvRequest(request);
    this->coord->Destory(request);
}

void ConsoledAgent::recvRequest(ConsoledRequest* request) {
    if (request->Count() <= 0) {
        return;
    }
    printf("aaa %ld\n",request->Count());
    for (size_t i = 0; i < request->Count(); i++) {
        printf("gg %s\n", request->Arg(i));
    }
    this->Response("hello %s", "ljw");
}

void ConsoledAgent::close() {
    this->tcpAgent->Close();
}

int ConsoledAgent::send(coord::byte_slice& data) {
    return this->tcpAgent->Send(data);
}

int ConsoledAgent::send(const char* data, size_t len) {
    return this->tcpAgent->Send(data, len);
}

int ConsoledAgent::Response(const char* data, size_t len){
    return this->send(data, len);
}

int ConsoledAgent::Response(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    coord::byte_slice data;
    data.Appendf(fmt, args);
    data.Appendf("\r\n");
    va_end(args);
    return this->send(data);
}

}
      