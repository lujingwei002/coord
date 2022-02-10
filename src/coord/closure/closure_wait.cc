#include "coord/closure/closure_wait.h"
#include "coord/closure/closure.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"

namespace coord {
namespace closure {
CC_IMPLEMENT(closure_wait, "coord::closure::closure_wait")

closure_wait::closure_wait(Coord* coord, Closure* closure, uint64_t msec) : closure_action(coord, closure) {
    this->msec = msec;
    this->id = 0;
}

closure_wait::~closure_wait() {
    if (this->id) {
        this->coord->ClearTimeout(this->id);
        this->id = 0;
    }
}

void closure_wait::execute() {
    this->id = this->coord->SetTimeout(this->msec, [this](){
        this->id = 0;
        if (this->isAbort)return 0;
        if (this->parent) this->parent->onComplete(this);
        return 0;
    });
}

void closure_wait::onAbort() {
    closure_action::onAbort();
    if (this->id) {
        this->coord->ClearTimeout(this->id);
        this->id = 0;
    }
}

}
}