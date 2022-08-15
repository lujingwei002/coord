#pragma once 
#include "coord/coordx.h"
#include <functional>
#include <vector>

namespace coord {
    
class Coord;

namespace closure {

class Closure;
class closure_await;

class ClosurePromise : public coordx::RcObject {
CC_CLASS(ClosurePromise); 
public:
    ClosurePromise(Coord* coord, Closure* closure, closure_await* await);
    virtual ~ClosurePromise();
public:
    void Reslove();
    void Reject();
public:
    Coord*          coord;
    Closure*        closure;
    closure_await*  await;
};

}
}