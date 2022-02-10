#include "coord/closure/closure_action.h"
#include "coord/coord.h"

namespace coord {
namespace closure {



closure_action::closure_action(Coord* coord, Closure* closure) {
    this->coord = coord;
    this->closure = closure;
    this->parent = NULL;
    this->isAbort = false;
}

closure_action::~closure_action() {
    
}

void closure_action::execute() {
    
}

void closure_action::onComplete(closure_action* action) {
    if (this->isAbort) return;
    if (this->parent) this->parent->onComplete(this);
}

void closure_action::onAbort() {
    this->isAbort = true;
}


}

}