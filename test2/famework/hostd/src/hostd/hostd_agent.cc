#include "hostd/hostd_agent.h"
#include "hostd.h"
#include "hostd/hostd_server.h"
#include "hostd/hostd_request.h"
#include "coord/config/config.h"
#include "coord/net/init.h"
#include "coord/coord.h"

namespace hostd {

CC_IMPLEMENT(HostdAgent, "hostd::HostdAgent")

HostdAgent* newHostdAgent(coord::Coord* coord, Hostd* hostd,  HostdServer* server, coord::net::TcpAgent* tcpAgent) {
    auto self = new HostdAgent(coord, hostd, server, tcpAgent);
    return self;
}

HostdAgent::HostdAgent(coord::Coord *coord, Hostd* hostd,  HostdServer* server, coord::net::TcpAgent* tcpAgent) {
    this->coord = coord;
    this->hostd = hostd;
    this->server = server;
    this->tcpAgent = tcpAgent;
    this->status = HostdAgentStatus_Start;
    this->tcpAgent->SetHandler(this);
}

HostdAgent::~HostdAgent() {
    this->coord->LogDebug("[HostdAgent] ~HostdAgent");
    this->coord->Destory(this->tcpAgent);
}

void HostdAgent::recvTcpNew(coord::net::TcpAgent* tcpAgent){
    this->coord->LogDebug("[HostdAgent] recvTcpNew");
    this->coord->DontDestory(this->tcpAgent);
    this->Response("welcome");
}

void HostdAgent::recvTcpClose(coord::net::TcpAgent* agent){
    this->coord->LogDebug("[HostdAgent] recvTcpClose sessionId=%d", this->sessionId);
    this->server->recvTcpClose(this);
}

void HostdAgent::recvTcpError(coord::net::TcpAgent* agent){
    this->coord->LogDebug("[HostdAgent] recvTcpError sessionId=%d", this->sessionId);
}

int HostdAgent::recvTcpData(coord::net::TcpAgent* agent, char* data, size_t len){
    this->coord->LogDebug("[HostdAgent] recvTcpData, len=%ld", len);
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

void HostdAgent::recvPacket(const char* data, size_t len) {
    this->coord->LogDebug("[HostdAgent] recvPacket, data=%s", data);
    HostdRequest* request = newHostdRequest(this->coord, this);
    int err = request->parse(data, len);
    if (err) {
        this->coord->LogDebug("[HostdAgent] recvPacket failed, error=%d", err);
        this->coord->Destory(request);
        return;
    }
    this->recvRequest(request);
    this->coord->Destory(request);
}

void HostdAgent::recvRequest(HostdRequest* request) {
    if (request->Count() <= 0) {
        return;
    }
    printf("aaa %ld\n",request->Count());
    for (size_t i = 0; i < request->Count(); i++) {
        printf("gg %s\n", request->Arg(i));
    }
    this->Response("hello %s", "ljw");
}

void HostdAgent::close() {
    this->tcpAgent->Close();
}

int HostdAgent::send(coord::byte_slice& data) {
    return this->tcpAgent->Send(data);
}

int HostdAgent::send(const char* data, size_t len) {
    return this->tcpAgent->Send(data, len);
}

int HostdAgent::Response(const char* data, size_t len){
    return this->send(data, len);
}

int HostdAgent::Response(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    coord::byte_slice data;
    data.Appendf(fmt, args);
    data.Appendf("\r\n");
    va_end(args);
    return this->send(data);
}

}
      