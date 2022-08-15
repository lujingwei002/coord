#include "coord/worker/worker_notify.h"
#include "coord/worker/worker.h"
#include "coord/worker/worker_response.h"
#include "coord/worker/worker_result.h"
#include "coord/coord.h"
#include "coord/protobuf/init.h"
#include "coord/coordx.h"
namespace coord {

namespace worker {
CC_IMPLEMENT(Notify, "coord::worker::Notify")

Notify* newNotify(Coord* coord) {
    Notify* notify = new Notify(coord);
    return notify;
}

Notify::Notify(Coord* coord) : base_notify(coord, nullptr) {
   
}

Notify::~Notify() {
    this->coord->CoreLogDebug("[worker::Notify] ~");
}

void Notify::onDestory() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("[worker::Notify] %10s| NOTIFY |\t\"%s\"", coordx::date::FormatNano(duration), this->Route.c_str());
}
 



}
}
