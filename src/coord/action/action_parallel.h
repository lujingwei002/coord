#pragma once 

#include "coord/builtin/init.h"
#include "coord/action/action.h"
#include <functional>
#include <vector>
#include <map>

namespace coord {
class Coord;
namespace action {

class Action;

class parallel_action : public Action {
CC_CLASS(parallel_action);
public:
    parallel_action(Coord*  coord);
    virtual ~parallel_action();
public:
    virtual void Next();
public:
    virtual void execute();
    virtual void onComplete(Action* action);
    virtual void onAbort(Action* action);
    void push(Action* action);
public:
    std::vector<Action*> actionArr;
    std::map<Action*, bool> actionDict;
};


}
}