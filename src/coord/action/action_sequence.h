#pragma once 

#include "coord/builtin/init.h"
#include "coord/action/action.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace action {

class Action;

class sequence_action : public Action {
CC_CLASS(sequence_action);    
public:
    sequence_action(Coord*  coord);
    virtual ~sequence_action();
public:
    virtual void Next();
public:
    virtual void execute();
    virtual void onComplete(Action* action);
    virtual void onAbort(Action* action);
    void push(Action* action);
public:
    size_t                  progress;
    Action*                 action;
    std::vector<Action*>    actionArr;

};


}
}