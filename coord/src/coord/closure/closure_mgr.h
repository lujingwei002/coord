#pragma once 

#include "coord/builtin/init.h"
#include "coord/closure/closure.h"
#include <functional>
#include <vector>

namespace coord {//tolua_export

class Coord;

namespace closure {//tolua_export

class Closure;

class Sequence;

class ClosureMgr {//tolua_export
public:
    ClosureMgr(Coord*  coord);
    ~ClosureMgr();
public:

    template<class... T>
    Closure* Function(T... args) {
        auto closure = new Closure(this->coord);
        closure->createArg(args...);
        return closure;
    }
public:
    Coord*  coord;
};//tolua_export

ClosureMgr* newClosureMgr(Coord *coord);

}//tolua_export
}//tolua_export