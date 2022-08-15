#pragma once 

#include "coord/builtin/inc.h"
#include <functional>
#include <vector>

namespace coord {
    
class Coord;

namespace closure {

class Closure;

class closure_action : public RcObject {
public:
    closure_action(Coord* coord, Closure* closure);
    virtual ~closure_action();
public:
    /// 执行动作
    virtual void execute();
    /// 子动作完成时触发
    virtual void onComplete(closure_action* action);
    virtual void onAbort();
public:
    Coord*          coord;
    Closure*        closure;
    closure_action* parent;
    bool            isAbort;

};

}
}