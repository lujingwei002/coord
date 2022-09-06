#pragma once 
#include "coord/coordx.h"
#include "coord/closure/closure_action.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace closure {

class Closure;

class closure_wait : public closure_action {
RC_CLASS(closure_wait);  
public:
    closure_wait(Coord*  coord, Closure* closure, uint64_t msec);
    virtual ~closure_wait();
public:
    virtual void onAbort();
    virtual void execute();
public:
    uint64_t    msec;
    int         id;

};

}
}