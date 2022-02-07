#include "coord/gate/gate_notify.h"
#include "coord/gate/gate_agent.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_response.h"
#include "util/date/date.h"

namespace coord {

namespace gate {
CC_IMPLEMENT(GateNotify, "coord::gate::GateNotify")

GateNotify* newGateNotify(Coord* coord, GateAgent* agent) {
    GateNotify* notify = new GateNotify(coord, agent);
    return notify;
}

GateNotify::GateNotify(Coord* coord, GateAgent* agent) : BaseRequest(coord) {
    this->agent = agent;
    this->sessionId = agent->sessionId;
    this->coord->DontDestory(this->agent);
}

GateNotify::~GateNotify() {
    this->coord->Destory(this->agent);
}

void GateNotify::onDestory() {
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("| %10s | %16s | NOTIFY | \"%s\"", date::FormatNano(duration), this->agent->remoteAddr.c_str(), this->route.c_str());
}
 

}

}