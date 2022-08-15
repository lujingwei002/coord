#include "coord/event/event_mgr.h"
#include "coord/coord.h"
#include "coord/component/script_component.h"
#include <limits>

namespace coord {
namespace event {

EventMgr* newEventMgr(Coord* coord) {
    EventMgr* self = new EventMgr(coord);
    return self; 
}

EventMgr::EventMgr(Coord* coord) : coord(coord) {
}

EventMgr::~EventMgr() {
}

bool EventMgr::removeListener(Listener* listener) {
    if (listener == nullptr) {
        return false;
    }
    auto ret = this->listenerDict.equal_range(listener->name);
    for(auto it = ret.first; it != ret.second; ++it){
        if(it->second == listener){
            this->listenerDict.erase(it);
            return true;
        }
    }
    return false;
}

Listener* EventMgr::AddListener(const char* name, Function func) {
    Listener* listener = new Listener(this->coord, this, name, func);
    this->listenerDict.insert(std::pair<std::string, Listener*>(name, listener));
    return listener;
}

Listener* EventMgr::addListener(const char* name, ScriptComponent* object, int ref) {
    Listener* listener = new Listener(this->coord, this, name, object, ref);
    this->listenerDict.insert(std::pair<std::string, Listener*>(name, listener));
    return listener;
}

int EventMgr::AddListener(lua_State* L) {
    #ifndef TOLUA_RELEASE
    tolua_Error tolua_err;
    if (
        !tolua_isusertype(L,1,"coord::event::EventMgr",0,&tolua_err) ||
        !tolua_isusertype(L,2,"coord::ScriptComponent",0,&tolua_err) ||
        !tolua_isstring(L,3,0,&tolua_err) ||
        !tolua_isfunction(L,4,0,&tolua_err) ||
        !tolua_isnoobj(L,5,&tolua_err)
    )
        goto tolua_lerror;
    else 
#endif
    {
        coord::ScriptComponent* object = ((coord::ScriptComponent*)  tolua_tousertype(L,2,0));
        const char* name = (const char*)tolua_tostring(L, 3, 0);
        lua_pushvalue(L, 4);
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX);
        if (ref < 0) {
            tolua_error(L, "error in function 'AddListener'.\nattempt to set a nil function", NULL);
            return 0;
        }
        Listener* tolua_ret = (Listener*)  this->addListener(name, object, ref);
        tolua_pushusertype_and_takeownership(L,(void*)tolua_ret,"coord::event::Listener");
    }
    return 1;
#ifndef TOLUA_RELEASE
    tolua_lerror:
    tolua_error(L,"#ferror in function 'AddListener'.",&tolua_err);
    return 0;
#endif
}

bool EventMgr::HasListener(const char* name) {
    auto it = this->listenerDict.find(name);
    return it != this->listenerDict.end();
}

void EventMgr::Emit(const char* name, BaseEvent* args) {
    auto ret = this->listenerDict.equal_range(name);
    for(auto it = ret.first; it != ret.second; ++it){
        Listener* listener = it->second;
        (*listener)(args);
    }
}

}
}