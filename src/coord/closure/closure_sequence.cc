#include "coord/closure/closure_sequence.h"
#include "coord/closure/closure_action.h"
#include "coord/closure/closure.h"
#include "coord/coordx.h"
#include "coord/coord.h"

namespace coord {

namespace closure {
RC_IMPLEMENT(closure_sequence, "coord::closure::closure_sequence")

closure_sequence::closure_sequence(Coord* coord, Closure* closure) : closure_action(coord, closure) {
    this->progress = 0;
    this->action = nullptr;
}

closure_sequence::~closure_sequence() {
    for(const auto it : this->actionArr) {
        this->coord->Destory(it);
    }
    this->actionArr.clear();
}

void closure_sequence::addInstruction(closure_action* action) {
    action->parent = this;
    this->actionArr.push_back(action);
}

void closure_sequence::execute() {
    if (this->progress >= this->actionArr.size()) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
    closure_action* action = this->actionArr[this->progress];
    this->action = action;
    this->progress++;
    action->execute();
}

void closure_sequence::onComplete(closure_action* action) {
    if (this->action != action) {
        return;
    }
    if (this->isAbort)return;
    if (this->progress >= this->actionArr.size()) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
    this->execute();
}

void closure_sequence::onAbort() {
    closure_action::onAbort();
    for (const auto it : this->actionArr) {
        it->onAbort();
    }
}

}
}