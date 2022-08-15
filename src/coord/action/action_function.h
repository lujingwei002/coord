#pragma once 

#include "coord/coordx.h"
#include "coord/action/action.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace action {

class Action;
typedef std::function<void (Action* action)> Function; 

class function_action : public Action {
CC_CLASS(function_action);
public:
    function_action(Coord*  coord, Function func);
    virtual ~function_action();
public:
    virtual void Next();
    virtual void Abort();
public:
    virtual void execute();
public:
    Function func;

};

}
}