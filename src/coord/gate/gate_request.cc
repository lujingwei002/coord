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

GateRequest::GateRequest(Coord* coord, GateAgent* agent) : base_request(coord, agent) {
    this->agent = agent;
    this->response = new GateResponse(this->coord, agent, this);
}

GateRequest::~GateRequest() {
}

/*  
void GateRequest::onDestory() {
    if(this->response){
        this->response->flush();
    }
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("[GateRequest] REQUEST | %10s | %16s | \"%s\"", date::FormatNano(duration), this->agent->remoteAddr.c_str(), this->Route.c_str());
}
*/
 
GateResponse* GateRequest::GetResponse() {
    return dynamic_cast<GateResponse*>(this->response);
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
