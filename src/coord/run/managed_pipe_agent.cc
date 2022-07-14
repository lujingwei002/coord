#include "coord/run/managed_pipe_agent.h"
#include "coord/run/running.h"
#include "coord/config/config.h"
#include "coord/run/managed_pipe_server.h"
#include "coord/run/managed_pipe_request.h"
#include "coord/pipe/pipe_agent.h"
#include "coord/coord.h"
namespace coord {

namespace run {

CC_IMPLEMENT(ManagedPipeAgent, "coord::run::ManagedPipeAgent")

ManagedPipeAgent* newManagedPipeAgent(Coord* coord, Running* running,  ManagedPipeServer* server, pipe::PipeAgent* pipeAgent) {
    auto self = new ManagedPipeAgent(coord, running, server, pipeAgent);
    return self;
}

ManagedPipeAgent::ManagedPipeAgent(Coord *coord, Running* running,  ManagedPipeServer* server, pipe::PipeAgent* pipeAgent) {
    this->coord = coord;
    this->running = running;
    this->server = server;
    this->pipeAgent = pipeAgent;
    this->status = ManagedPipeAgentStatus_Start;
    this->pipeAgent->SetHandler(this);
}

ManagedPipeAgent::~ManagedPipeAgent() {
    this->coord->CoreLogDebug("[ManagedPipeAgent] ~ManagedPipeAgent");
    this->coord->Destory(this->pipeAgent);
}

void ManagedPipeAgent::recvPipeNew(pipe::PipeAgent* pipeAgent){
    this->coord->CoreLogDebug("[ManagedPipeAgent] recvPipeNew");
    this->coord->DontDestory(this->pipeAgent);
    this->Response("welcome");
}

void ManagedPipeAgent::recvPipeClose(pipe::PipeAgent* agent){
    this->coord->CoreLogDebug("[ManagedPipeAgent] recvPipeClose sessionId=%d", this->sessionId);
    this->server->recvPipeClose(this);
}

void ManagedPipeAgent::recvPipeError(pipe::PipeAgent* agent){
    this->coord->CoreLogDebug("[ManagedPipeAgent] recvPipeError sessionId=%d", this->sessionId);
}

int ManagedPipeAgent::recvPipeData(pipe::PipeAgent* agent, char* data, size_t len){
    this->coord->CoreLogDebug("[ManagedPipeAgent] recvPipeData, len=%ld", len);
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

void ManagedPipeAgent::recvPacket(const char* data, size_t len) {
    this->coord->CoreLogDebug("[ManagedPipeAgent] recvPacket, data=%s", data);
    ManagedPipeRequest* request = newManagedPipeRequest(this->coord, this);
    int err = request->parse(data, len);
    if (err) {
        this->coord->CoreLogDebug("[ManagedPipeAgent] recvPacket failed, error=%d", err);
        this->coord->Destory(request);
        return;
    }
    this->recvRequest(request);
    this->coord->Destory(request);
}

void ManagedPipeAgent::recvRequest(ManagedPipeRequest* request) {
    if (request->Count() <= 0) {
        return;
    }
    for (size_t i = 0; i < request->Count(); i++) {
        printf("gg %s\n", request->Arg(i));
    }
    this->Response("hello %s", "ljw");
}

void ManagedPipeAgent::close() {
    this->pipeAgent->Close();
}

int ManagedPipeAgent::send(byte_slice& data) {
    return this->pipeAgent->Send(data);
}

int ManagedPipeAgent::send(const char* data, size_t len) {
    return this->pipeAgent->Send(data, len);
}


int ManagedPipeAgent::Response(const char* data, size_t len){
    return this->send(data, len);
}

int ManagedPipeAgent::Response(const char* fmt, ...) {
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