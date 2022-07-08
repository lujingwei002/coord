
#include "coord/component/script_component.h"
#include "coord/object/object.h"
#include "coord/scene/scene.h"
#include "coord/log/log.h"
#include "coord/http/http_request.h"
#include "coord/http/http_base.h"
#include "coord/websocket/websocket_agent.h"
#include "coord/websocket/websocket_frame.h"
#include "coord/gate/gate_request.h"
#include "coord/gate/gate_session.h"
#include "coord/cluster/cluster_request.h"
#include "coord/cluster/cluster_notify.h"
#include "coord/cluster/cluster_result.h"
#include "coord/worker/worker_request.h"
#include "coord/worker/worker_result.h"
#include "coord/worker/worker_notify.h"
#include "coord/builtin/exception.h"
#include "coord/event/init.h"
#include "coord/coord.h"
#include <string.h>
#include <typeinfo>       // operator typeid
namespace coord {

CC_IMPLEMENT(ScriptComponent, "coord::ScriptComponent")


ScriptComponent::ScriptComponent(Coord* coord, const char* scriptName, int ref) : Component(coord) {
    strcpy(this->scriptName, scriptName);
    this->tableRef = ref;
    this->onAwakeRef = 0;
    this->onStartRef = 0;
    this->onUpdateRef = 0;
    this->onDestoryRef = 0;
    this->onReloadRef = 0;
}

ScriptComponent::~ScriptComponent() {
    if(this->tableRef > 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->tableRef);
        this->tableRef = 0;
    }
    this->releaseRef();
}

const char* ScriptComponent::GetScriptName() {
    return this->scriptName;
}

int ScriptComponent::Log(lua_State* L) {
    static thread_local char buffer[4096];
    static thread_local char address[64];
    buffer[0] = 0;
    int argc = lua_gettop(L);
    for (int i = 2; i <= argc; i++) {
        if (lua_isstring(L, i)) {
            strcat(buffer, (const char*)lua_tostring(L, i));
        } else if (lua_isnil(L, i)) {
            strcat(buffer, "nil");
        } else if (lua_istable(L, i)) {
            sprintf(address, "%p", lua_topointer(L, i));
            strcat(buffer, "table: ");
            strcat(buffer, address);
        } else if (lua_isfunction(L, i)) {
            sprintf(address, "%p", lua_topointer(L, i));
            strcat(buffer, "function: ");
            strcat(buffer, address);
        } else if (lua_isuserdata(L, i)) {
            sprintf(address, "%p", lua_topointer(L, i));
            strcat(buffer, "userdata: ");
            strcat(buffer, address);
        } else if (lua_isboolean(L, i)) {
            strcat(buffer, lua_toboolean(L, i) ? "true" : "false");
        } else {
            sprintf(address, "%d", lua_type(L, i));
            strcat(buffer, "type: ");
            strcat(buffer, address);
        }
        strcat(buffer, "\t");
    }
    this->Log(buffer);
    return 0;
}

void ScriptComponent::Log(const char* str) const{;
    this->coord->Log("[%s] %s", scriptName, str);
}

void ScriptComponent::LogFatal(const char* str) const{;
    this->coord->LogFatal("[%s] %s", scriptName, str);
}

void ScriptComponent::LogError(const char* str) const{
    this->coord->CoreLogError("[%s] %s", scriptName, str);
}

void ScriptComponent::LogWarn(const char* str) const{
    this->coord->LogWarn("[%s] %s", scriptName, str);
}

void ScriptComponent::LogInfo(const char* str) const{
    this->coord->LogDebug("[%s] %s", scriptName, str);
}

void ScriptComponent::LogDebug(const char* str) const{
    this->coord->CoreLogDebug("[%s] %s", scriptName, str);
}

void ScriptComponent::LogMsg(const char* str) const{
    this->coord->LogMsg("[%s] %s", scriptName, str);
}

