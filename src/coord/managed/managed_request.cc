#include "coord/managed/managed_request.h"
#include "coord/managed/managed_agent.h"
#include "coord/managed/managed_server.h"
#include "coord/coord.h"
#include <cctype>

namespace coord {
namespace managed {

RC_IMPLEMENT(ManagedRequest, "coord::managed::ManagedRequest")

ManagedRequest::ManagedRequest(Coord* coord, ManagedAgent* agent) : base_request(coord, agent) {
    this->response = new ManagedResponse(this->coord, agent, this);
}

ManagedRequest::~ManagedRequest() {
}

ManagedResponse* ManagedRequest::GetResponse() {
    return dynamic_cast<ManagedResponse*>(this->response);
}

}

}
