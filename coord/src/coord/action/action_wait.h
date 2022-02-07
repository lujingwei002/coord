#pragma once 

#include "coord/builtin/init.h"
#include "coord/action/action.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace action {

class Action;

class wait_action : public Action {
CC_CLASS(wait_action);  
public:
    wait_action(Coord*  coord, uint64_t msec);
    virtual ~wait_action();
public:
    virtual void Next();
    virtual void Abort();
    virtual void abortByParent(Action* action);
public:
    virtual void execute();
public:
    uint64_t    msec;
    int         id;

};

}
}