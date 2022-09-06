#include "coord/closure/closure_await.h"
#include "coord/closure/closure.h"
#include "coord/coord.h"

namespace coord {
namespace closure {

RC_IMPLEMENT(closure_await, "coord::closure::closure_await")

closure_await::closure_await(Coord* coord, Closure* closure, AwaitFunction func, Function thenFunc, Function catchFunc) : closure_action(coord, closure), promise(coord, closure, this) {
    this->func = func;
    this->thenFunc = thenFunc;
    this->catchFunc = catchFunc;
}

closure_await::~closure_await() {
}

void closure_await::execute() {
    if (!this->func) {
        if (this->parent) this->parent->onComplete(this);
        return;
    }
    this->func(this->closure, &this->promise); 
}

void closure_await::reslove() {
    if (this->thenFunc) this->thenFunc(this->closure);
    if (this->isAbort)return;
    if (this->parent) this->parent->onComplete(this);
}

void closure_await::reject() {
    if (this->catchFunc) this->catchFunc(this->closure);
    if (this->isAbort)return;
    if (this->parent) this->parent->onComplete(this);
}

}
}