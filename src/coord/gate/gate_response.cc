#include "coord/gate/gate_request.h"
#include "coord/gate/gate_agent.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_response.h"
#include "coord/protobuf/init.h"

namespace coord {

namespace gate {
CC_IMPLEMENT(GateResponse, "coord::gate::GateResponse")

GateResponse* newGateResponse(Coord* coord, GateRequest* request) {
    GateResponse* response = new GateResponse(coord, request);
    return response;
}

GateResponse::GateResponse(Coord* coord, GateRequest* request) : BaseResponse(coord) {
    this->request = request;
}

GateResponse::~GateResponse() {

}

int GateResponse::flush() {
    GateRequest* request = this->request;
    GateAgent* agent = this->request->agent; 
    if(this->proto != nullptr){
        return agent->response(request->id, request->route.c_str(), this->proto.GetMessage());
    } else {
        return agent->response(request->id, request->route.c_str(), this->payload);
    }
}


}

}