#include "coord/cluster/cluster_notify.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_server.h"
#include "util/date/date.h"
#include "coord/protobuf/init.h"
namespace coord {

namespace cluster {
CC_IMPLEMENT(GateNotify, "coord::cluster::GateNotify")

GateNotify* newNotify(Coord* coord, cluster_agent* agent) {
    GateNotify* notify = new GateNotify(coord, agent);
    return notify;
}

GateNotify::GateNotify(Coord* coord, cluster_agent* agent) : base_notify(coord, nullptr) {
    this->agent = agent;
    this->coord->DontDestory(this->agent);
}

GateNotify::~GateNotify() {
    this->coord->Destory(this->agent);
}

void GateNotify::onDestory() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%20s | NOTIFY |\t\"%s\"", date::FormatNano(duration), this->agent->name.c_str(), this->Route.c_str());
}



}

} 
