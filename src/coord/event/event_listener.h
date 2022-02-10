#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/slice.h"
#include "coord/event/event.h"
#include <functional>
#include <uv.h>
#include <map>

namespace coord {//tolua_export

class Coord;
class ScriptComponent;

namespace event {//tolua_export

class EventMgr;
typedef std::function<void (BaseEvent* args)> Function; 

class Listener  {//tolua_export
CC_CLASS(Listener);
public:
    Listener(Coord* coord, EventMgr* mgr, std::string name, Function func);
    Listener(Coord* coord, EventMgr* mgr, std::string name, ScriptComponent* object, int ref);
    virtual ~Listener();
public:
    void Remove();                          //tolua_export
    void operator()(BaseEvent* args);
public:
    Coord*              coord;
    EventMgr*           mgr;
    std::string         name;
    Function            func;
    int                 luaRef;
};//tolua_export

inline void Listener::operator()(BaseEvent* args) {
    this->func(args);
}

// class listener {
// public:
// };

}//tolua_export
}//tolua_export



