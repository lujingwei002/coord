#include "coord/json/reflect.h"

namespace coord {
namespace json {

CC_IMPLEMENT(Reflect, "coord::json::Reflect")


Reflect::Reflect(Coord* coord) {
    this->coord = coord;
}

Reflect::Reflect(Coord* coord, const json11::Json& object) : object(object) {
    this->coord = coord;
}

Reflect::Reflect(const Reflect& other) : object(other.object) {
    this->coord = other.coord;
}

Reflect& Reflect::operator=(const Reflect& other) {
    this->coord = coord;
    this->object = other.object;
    return *this;
}

Reflect::~Reflect() {
}

int Reflect::Encode(byte_slice& buffer) {
    std::string result;
    this->object.dump(result);
    coord::Append(buffer, result.data(), result.length());
    return 0;
}

int Reflect::Encode(std::string& buffer) {
    this->object.dump(buffer);
    return 0;
}

const char* Reflect::ToString() {
    static thread_local std::string result;result.clear();
    this->object.dump(result);
    return result.c_str();
}

int Reflect::Get(lua_State* L) {
    if(lua_type(L, 2) == LUA_TNUMBER) {
        size_t index = (size_t)lua_tointeger(L, 2);
        if (!this->object.is_array()) {
            return 0;
        }
        auto& arr = (json11::Json::array&)this->object.array_items();
        if (index < 0 || index >= arr.size()) {
            return 0;
        }
        auto& json = arr.at(index);
        if (json.is_number()) {
            lua_pushnumber(L, json.number_value());
            return 1;
        } else if (json.is_bool()) {
            lua_pushboolean(L, json.bool_value());
            return 1;
        } else if (json.is_null()) {
            lua_pushnil(L);
            return 1;
        } else if (json.is_string()) {
            lua_pushstring(L, json.string_value().c_str());
            return 1;
        } else if (json.is_object()) {
            Reflect* ret = new Reflect(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        } else if (json.is_array()) {
            Reflect* ret = new Reflect(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        }  
    } else if(lua_type(L, 2) == LUA_TSTRING) {
        const char* key = (const char*)lua_tostring(L, 2);
         if (!this->object.is_object()) {
            return 0;
        }
        auto& object = (json11::Json::object&)this->object.object_items();
        const auto it = object.find(key);
        if (it == object.end()) {
            return 0;
        }
        auto& json = it->second;
        if (json.is_number()) {
            lua_pushnumber(L, json.number_value());
            return 1;
        } else if (json.is_bool()) {
            lua_pushboolean(L, json.bool_value());
            return 1;
        } else if (json.is_null()) {
            lua_pushnil(L);
            return 1;
        } else if (json.is_string()) {
            lua_pushstring(L, json.string_value().c_str());
            return 1;
        } else if (json.is_object()) {
            Reflect* ret = new Reflect(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        } else if (json.is_array()) {
            Reflect* ret = new Reflect(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        }  
    }
    return 0;
}

int Reflect::Set(lua_State* L) {
    if(lua_type(L, 2) == LUA_TNUMBER) {
        size_t index = (size_t)lua_tointeger(L, 2);
        if (!this->object.is_array()) {
            return 0;
        }
        auto& arr = (json11::Json::array&)this->object.array_items();
        if (index < 0 || index >= arr.size()) {
            return 0;
        }
        if (lua_type(L, 3) == LUA_TNUMBER) {
            arr[index] = json11::Json((double)lua_tonumber(L, 3));
            lua_pushboolean(L, true);
            return 1;
        } else if(lua_type(L, 3) == LUA_TSTRING) {
            arr[index] = json11::Json((const char*)lua_tostring(L, 3));
            lua_pushboolean(L, true);
            return 1;
        }
    } else if(lua_type(L, 2) == LUA_TSTRING) {
        const char* key = (const char*)lua_tostring(L, 2);
         if (!this->object.is_object()) {
            return 0;
        }
        auto& object = (json11::Json::object&)this->object.object_items();
        if (lua_type(L, 3) == LUA_TNUMBER) {
            object[key] = json11::Json((double)lua_tonumber(L, 3));
            lua_pushboolean(L, true);
            return 1;
        } else if(lua_type(L, 3) == LUA_TSTRING) {
            object[key] = json11::Json((const char*)lua_tostring(L, 3));
            lua_pushboolean(L, true);
            return 1;
        }
    }
    return 0;
}
}
}