#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
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

class CacheReader;
class AsyncClient;

typedef std::function<void (AsyncClient* client, CacheReader& reader)> PromiseResolveFunction; 
typedef std::function<void (AsyncClient* client, CacheReader& reader)> PromiseRejectFunction; 

class Promise: public Destoryable {//tolua_export
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
    void reject(AsyncClient* client, CacheReader& reader);
    void resolve(AsyncClient* client, CacheReader& reader);
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


