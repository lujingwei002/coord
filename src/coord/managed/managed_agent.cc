#include "coord/managed/managed_agent.h"
#include "coord/managed/managed.h"
#include "coord/config/config.h"
#include "coord/managed/managed_server.h"
#include "coord/managed/managed_request.h"
#include "coord/net/tcp_agent.h"
#include "coord/coord.h"
namespace coord {

namespace managed {

CC_IMPLEMENT(ManagedAgent, "coord::managed::ManagedAgent")

ManagedAgent* newManagedAgent(Coord* coord, Managed* managed,  ManagedServer* server, net::TcpAgent* tcpAgent) {
    auto self = new ManagedAgent(coord, managed, server, tcpAgent);
    return self;
}

ManagedAgent::ManagedAgent(Coord *coord, Managed* managed,  ManagedServer* server, net::TcpAgent* tcpAgent) {
    this->coord = coord;
    this->managed = managed;
    this->server = server;
    this->tcpAgent = tcpAgent;
    this->status = ManagedAgentStatus_Start;
    this->tcpAgent->SetHandler(this);
}

ManagedAgent::~ManagedAgent() {
    this->coord->CoreLogDebug("[ManagedAgent] ~ManagedAgent");
    this->coord->Destory(this->tcpAgent);
}

void ManagedAgent::recvTcpNew(net::TcpAgent* tcpAgent){
    this->coord->CoreLogDebug("[ManagedAgent] recvTcpNew");
    this->coord->DontDestory(this->tcpAgent);
    this->Response("welcome");
}

void ManagedAgent::recvTcpClose(net::TcpAgent* agent){
    this->coord->CoreLogDebug("[ManagedAgent] recvTcpClose sessionId=%d", this->sessionId);
    this->server->recvTcpClose(this);
}

void ManagedAgent::recvTcpError(net::TcpAgent* agent){
    this->coord->CoreLogDebug("[ManagedAgent] recvTcpError sessionId=%d", this->sessionId);
}

int ManagedAgent::recvTcpData(net::TcpAgent* agent, char* data, size_t len){
    this->coord->CoreLogDebug("[ManagedAgent] recvTcpData, len=%ld", len);
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

void ManagedAgent::recvPacket(const char* data, size_t len) {
    this->coord->CoreLogDebug("[ManagedAgent] recvPacket, data=%s", data);
    ManagedRequest* request = newManagedRequest(this->coord, this);
    int err = request->parse(data, len);
    if (err) {
        this->coord->CoreLogDebug("[ManagedAgent] recvPacket failed, error=%d", err);
        this->coord->Destory(request);
        return;
    }
    this->recvRequest(request);
    this->coord->Destory(request);
}

void ManagedAgent::recvRequest(ManagedRequest* request) {
    if (request->Count() <= 0) {
        return;
    }
    for (size_t i = 0; i < request->Count(); i++) {
        printf("gg %s\n", request->Arg(i));
    }
    this->Response("hello %s", "ljw");
}

void ManagedAgent::close() {
    this->tcpAgent->Close();
}

int ManagedAgent::send(byte_slice& data) {
    return this->tcpAgent->Send(data);
}

int ManagedAgent::send(const char* data, size_t len) {
    return this->tcpAgent->Send(data, len);
}




int ManagedAgent::Response(const char* data, size_t len){
    return this->send(data, len);
}

int ManagedAgent::Response(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    byte_slice data;
    coord::Appendf(data, fmt, args);
    coord::Appendf(data, "\r\n");
    va_end(args);
    return this->send(data);
}

}
}        