#include "coord/gate/gate_request.h"
#include "coord/gate/gate_agent.h"
#include "coord/coord.h"
#include "coord/gate/gate.h"
#include "coord/gate/gate_response.h"
#include "coord/protobuf/init.h"

namespace coord {

namespace gate {
CC_IMPLEMENT(GateResponse, "coord::gate::GateResponse")

GateResponse::GateResponse(Coord* coord, GateAgent* agent, GateRequest* request) : internal_response(coord, agent, request) {
}

GateResponse::~GateResponse() {

}

int GateResponse::flush() {
    /*  
    GateRequest* request = this->request;
    GateAgent* agent = this->request->agent; 
    if(this->proto != nullptr){
        return agent->response(request->Id, request->Route.c_str(), this->proto->GetMessage());
    } else {
        return agent->response(request->Id, request->Route.c_str(), this->payload);
    }*/
    return 0;
}


}

}
