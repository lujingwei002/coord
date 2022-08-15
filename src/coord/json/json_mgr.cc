#include "coord/json/json_mgr.h"
#include "coord/json/json.h"
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
        coord::json::Json* self = (coord::json::Json*)  tolua_tousertype(L,1,0);
        return self->Get(L);
    }
    return 0;
}

// 设置字段
static int __newindex(lua_State* L) {
    coord::json::Json* self = (coord::json::Json*)  tolua_tousertype(L,1,0);
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
    luaL_getmetatable (L, Json::_type->name);
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

JsonRef JsonMgr::NewString(const char* data) {
    json11::Json json = json11::Json(data == nullptr ? "" : data);
    return new Json(this->coord, json);
}

JsonRef JsonMgr::NewObject(){
    json11::Json json = json11::Json(json11::Json::object());
    return new Json(this->coord, json);
}

JsonRef JsonMgr::NewArray(){
    json11::Json json = json11::Json(json11::Json::array());
    return new Json(this->coord, json);
}

JsonRef JsonMgr::NewNull(){
    json11::Json json = json11::Json();
    return new Json(this->coord, json);
}

JsonRef JsonMgr::NewBool(bool value){
    json11::Json json = json11::Json(value);
    return new Json(this->coord, json);
}

JsonRef JsonMgr::NewNumber(int value){
    json11::Json json = json11::Json(value);
    return new Json(this->coord, json);
}

JsonRef JsonMgr::NewNumber(double value){
    json11::Json json = json11::Json(value);
    return new Json(this->coord, json);
}

JsonRef JsonMgr::Decode(const char* data){
    std::string err;
    json11::Json json = json11::Json::parse(data, err);
    if (err.length() > 0) {
        this->coord->CoreLogError("[JsonMgr] Decode failed, error=%s", err.c_str());
        return nullptr;
    }
    return new Json(this->coord, json);
}

JsonRef JsonMgr::Decode(std::string& data){
    std::string err;
    json11::Json json = json11::Json::parse(data, err);
    if (err.length() > 0) {
        this->coord->CoreLogError("[JsonMgr] Decode failed, error=%s", err.c_str());
        return nullptr;
    }
    return new Json(this->coord, json);
}

int Encode(JsonRef& json, byte_slice& buffer) {
    return json->Encode(buffer);
}

int Encode(JsonRef& json, std::string& buffer) {
    return json->Encode(buffer);
}

}
}