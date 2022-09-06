#include "coord/action/action_sequence.h"
#include "coord/action/action.h"
#include "coord/action/action_animation.h"
#include "coord/coordx.h"
#include "coord/coord.h"

namespace coord {
namespace action {
RC_IMPLEMENT(sequence_action, "coord::action::sequence_action")

sequence_action::sequence_action(Coord* coord) : Action(coord) {
    this->progress = 0;
    this->action = nullptr;
}

sequence_action::~sequence_action() {
    for(const auto it : this->actionArr) {
        this->coord->Destory(it);
    }
    this->actionArr.clear();
}

void sequence_action::Next() {
    throw new NotImplementException("coord::action::sequence_action::Next");
}

void sequence_action::push(Action* action) {
    this->actionArr.push_back(action);
}

void sequence_action::execute() {
    if (this->progress >= this->actionArr.size()) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
    Action* action = this->actionArr[this->progress];
    this->action = action;
    this->progress++;
    action->execute();
}

void sequence_action::onComplete(Action* action) {
    if (this->action != action) {
        return;
    }
    if (this->progress >= this->actionArr.size()) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
    this->execute();
}

void sequence_action::onAbort(Action* action) {
    if (this->action != action) {
        return;
    }    
    if (this->parent)this->parent->onAbort(this);
}

}
}