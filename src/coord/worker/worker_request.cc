#include "coord/worker/worker_request.h"
#include "coord/worker/worker.h"
#include "coord/worker/worker_response.h"
#include "coord/worker/worker_result.h"
#include "coord/coord.h"
#include "coord/protobuf/init.h"
#include "util/date/date.h"
namespace coord {

namespace worker {
CC_IMPLEMENT(Request, "coord::worker::Request")

Request* newRequest(Coord* coord) {
    Request* request = new Request(coord);
    return request;
}

Request::Request(Coord* coord) : BaseRequest(coord) {
    this->response = newResponse(this->coord, this);
}

Request::~Request() {
    this->coord->coreLogDebug("[worker::Request] ~");
    if(this->response != NULL){
        delete this->response;
        this->response = NULL;
    }
}

void Request::onDestory() {
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("[worker::Request] %10s| REQUEST |\t\"%s\"", date::FormatNano(duration), this->route.c_str());
}
 
Response* Request::GetResponse() {
    return this->response;
}



}
}