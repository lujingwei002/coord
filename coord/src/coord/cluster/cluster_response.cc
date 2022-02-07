#include "coord/cluster/cluster_response.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_agent.h"
#include "coord/coord.h"
#include "coord/cluster/cluster.h"
#include "coord/protobuf/init.h"

namespace coord {

namespace cluster {
CC_IMPLEMENT(Response, "coord::cluster::Response")

Response* newResponse(Coord* coord, Request* request) {
    Response* response = new Response(coord, request);
    return response;
}

Response::Response(Coord* coord, Request* request) : BaseResponse(coord) {
    this->request = request;
}

Response::~Response() {

}

int Response::flush() {
    BaseResponse::flush();
    Request* request = this->request;
    cluster_agent* agent = this->request->agent; 
    return agent->response(request->id, this->code, this->payload);
}

}

}