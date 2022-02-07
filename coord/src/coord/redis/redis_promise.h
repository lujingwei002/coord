#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/promise.h"
#include <libuv/uv.h>
#include <vector>
#include <iostream>
#include <stdint.h>
#include <map>
#include <functional>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include <hiredis/hiredis.h>
#include <hiredis/async.h>
namespace coord {//tolua_export
    
class Coord;
class ScriptComponent;

namespace redis {//tolua_export

class Reply;
class AsyncClient;

typedef std::function<void (AsyncClient* client, Reply& reply)> PromiseResolveFunction; 
typedef std::function<void (AsyncClient* client, Reply& reply)> PromiseRejectFunction; 

class Promise: public Destoryable {//tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord *coord);
    virtual ~Promise();
 public:
    Promise* Then(PromiseResolveFunction func);
    Promise* Else(PromiseRejectFunction func);
    int Then(lua_State* L);             //tolua_export
    int Else(lua_State* L);             //tolua_export;
public:
    Promise* then(ScriptComponent* object, int ref);
    Promise* else_(ScriptComponent* object, int ref);
    void reject(AsyncClient* client, Reply& reply);
    void resolve(AsyncClient* client, Reply& reply);
    void reject(AsyncClient* client, std::nullptr_t);
    void resolve(AsyncClient* client, std::nullptr_t);
public:
    Coord*                  coord;
    PromiseResolveFunction  resolveFunc;
    PromiseRejectFunction   rejectFunc;
    int                     resolveRef;
    int                     rejectRef;
};//tolua_export

Promise* newPromise(Coord* coord);
}//tolua_export
}//tolua_export


