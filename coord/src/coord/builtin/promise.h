#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include <uv.h>
#include <map>
#include <functional>
#include <any>
#include <tuple>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}


namespace coord {//tolua_export

class Coord;
class ScriptComponent;

 
typedef std::function<void ()> Promise_Resolve; 
typedef std::function<void ()> Promise_Reject;

class Promise : public Destoryable { //tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord* coord);
    virtual ~Promise();
public:

    void resolve();
    void reject();

    Promise* Then(Promise_Resolve func);
    Promise* Else(Promise_Reject func);
    int Then(lua_State* L);                             //tolua_export
    int Else(lua_State* L);                             //tolua_export
    Promise* Then(ScriptComponent* object, int ref);
    Promise* Else(ScriptComponent* object, int ref);
private:
    Promise_Resolve     resolveFunc;
    Promise_Reject      rejectFunc;
protected:
    int                 resolveRef;
    int                 rejectRef;
public:
    Coord*              coord;
};//tolua_export

Promise* newPromise(Coord* coord);


}//tolua_export


