#pragma once 

#include "coord/builtin/init.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace action {

class Action;

class Sequence;

class Action : public RcObject {
public:
    Action(Coord*  coord);
    virtual ~Action();
public:
    virtual void Next();
    virtual void Abort();
public:
    /// 执行动作
    virtual void execute();
    /// 子动作完成时触发
    virtual void onComplete(Action* action);
    /// 子动作中断时触发
    virtual void onAbort(Action* action);
    // 被父动作中断
    virtual void abortByParent(Action* action);
public:
    Coord*  coord;
    Action* parent;

};

}
}