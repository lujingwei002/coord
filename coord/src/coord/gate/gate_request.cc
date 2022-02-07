#include "coord/gate/gate_request.h"
#include "coord/gate/gate_agent.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_response.h"
#include "coord/protobuf/init.h"
#include "util/date/date.h"

namespace coord {

namespace gate {
CC_IMPLEMENT(GateRequest, "coord::gate::GateRequest")

GateRequest* newGateRequest(Coord* coord, GateAgent* agent) {
    GateRequest* request = new GateRequest(coord, agent);
    return request;
}

GateRequest::GateRequest(Coord* coord, GateAgent* agent) : BaseRequest(coord) {
    this->agent = agent;
    this->response = newGateResponse(this->coord, this);
    this->sessionId = agent->sessionId;
    this->coord->DontDestory(this->agent);
}

GateRequest::~GateRequest() {
    this->coord->coreLogDebug("[GateRequest] ~GateRequest");
    if(this->response){
        delete this->response;
        this->response = NULL;
    }
    this->coord->Destory(this->agent);
}

void GateRequest::onDestory() {
    if(this->response){
        this->response->flush();
    }
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("[GateRequest] REQUEST | %10s | %16s | \"%s\"", date::FormatNano(duration), this->agent->remoteAddr.c_str(), this->route.c_str());
}
 
GateResponse* GateRequest::GetResponse() {
    return this->response;
}

void GateRequest::Kick(const char* reason) {
    if(!this->agent){
        return;
    }
    this->agent->kick(reason);
}
GateSession* GateRequest::GetSession() {
    return this->agent->session;
}
}

}