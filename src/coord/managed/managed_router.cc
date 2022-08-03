#include "coord/managed/managed_router.h"
#include "coord/managed/managed.h"
#include "coord/base/base_router.h"
#include "coord/coord.h"
namespace coord {
namespace managed {

CC_IMPLEMENT(ManagedRouter, "coord::managed::ManagedRouter")

ManagedRouter::ManagedRouter(Coord *coord, Managed* managed) : base_router(coord) {
    this->managed = managed;
}

ManagedRouter::~ManagedRouter() {
}

}
}  
