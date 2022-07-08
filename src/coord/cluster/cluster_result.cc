#include "coord/cluster/cluster_result.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_client.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/protobuf/init.h"
#include "util/date/date.h"

namespace coord {

namespace cluster {
CC_IMPLEMENT(Result, "coord::cluster::Result")

Result* newResult(Coord* coord, cluster_client* client) {
    Result* result = new Result(coord, client);
    return result;
}

Result::Result(Coord* coord, cluster_client* client) : BaseResult(coord) {
    this->client = client;
    this->coord->DontDestory(this->client);
}

Result::~Result() {
    this->coord->CoreLogDebug("[cluster::Result] ~Result");
    this->coord->Destory(this->client);
}

void Result::onDestory() {
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("|%10s|%20s | RESULT | %3d |\t\"%s\"", date::FormatNano(duration), this->client->name.c_str(), this->Code, this->route.c_str());
}


}
}