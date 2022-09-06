#include "coord/action/action_animation.h"
#include "coord/action/action_sequence.h"
#include "coord/action/action_parallel.h"
#include "coord/action/action_wait.h"
#include "coord/action/action.h"
#include "coord/coord.h"

namespace coord {
namespace action {
RC_IMPLEMENT(Animation, "coord::action::Animation")
Animation* newAnimation(Coord* coord) {
    Animation* self = new Animation(coord);
    return self;
}

Animation::Animation(Coord* coord) : Action(coord) {
    this->action = nullptr;
}

Animation::~Animation() {
    if (this->action != nullptr) {
        this->coord->Destory(this->action);
        this->action = nullptr;
    }
}

Action* Animation::Sequence(Action* action, ...) {
    va_list args;
    va_start(args, action);
    sequence_action* sequence = new sequence_action(this->coord);
    while (action) {
        action->parent = sequence;
        sequence->push(action);
        action = va_arg(args, Action*);
    }
    va_end(args); 
    return sequence;
}


Action* Animation::Parallel(Action* action, ...) {
    va_list args;
    va_start(args, action);
    parallel_action* parallel = new parallel_action(this->coord);
    while (action) {
        action->parent = parallel;
        parallel->push(action);
        action = va_arg(args, Action*);
    }
    va_end(args); 
    return parallel;
}

int Animation::Run(Action* action) {
    if (this->action != nullptr) {
        return -1;
    }
    if (action == nullptr) {
        return -1;
    }
    action->parent = this;
    this->action = action;
    this->action->execute();
    return 0;
}

Action* Animation::Call(Function func) {
    Action* action = new function_action(this->coord, func);
    return action;
}

Action* Animation::Wait(uint64_t msec) {
    Action* action = new wait_action(this->coord, msec);
    return action;
}

void Animation::onComplete(Action* action) {
    if (this->action != action) {
        this->coord->CoreLogError("[action::Animation] onComplete failed, action=%p, error='action already onCompleteed'", action);
        return;
    }
    this->coord->Destory(this);
}

void Animation::onAbort(Action* action) {
    printf("hello abort\n");
    this->coord->Destory(this);
}

}
}