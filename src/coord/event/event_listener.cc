#include "coord/event/event_listener.h"
#include "coord/event/event_mgr.h"
#include "coord/log/log.h"
#include "coord/component/script_component.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include <limits>

namespace coord {
namespace event {

CC_IMPLEMENT(Listener, "coord::event::Listener")

Listener::Listener(Coord* coord, EventMgr* mgr, std::string name, Function func) 
    : coord(coord), mgr(mgr), name(name), func(func), luaRef(LUA_NOREF) {
}

Listener::Listener(Coord* coord, EventMgr* mgr, std::string name, ScriptComponent* object, int ref) 
    : coord(coord), mgr(mgr), name(name), luaRef(ref) {
    this->func = std::bind(&ScriptComponent::recvEvent, object, std::placeholders::_1, "recvEvent", ref);
}

Listener::~Listener() {
    if (this->mgr == nullptr) {
        return;
    }
    this->mgr->removeListener(this);
    this->mgr = nullptr;
    if (this->luaRef < 0) {
        return;
    }
    lua_unref(this->coord->Script->L, this->luaRef);
    this->luaRef = LUA_NOREF;
}

void Listener::Remove() {
    if (this->mgr == nullptr) {
        return;
    }
    this->mgr->removeListener(this);
    this->mgr = nullptr;
    if (this->luaRef < 0) {
        return;
    }
    lua_unref(this->coord->Script->L, this->luaRef);
    this->luaRef = LUA_NOREF;
}

}
}