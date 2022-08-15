#pragma once 

#include "coord/coordx.h"
#include "coord/closure/closure_action.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;

namespace closure {

class closure_action;

class closure_sequence : public closure_action {
CC_CLASS(closure_sequence);    
public:
    closure_sequence(Coord* coord, Closure* closure);
    virtual ~closure_sequence();
public:
    virtual void execute();
    virtual void onAbort();
public:
    virtual void onComplete(closure_action* action);
    virtual void addInstruction(closure_action* action);
public:
    size_t                          progress;
    closure_action*                 action;
    std::vector<closure_action*>    actionArr;

};


}
}
