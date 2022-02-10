#include "coord/closure/closure_function.h"
#include "coord/closure/closure.h"
#include "coord/coord.h"

namespace coord {
namespace closure {

CC_IMPLEMENT(closure_function, "coord::closure::closure_function")

closure_function::closure_function(Coord* coord, Closure* closure, Function func) : closure_action(coord, closure) {
    this->func = func;
}

closure_function::~closure_function() {
}

void closure_function::execute() {
    if (this->func) {
        this->func(this->closure);
    }   
    if (this->parent) this->parent->onComplete(this);
}

}
}