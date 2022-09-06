#include "coord/managed/managed_promise.h"
#include "coord/managed/managed.h"
#include "coord/coord.h"
namespace coord {
namespace managed {

RC_IMPLEMENT(ManagedPromise, "coord::managed::ManagedPromise")

ManagedPromise::ManagedPromise(Coord *coord) : base_promise(coord) {
}

ManagedPromise::~ManagedPromise() {
}

}
}
