#include "coord/base/base_notify.h"
#include "coord/base/base_agent.h"
#include "coord/base/base_response.h"
#include "coord/coord.h"
#include "coord/coordx.h"

namespace coord {

CC_IMPLEMENT(base_notify, "coord::base_notify")

base_notify::base_notify(Coord* coord, base_agent* agent) : base_reader(coord) {
    this->agent = agent;
    this->coord->DontDestory(this->agent);
    this->ReqTime = uv_hrtime();
}

base_notify::~base_notify() {
    if (nullptr != this->agent) {
        this->coord->Destory(this->agent);
        this->agent = nullptr;
    }
}

void base_notify::onDestory() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s| NOTIFY |\t\"%s\"", coordx::date::FormatNano(duration), this->Route.c_str());
}

} 
