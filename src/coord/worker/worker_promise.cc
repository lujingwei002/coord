#include "coord/worker/worker_promise.h"
#include "coord/coord.h"
namespace coord {
namespace worker {

RC_IMPLEMENT(Promise, "coord::worker::Promise")

Promise::Promise(Coord *coord) : base_promise(coord) {
}

Promise::~Promise() {
}

}
}
