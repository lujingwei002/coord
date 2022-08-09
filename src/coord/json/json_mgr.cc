#include "coord/json/json_mgr.h"
#include "coord/json/reflect.h"
#include "coord/script/script.h"
#include "coord/coord.h"
#include <json11/json11.hpp>

namespace coord {
namespace json {
CC_IMPLEMENT(JsonMgr, "coord::json::JsonMgr")

// 获取字段
static int __index(lua_State* L) {
    lua_getmetatable(L, 1); //self key mt
    lua_pushvalue(L, 2); //self key mt key
    lua_gettable(L, -2); //self key mt value
    if(lua_iscfunction(L, -1)) {
        lua_remove(L, -2);//self key value
        return 1;
    } else {
        lua_pop(L, 2);//self key        
        coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(L,1,0);
        return self->Get(L);
    }
    return 0;
}

// 设置字段
static int __newindex(lua_State* L) {
    coord::json::Reflect* self = (coord::json::Reflect*)  tolua_tousertype(L,1,0);
    return self->Set(L);
}

JsonMgr::JsonMgr(Coord* coord) {
    this->coord = coord;
  
}

JsonMgr::~JsonMgr() {
}

int JsonMgr::main() {
    return 0;
}

int JsonMgr::registerMetatable() {
    lua_State* L = this->coord->Script->L;
    luaL_getmetatable (L, Reflect::_type->name);
    if(lua_isnil(L, -1)) {
        this->coord->CoreLogError("[coord::JsonMgr] registerMetatable failed, error='metatable not found'");
        return 1;
    }
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, __index);
    lua_settable(L, -3);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, __newindex);
    lua_settable(L, -3);
    return 0;
}

Reflect JsonMgr::NewString(const char* data) {
    json11::Json json = json11::Json(data == nullptr ? "" : data);
    return Reflect(this->coord, json);
}

Reflect JsonMgr::NewObject(){
    json11::Json json = json11::Json(json11::Json::object());
    return Reflect(this->coord, json);
}

Reflect JsonMgr::NewArray(){
    json11::Json json = json11::Json(json11::Json::array());
    return Reflect(this->coord, json);
}

Reflect JsonMgr::NewNull(){
    json11::Json json = json11::Json();
    return Reflect(this->coord, json);
}

Reflect JsonMgr::NewBool(bool value){
    json11::Json json = json11::Json(value);
    return Reflect(this->coord, json);
}

Reflect JsonMgr::NewNumber(int value){
    json11::Json json = json11::Json(value);
    return Reflect(this->coord, json);
}

Reflect JsonMgr::NewNumber(double value){
    json11::Json json = json11::Json(value);
    return Reflect(this->coord, json);
}

Reflect JsonMgr::Decode(const char* data){
    std::string err;
    json11::Json json = json11::Json::parse(data, err);
    if (err.length() > 0) {
        this->coord->CoreLogError("[JsonMgr] Decode failed, error=%s", err.c_str());
        return nullptr;
    }
    return Reflect(this->coord, json);
}

Reflect JsonMgr::Decode(std::string& data){
    std::string err;
    json11::Json json = json11::Json::parse(data, err);
    if (err.length() > 0) {
        this->coord->CoreLogError("[JsonMgr] Decode failed, error=%s", err.c_str());
        return nullptr;
    }
    return Reflect(this->coord, json);
}

int Encode(Reflect& json, byte_slice& buffer) {
    return json.Encode(buffer);
}

int Encode(Reflect& json, std::string& buffer) {
    return json.Encode(buffer);
}

}
}