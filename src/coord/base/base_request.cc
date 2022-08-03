#include "coord/base/base_request.h"
#include "coord/base/base_response.h"
#include "coord/base/base_agent.h"
#include "coord/coord.h"
#include "util/date/date.h"

namespace coord {
CC_IMPLEMENT(base_request, "coord::base_request")

base_request::base_request(Coord* coord, base_agent* agent) : base_reader(coord) {
    this->ReqTime = uv_hrtime();
    this->agent = agent;
    this->coord->DontDestory(this->agent);
    this->response = nullptr;
    this->SessionId = agent->SessionId;
}

base_request::~base_request() {
    this->coord->Destory(this->agent);
}

void base_request::onDestory() {
    if(nullptr != this->response){
//        this->response->Flush();
        this->coord->Destory(this->response);
        this->response = nullptr;
    }
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%10s| REQUEST |\t%s", this->TypeName(), date::FormatNano(duration), this->Route.c_str());
}

base_response* base_request::GetResponse() {
    return this->response;
}

}
