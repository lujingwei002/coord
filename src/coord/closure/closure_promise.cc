#include "coord/closure/closure_promise.h"
#include "coord/closure/closure_await.h"
#include "coord/coord.h"

namespace coord {
namespace closure {

RC_IMPLEMENT(ClosurePromise, "coord::closure::ClosurePromise")

ClosurePromise::ClosurePromise(Coord* coord, Closure* closure, closure_await* await) {
    this->coord = coord;
    this->closure = closure;
    this->await = await;
}

ClosurePromise::~ClosurePromise() {
    
}

void ClosurePromise::Reslove() {
    this->await->reslove();
}

void ClosurePromise::Reject() {
    this->await->reject();
}

}

}