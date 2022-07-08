#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/cluster/cluster_response.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/protobuf/init.h"
#include "util/date/date.h"
namespace coord {

namespace cluster {
CC_IMPLEMENT(Request, "coord::cluster::Request")

Request* newRequest(Coord* coord, cluster_agent* agent) {
    Request* request = new Request(coord, agent);
    return request;
}

Request::Request(Coord* coord, cluster_agent* agent) : BaseRequest(coord) {
    this->agent = agent;
    this->response = newResponse(this->coord, this);
    this->coord->DontDestory(this->agent);
}

Request::~Request() {
    this->coord->CoreLogDebug("[cluster::Request] ~Request");
    if(this->response != NULL){
        delete this->response;
        this->response = NULL;
    }
    this->coord->Destory(this->agent);
}


void Request::onDestory() {
    if(this->response){
        this->response->flush();
    }
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("|%10s|%20s | REQUEST |\t\"%s\"", date::FormatNano(duration), this->agent->name.c_str(), this->route.c_str());
}
 

Response* Request::GetResponse() {
    return this->response;
}


}

}