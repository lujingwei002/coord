#include "coord/action/action.h"
#include "coord/action/action_animation.h"
#include "coord/coord.h"

namespace coord {
namespace action {



Action::Action(Coord* coord) {
    this->coord = coord;
    this->parent = NULL;
}

Action::~Action() {
    
}

void Action::Next() {
    
}

void Action::execute() {
    
}

void Action::onComplete(Action* action) {

}

void Action::onAbort(Action* action) {

}

void Action::Abort() {

}

void Action::abortByParent(Action* action) {

}
}

}