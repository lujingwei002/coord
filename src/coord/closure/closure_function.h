#pragma once 

#include "coord/coordx.h"
#include "coord/closure/closure_action.h"
#include "coord/closure/closure_base.h"
#include <functional>
#include <vector>

namespace coord {
class Coord;
namespace closure {

class Closure;


class closure_function : public closure_action {
RC_CLASS(closure_function);
public:
    closure_function(Coord*  coord, Closure* closure, Function func);
    virtual ~closure_function();
public:
    virtual void execute();
public:
    Function func;

};

}
}