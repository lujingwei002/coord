#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/slice.h"
#include "coord/event/event.h"
#include "coord/event/event_listener.h"
#include <functional>
#include <libuv/uv.h>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {//tolua_export

class Coord;
class ScriptComponent;

namespace event {//tolua_export
 
/// #example
/// '''
/// auto listener = coorda->Event->AddListener("login", xx);
/// coorda->Event->Emit("login", event);
/// delete listener;
/// '''

class EventMgr {//tolua_export
public:
    EventMgr(Coord* coord);
    virtual ~EventMgr();
public:
    Listener* AddListener(const char* name, Function func); 
    bool On(const char* name, Function func);
    int AddListener(lua_State* L);                          //tolua_export
    bool HasListener(const char* name);                     //tolua_export                            
    void Emit(const char* name, BaseEvent* args);           //tolua_export
public:
    Listener* addListener(const char* name, ScriptComponent* object, int ref);
    bool removeListener(Listener* listener);
public:
    Coord*                                 coord;
    std::multimap<std::string, Listener*>  listenerDict;
};//tolua_export

EventMgr* newEventMgr(Coord* coord);

inline bool EventMgr::On(const char* name, Function func) {
    return this->AddListener(name, func);
}

}//tolua_export
}//tolua_export



