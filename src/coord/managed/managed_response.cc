#include "coord/managed/managed_response.h"
#include "coord/managed/managed_request.h"
#include "coord/managed/managed_agent.h"
#include "coord/coord.h"

namespace coord {

namespace managed {
CC_IMPLEMENT(ManagedResponse, "coord::managed::ManagedResponse")

ManagedResponse::ManagedResponse(Coord* coord, ManagedAgent* agent, ManagedRequest* request) : internal_response(coord, agent, request) {
}

ManagedResponse::~ManagedResponse() {
}

}

}
