#pragma once 

#include "coord/coordx.h"
#include <uv.h>
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

namespace coord {//tolua_export
    
class Coord;
class ScriptComponent;

namespace cache {//tolua_export

class CacheResult;
class AsyncClient;

typedef std::function<void (AsyncClient* client, CacheResult* result)> PromiseResolveFunction; 
typedef std::function<void (AsyncClient* client, CacheResult* result)> PromiseRejectFunction; 

class Promise: public coordx::RcObject {//tolua_export
CC_CLASS(Promise);
public:
    Promise(Coord *coord, AsyncClient* client);
    virtual ~Promise();
public:
    int Then(lua_State* L);             //tolua_export
    int Else(lua_State* L);             //tolua_export;
    Promise* Then(PromiseResolveFunction func);
    Promise* Else(PromiseRejectFunction func);
public:
    Promise* then(ScriptComponent* object, int ref);
    Promise* else_(ScriptComponent* object, int ref);
    void reject(AsyncClient* client, CacheResult* result);
    void resolve(AsyncClient* client, CacheResult* result);
    void reject(AsyncClient* client, std::nullptr_t);
    void resolve(AsyncClient* client, std::nullptr_t);
public:
    Coord*                  coord;
    AsyncClient*            client;
    PromiseResolveFunction  resolveFunc;
    PromiseRejectFunction   rejectFunc;
    int                     resolveRef;
    int                     rejectRef;
};//tolua_export

Promise* newPromise(Coord* coord, AsyncClient* client);
}//tolua_export
}//tolua_export