void ScriptComponent::loadRef() {
    lua_State* L = this->coord->Script->L;
    if (this->tableRef <= 0) {
        return;
    }
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->tableRef);// component
    lua_pushstring(L, "onAwake");//component 'onAwake'
    lua_gettable(L, -2);//component component.onAwake
    if (lua_isfunction(L, -1)) {
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX); //component
        this->onAwakeRef = ref;
    } else {
        lua_pop(L, 1);
    }
    lua_pushstring(L, "onUpdate");//component 'onAwake'
    lua_gettable(L, -2);//component component.onAwake
    if (lua_isfunction(L, -1)) {
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX); //component
        this->onUpdateRef = ref;
    } else {
        lua_pop(L, 1);
    }
    lua_pushstring(L, "onDestory");//component 'onAwake'
    lua_gettable(L, -2);//component component.onAwake
    if (lua_isfunction(L, -1)) {
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX); //component
        this->onDestoryRef = ref;
    } else {
        lua_pop(L, 1);
    }
    lua_pushstring(L, "onReload");//component 'onAwake'
    lua_gettable(L, -2);//component component.onAwake
    if (lua_isfunction(L, -1)) {
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX); //component
        this->onReloadRef = ref;
    } else {
        lua_pop(L, 1);
    }
    lua_pushstring(L, "onStart");//component 'onAwake'
    lua_gettable(L, -2);//component component.onAwake
    if (lua_isfunction(L, -1)) {
        int ref =  luaL_ref(L, LUA_REGISTRYINDEX); //component
        this->onStartRef = ref;
    } else {
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

void ScriptComponent::releaseRef() {
    if(this->onAwakeRef > 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->onAwakeRef);
        this->onAwakeRef = 0;
    }
    if(this->onUpdateRef > 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->onUpdateRef);
        this->onUpdateRef = 0;
    }
    if(this->onDestoryRef > 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->onDestoryRef);
        this->onDestoryRef = 0;
    }
    if(this->onReloadRef > 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->onReloadRef);
        this->onReloadRef = 0;
    }
    if(this->onStartRef > 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->onStartRef);
        this->onStartRef = 0;
    }
}

void ScriptComponent::onAwake() {
    this->loadRef();
    if (this->onAwakeRef <= 0) {
        return;
    }
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->onAwakeRef);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 0, 0) != 0){
        printf("ScriptComponent %s.onAwake error %s\n", this->scriptName, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::onStart() {
    this->loadRef();
    if (this->onStartRef <= 0) {
        return;
    }
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->onStartRef);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 0, 0) != 0){
        printf("ScriptComponent %s.onStart error %s\n", this->scriptName, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::onReload() {
    this->releaseRef();
    this->loadRef();
    if (this->onReloadRef <= 0) {
        return;
    }
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->onReloadRef);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 0, 0) != 0){
        printf("ScriptComponent %s.onReload error %s\n", this->scriptName, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::onUpdate(uint64_t cur_tick) {
    if (this->onUpdateRef <= 0) {
        return;
    }
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->onUpdateRef);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    lua_pushnumber(L, cur_tick);
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->CoreLogError("ScriptComponent %s.onUpdate error %s\n", this->scriptName, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::onDestory() {
    if (this->onDestoryRef <= 0) {
        return;
    }
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->onDestoryRef);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 0, 0) != 0) {
        this->CoreLogError("ScriptComponent %s.onDestory error %s\n", this->scriptName, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvHttpRequest(http::HttpRequest* request, int ref) {
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, request, "coord::http::HttpRequest");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.recvHttpRequest failed, error=%s", this->scriptName, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        throw http::HttpException("script error");
        return;
    }
    lua_pop(L, lua_gettop(L));
}

uint64_t ScriptComponent::recvTimer(const char* script, int ref) {
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 1, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        throw http::HttpException("script error");
        return 0;
    }
    uint64_t result = (uint64_t)lua_tonumber(L, -1);
    lua_pop(L, lua_gettop(L));
    return result;
}

