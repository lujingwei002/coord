#include "coord/base/base_request.h"
#include "coord/base/base_response.h"
#include "coord/base/base_agent.h"
#include "coord/coord.h"
#include "coord/coordx.h"

namespace coord {
CC_IMPLEMENT(base_request, "coord::base_request")

base_request::base_request(Coord* coord, base_agent* agent) : base_reader(coord) {
    this->ReqTime = uv_hrtime();
    this->agent = agent;
    this->SessionId = agent->SessionId;
    this->coord->DontDestory(this->agent);
    this->response = nullptr;
    this->SessionId = agent->SessionId;
}

base_request::~base_request() {
    if (nullptr != this->agent) {
        this->coord->Destory(this->agent);
        this->agent = nullptr;
    }
}

void base_request::DebugLog() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%ld|%ld|%10s| REQUEST | %s", 
                this->TypeName(), 
                this->SessionId, 
                this->Id, 
                coordx::date::FormatNano(duration), 
                this->Route.c_str()
    );
}

void base_request::onDestory() {
    this->DebugLog();
    if(nullptr != this->response){
        this->coord->Destory(this->response);
        this->response = nullptr;
    }
}

base_response* base_request::GetResponse() {
    return this->response;
}

}
