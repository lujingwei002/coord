#include "coord/managed/managed_result.h"
#include "coord/coord.h"

namespace coord {
namespace managed {

CC_IMPLEMENT(ManagedResult, "coord::managed::ManagedResult")

ManagedResult::ManagedResult(Coord* coord) : base_result(coord) {
}

ManagedResult::~ManagedResult() {
}



}
}