void ScriptComponent::recvCron(const char* script, int ref) {
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        throw http::HttpException("script error");
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvWebSocket(websocket::Agent* agent, const char* script, int ref){
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, agent, "coord::websocket::Agent");
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->CoreLogError("ScriptComponent %s.%s recvWebSocketNew error %s", this->scriptName, script, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvWebSocketFrame(websocket::Agent* agent, websocket::Frame* frame, const char* script, int ref){
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, agent, "coord::websocket::Agent");
    tolua_pushusertype(L, frame, "coord::websocket::Frame");
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error %s", this->scriptName, script, lua_tostring(L, -1));
        lua_pop(L, lua_gettop(L));
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvEvent(event::BaseEvent* args, const char* script, int ref) {
    this->coord->CoreLogDebug("[ScriptComponent] recvEvent");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, args, args->TypeName());
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvPromise(const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvPromise");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    if (lua_pcall(L, 1, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::AddHttpGet(const char* pattern, const char* callback) {
    //this->coord->HttpServer->router->AddGet(pattern, this, (http::RouterMethod)&ScriptComponent::recvHttpRequest, callback);
}

void ScriptComponent::recvGateRequest(gate::GateSession* session, gate::GateRequest* request, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvGateRequest");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    tolua_pushusertype(L, request, "coord::gate::GateRequest");
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvGateNotify(gate::GateSession* session, gate::GateNotify* notify, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvGateNotify");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    tolua_pushusertype(L, notify, "coord::gate::GateRequest");
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

/*void ScriptComponent::recvGateSessionNew(gate::GateSession* session, const char* script) {
    this->coord->CoreLogDebug("[ScriptComponent] recvGateSessionNew");
    lua_State* L = this->GetLuaState(); 
    static thread_local char funcname[128];
    sprintf(funcname, "%s.%s", this->scriptName, script);
    if(this->GetFunction(funcname)) {
        this->coord->CoreLogError("[ScriptComponent] function not found, function=%s.%s", this->scriptName, script);
        lua_pop(L, lua_gettop(L));
        throw ScriptException("script error");
        return;
    }
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvGateSessionClose(gate::GateSession* session, const char* script) {
    this->coord->CoreLogDebug("[ScriptComponent] recvGateSessionClose");
    lua_State* L = this->GetLuaState(); 
    static thread_local char funcname[128];
    sprintf(funcname, "%s.%s", this->scriptName, script);
    if(this->GetFunction(funcname)) {
        this->coord->CoreLogError("[ScriptComponent] function not found, function=%s.%s", this->scriptName, script);
        lua_pop(L, lua_gettop(L));
        throw ScriptException("script error");
        return;
    }
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));    
}

void ScriptComponent::recvGateUserLogin(gate::GateSession* session, const char* script) {
    this->coord->CoreLogDebug("[ScriptComponent] recvGateUserLogin");
    lua_State* L = this->GetLuaState(); 
    static thread_local char funcname[128];
    sprintf(funcname, "%s.%s", this->scriptName, script);
    if(this->GetFunction(funcname)) {
        this->coord->CoreLogError("[ScriptComponent] function not found, function=%s.%s", this->scriptName, script);
        lua_pop(L, lua_gettop(L));
        throw ScriptException("script error");
        return;
    }
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));    
}

void ScriptComponent::recvGateUserLogout(gate::GateSession* session, const char* script) {
    this->coord->CoreLogDebug("[ScriptComponent] recvGateUserLogout");
    lua_State* L = this->GetLuaState(); 
    static thread_local char funcname[128];
    sprintf(funcname, "%s.%s", this->scriptName, script);
    if(this->GetFunction(funcname)) {
        this->coord->CoreLogError("[ScriptComponent] function not found, function=%s.%s", this->scriptName, script);
        lua_pop(L, lua_gettop(L));
        throw ScriptException("script error");
        return;
    }
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));    
}

void ScriptComponent::recvGateUserInstead(gate::GateSession* session, const char* script) {
    this->coord->CoreLogDebug("[ScriptComponent] recvGateUserInstead");
    lua_State* L = this->GetLuaState(); 
    static thread_local char funcname[128];
    sprintf(funcname, "%s.%s", this->scriptName, script);
    if(this->GetFunction(funcname)) {
        this->coord->CoreLogError("[ScriptComponent] function not found, function=%s.%s", this->scriptName, script);
        lua_pop(L, lua_gettop(L));
        throw ScriptException("script error");
        return;
    }
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));    
}*/

void ScriptComponent::recvGateSession(gate::GateSession* session, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvGateSession");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvGatePromise(gate::GateSession* session, BaseRequest* request, const char* script, int ref) {
    this->coord->CoreLogDebug("[ScriptComponent] recvGateSession");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, session, "coord::gate::GateSession");
    if(request) {
        tolua_pushusertype(L, request, request->TypeName());
    } else {
        lua_pushnil(L);
    }
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvClusterRequest(cluster::Request* request, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvClusterRequest");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, request, "coord::cluster::Request");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] recvClusterRequest %s %s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvClusterNotify(cluster::Notify* notify, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvClusterNotify");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, notify, "coord::cluster::Notify");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvClusterResult(cluster::Result* result, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvClusterResult");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, result, "coord::cluster::Result");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvWorkerRequest(worker::Request* request, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvWorkerRequest");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, request, "coord::worker::Request");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] recvWorkerRequest %s %s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvWorkerNotify(worker::Notify* notify, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvWorkerNotify");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, notify, "coord::worker::Notify");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] recvWorkerNotify %s %s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvWorkerResult(worker::Result* result, BaseRequest* request, const char* script, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvWorkerResult");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, result, "coord::worker::Result");
    if (request) {
        tolua_pushusertype(L, request, request->TypeName());
    } else {
        lua_pushnil(L);
    }
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

