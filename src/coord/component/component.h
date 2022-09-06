#pragma once 

#include "coord/object/object.h"
#include "coord/coordx.h"
#include <cstdlib>
#include <map>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
class TestA{

};
namespace coord {//tolua_export

class EventListener;
class IEventHandler;
class EventArgs;
class Object;
class Coord;
class Scene;
class Component {//tolua_export
RC_CLASS(Component)
public:
    Component(Coord* coord);
    virtual ~Component();

    int GetFunction(const char *func);
    int TraceStack(); 
   
    
    Object *GetObject();
    void SetObject(Object* object);
    Scene* GetScene();

    int GetComponent(lua_State* L);
    Component* GetComponent(const char* name);//tolua_export

    virtual void AddHttpRouterGet(const char* pattern, const char* callback);//tolua_export
    virtual void Log(const char* str) const;//tolua_export
    virtual void LogFatal(const char* str) const;//tolua_export
    virtual void LogError(const char* str) const;//tolua_export
    virtual void LogWarn(const char* str) const;//tolua_export
    virtual void LogInfo(const char* str) const;//tolua_export
    virtual void LogDebug(const char* str) const;//tolua_export
    virtual void LogMsg(const char* str) const;//tolua_export
public:
    virtual void onAwake();
    virtual void onStart();
    virtual void onDestory();
    virtual void onUpdate(uint64_t cur_tick);
    virtual void onReload();
    void CoreLogFatal(const char* fmt, ...);
    void CoreLogError(const char* fmt, ...);
    void CoreLogWarn(const char* fmt, ...);
    void CoreLogInfo(const char* fmt, ...);
    void CoreLogDebug(const char* fmt, ...);
    void CoreLogMsg(const char* fmt, ...);
public:
    Object*     object; //tolua_export
    Scene*      scene;  //tolua_export
    Coord*      coord;  //tolua_export
    bool        isStart;
public:
    template<class T>
    T* GetComponent();
protected:
    lua_State*  GetLuaState();
};//tolua_export

template<class T>T* Component::GetComponent()
{
    return (T*)this->object->GetComponent(T::type);
}
}//tolua_export
