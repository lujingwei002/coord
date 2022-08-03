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

Request::Request(Coord* coord, cluster_agent* agent) : base_request(coord, agent) {
    this->response = new Response(this->coord, agent, this);
}

Request::~Request() {
}

void Request::onDestory() {
    /*  
    if(this->response){
        this->response->flush();
    }
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("|%10s|%20s | REQUEST |\t\"%s\"", date::FormatNano(duration), this->agent->name.c_str(), this->Route.c_str());
    */
}
 

Response* Request::GetResponse() {
    return dynamic_cast<Response*>(this->response);
}

}

}
