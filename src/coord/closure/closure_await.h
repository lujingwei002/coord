#pragma once 

#include "coord/builtin/init.h"
#include "coord/closure/closure_action.h"
#include "coord/closure/closure_base.h"
#include "coord/closure/closure_promise.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace closure {

class Closure;


class closure_await : public closure_action {
CC_CLASS(closure_await);
public:
    closure_await(Coord*  coord, Closure* closure, AwaitFunction func, Function thenFunc, Function catchFunc);
    virtual ~closure_await();
public:
    virtual void execute();
    void reslove();
    void reject();
public:
    ClosurePromise promise;
    AwaitFunction func;
    Function thenFunc;
    Function catchFunc;

};

}
}