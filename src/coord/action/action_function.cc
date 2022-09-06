#include "coord/action/action_function.h"
#include "coord/action/action.h"
#include "coord/action/action_animation.h"
#include "coord/coord.h"

namespace coord {
namespace action {

RC_IMPLEMENT(function_action, "coord::action::function_action")

function_action::function_action(Coord* coord, Function func) : Action(coord) {
    this->func = func;
}

function_action::~function_action() {
}

void function_action::Next() {
    if (this->parent) this->parent->onComplete(this);
}

void function_action::execute() {
    if (this->func) {
        this->func(this);
    }   
}

void function_action::Abort() {
    if (this->parent) this->parent->onAbort(this);
}

}
}