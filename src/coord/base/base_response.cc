#include "coord/base/base_response.h"
#include "coord/base/base_agent.h"
#include "coord/base/base_request.h"
#include "coord/coordx.h"
#include "coord/coord.h"
namespace coord {

RC_IMPLEMENT(base_response, "coord::base_response")

base_response::base_response(Coord* coord, base_agent* agent, base_request* request) : table(coord) {
    this->coord = coord;
    this->Code = 0;
    this->agent = agent;
    this->request = request;
    this->DataType = base_message_data_type_none;
    this->ReqTime = uv_hrtime();
}

base_response::~base_response() {
}

void base_response::Resolve() {
    this->Code = 0;
}

void base_response::Reject(int code) {
    this->Code = code;
}

void base_response::DebugLog() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%ld|%ld|%10s| RESPONSE | %s", 
            this->TypeName(), 
            this->request->SessionId, 
            this->request->Id, 
            coordx::date::FormatNano(duration), 
            this->request->Route.c_str()
            );
}

void base_response::onDestory() {
    this->DebugLog();
    this->Flush();
}


}
