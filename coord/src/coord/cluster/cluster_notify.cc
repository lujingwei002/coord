#include "coord/cluster/cluster_notify.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/cluster/cluster_server.h"
#include "util/date/date.h"
#include "coord/protobuf/init.h"
namespace coord {

namespace cluster {
CC_IMPLEMENT(Notify, "coord::cluster::Notify")

Notify* newNotify(Coord* coord, cluster_agent* agent) {
    Notify* notify = new Notify(coord, agent);
    return notify;
}

Notify::Notify(Coord* coord, cluster_agent* agent) : BaseRequest(coord) {
    this->agent = agent;
    this->coord->DontDestory(this->agent);
}

Notify::~Notify() {
    this->coord->Destory(this->agent);
}

void Notify::onDestory() {
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("|%10s|%20s | NOTIFY |\t\"%s\"", date::FormatNano(duration), this->agent->name.c_str(), this->route.c_str());
}



}

} 