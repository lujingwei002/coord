#include "coord/cluster/cluster_response.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/protobuf/init.h"

namespace coord {

namespace cluster {
CC_IMPLEMENT(Response, "coord::cluster::Response")


Response::Response(Coord* coord, cluster_agent* agent, Request* request) : internal_response(coord, agent, request) {
}

Response::~Response() {
}

/*  
int Response::flush() {
    base_response::flush();
    Request* request = this->request;
    cluster_agent* agent = this->request->agent; 
    return agent->response(request->Id, this->Code, this->payload);
}*/

}

}
