#include "coord/managed/managed_notify.h"
#include "coord/managed/managed_agent.h"
#include "coord/managed/managed_server.h"
#include "coord/coord.h"
#include <cctype>

namespace coord {

namespace managed {
CC_IMPLEMENT(ManagedNotify, "coord::managed::ManagedNotify")

ManagedNotify::ManagedNotify(Coord* coord, ManagedAgent* agent) : base_notify(coord, agent) {
}

ManagedNotify::~ManagedNotify() {
}

}

}
