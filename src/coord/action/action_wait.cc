#include "coord/action/action_wait.h"
#include "coord/action/action.h"
#include "coord/action/action_animation.h"
#include "coord/coordx.h"
#include "coord/coord.h"

namespace coord {
namespace action {
RC_IMPLEMENT(wait_action, "coord::action::wait_action")

wait_action::wait_action(Coord* coord, uint64_t msec) : Action(coord) {
    this->msec = msec;
    this->id = 0;
}

wait_action::~wait_action() {
    if (this->id) {
        this->coord->ClearTimeout(this->id);
        this->id = 0;
    }
}

void wait_action::Next() {
    throw new NotImplementException("coord::action::wait_action::Next");
}

void wait_action::Abort() {

}

void wait_action::execute() {
    this->id = this->coord->SetTimeout(this->msec, [this](){
        this->id = 0;
        if (this->parent) this->parent->onComplete(this);
        return 0;
    });
}

void wait_action::abortByParent(Action* action) {
    if (this->id) {
        this->coord->ClearTimeout(this->id);
        this->id = 0;
    }
}

}
}