/*void ScriptComponent::recvWorkerResultRef(worker::Result* result, int ref){
    this->coord->CoreLogDebug("[ScriptComponent] recvWorkerResult");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, result, "coord::worker::Result");
    if (lua_pcall(L, 2, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] %s.%d failed, error=%s", this->scriptName, ref, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}*/

void ScriptComponent::recvRedisReply(redis::AsyncClient* client, redis::Reply& reply, const char* script, int ref) {
    this->coord->CoreLogDebug("[ScriptComponent] recvRedisReply");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, client, "coord::redis::AsyncClient");
    tolua_pushusertype(L, &reply, "coord::redis::Reply");
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] recvRedisReply %s %s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

void ScriptComponent::recvCacheReply(cache::AsyncClient* client, cache::CacheReader& reply, const char* script, int ref) {
    this->coord->CoreLogDebug("[ScriptComponent] recvCacheReply");
    lua_State* L = this->GetLuaState(); 
    lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    tolua_pushusertype(L, this, "coord::ScriptComponent");
    tolua_pushusertype(L, client, "coord::cache::AsyncClient");
    tolua_pushusertype(L, &reply, "coord::cache::CacheReader");
    if (lua_pcall(L, 3, 0, 0) != 0) {
        this->coord->CoreLogError("[ScriptComponent] recvCacheReply %s %s failed, error=%s", this->scriptName, script, lua_tostring(L, -1));
        const char* error = lua_tostring(L, -1); 
        lua_pop(L, lua_gettop(L));
        throw ScriptException(error);
        return;
    }
    lua_pop(L, lua_gettop(L));
}

int ScriptComponent::SetTimeout(lua_State* L) {
    return this->coord->SetTimeout(L);
}

int ScriptComponent::SetInterval(lua_State* L){
    return this->coord->SetInterval(L);
}

void ScriptComponent::ClearInterval(int id){
    return this->coord->ClearInterval(id);
}

} 
