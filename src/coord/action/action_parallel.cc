#include "coord/action/action_parallel.h"
#include "coord/action/action.h"
#include "coord/action/action_animation.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"

namespace coord {
namespace action {
CC_IMPLEMENT(parallel_action, "coord::action::parallel_action")

parallel_action::parallel_action(Coord* coord) : Action(coord) {
    
}

parallel_action::~parallel_action() {
    for(const auto it : this->actionArr) {
        this->coord->Destory(it);
    }
    this->actionArr.clear();
}

void parallel_action::Next() {
    throw new NotImplementException("coord::action::parallel_action::Next");
}

void parallel_action::push(Action* action) {
    this->actionArr.push_back(action);
}

void parallel_action::execute() {
    if (this->actionArr.size() <= 0) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
    for (auto const it : this->actionArr) {
        it->execute();
    }
}

void parallel_action::onComplete(Action* action) {
    auto it = this->actionDict.find(action);
    if (it != this->actionDict.end()) {
        this->coord->CoreLogError("[action::parallel_action] onComplete failed, action=%p, error='action already onCompleteed'", action);
        return;
    }
    this->actionDict[action] = true;
    if (this->actionDict.size() >= this->actionArr.size()) {
        if (this->parent)this->parent->onComplete(this);
        return;
    }
}

void parallel_action::onAbort(Action* action) {
    if (this->actionArr.size() <= 0) {
        if (this->parent)this->parent->onAbort(this);
        return;
    }
    for (auto const it : this->actionArr) {
        it->abortByParent(this);
    }
    if (this->parent)this->parent->onAbort(this);
}

}
}