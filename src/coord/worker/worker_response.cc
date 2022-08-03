#include "coord/worker/worker_response.h"
#include "coord/worker/worker_request.h"
#include "coord/coord.h"
#include "coord/worker/worker.h"
#include "coord/protobuf/init.h"

namespace coord {

namespace worker {
CC_IMPLEMENT(Response, "coord::worker::Response")

Response* newResponse(Coord* coord, Request* request) {
    Response* response = new Response(coord, request);
    return response;
}

Response::Response(Coord* coord, Request* request) : base_response(coord, nullptr, nullptr) {
    this->request = request;
}

Response::~Response() {
    this->coord->CoreLogDebug("[worker::Response] ~");
}



}
}
