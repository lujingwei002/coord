#pragma once 

#include "coord/builtin/init.h"
#include "coord/action/action_function.h"
#include "coord/action/action.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace action {

class Action;
class Animation : public Action {
CC_CLASS(Animation);
public:
    Animation(Coord*  coord);
    ~Animation();
public:
    Action* Sequence(Action* action, ...);
    Action* Parallel(Action* action, ...);
    Action* Wait(uint64_t msec);
    Action* Call(Function func);
    int Run(Action* action);
public:
    virtual void onComplete(Action* action);
    virtual void onAbort(Action* action);
public:
    Action* action;
};

Animation* newAnimation(Coord* coord);
}
}