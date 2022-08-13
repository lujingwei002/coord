#include "coord/gate/gate_session.h"
#include "coord/gate/gate_agent.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_promise.h"

#include "coord/protobuf/init.h"

namespace coord {

namespace gate {
CC_IMPLEMENT(GateSession, "coord::gate::GateSession")

GateSession* newGateSession(Coord* coord, GateAgent* agent) {
    GateSession* session = new GateSession(coord, agent);
    return session;
}

GateSession::GateSession(Coord* coord, GateAgent* agent) {
    this->agent = agent;
    this->gate = agent->gate;
    this->coord = coord;
    this->Id = agent->SessionId;
    this->RemoteAddr = agent->RemoteAddr;
    this->UserId = 0;
}

GateSession::~GateSession() {
  
}

void GateSession::Close() {
    this->agent->close();
}

void GateSession::Kick(const char* reason) {
    this->agent->kick(reason);
}

int GateSession::Push(const char* route, google::protobuf::Message* proto){
    return this->agent->push(route, proto);
}

int GateSession::Push(const char* route, protobuf::MessageRef& proto){
    return this->agent->push(route, proto);
}

GatePromise* GateSession::Login(uint64_t userId) {
    return this->gate->login(this->agent, userId);
}

bool GateSession::IsAuth() {
    return this->UserId != 0;
}

}
}
