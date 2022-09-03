#include "coord/json/json.h"

namespace coord {
namespace json {

CC_IMPLEMENT(Json, "coord::json::Json")

Json::Json(Coord* coord) {
    this->coord = coord;
}

Json::Json(Coord* coord, const json11::Json& object) : object(object) {
    this->coord = coord;
}

Json::~Json() {
}

int Json::Dump(byte_slice& buffer) {
    std::string result;
    this->object.dump(result);
    coordx::Append(buffer, result.data(), result.length());
    return 0;
}

int Json::Dump(std::string& buffer) {
    this->object.dump(buffer);
    return 0;
}

const char* Json::ToString() {
    static thread_local std::string result;result.clear();
    this->object.dump(result);
    return result.c_str();
}

int Json::Get(lua_State* L) {
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
            Json* ret = new Json(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        } else if (json.is_array()) {
            Json* ret = new Json(this->coord, json);
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
            Json* ret = new Json(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        } else if (json.is_array()) {
            Json* ret = new Json(this->coord, json);
            tolua_pushusertype_and_takeownership(L, ret, this->TypeName());
            return 1;
        }  
    }
    return 0;
}

// key = index
// value = index + 1
int Json::set(lua_State* L, json11::Json& object, int index) {
    tolua_Error tolua_err;
    int valueIndex = (index > 0) ? index + 1 : index - 1;
    if(lua_type(L, index) == LUA_TNUMBER) {
        //如果下标是整数，则要求是数组
        if (!object.is_array()) {
            return -1;
        }
        size_t key = (size_t)lua_tointeger(L, index);
        auto& arr = (json11::Json::array&)object.array_items();
        if (key < 0) {
            return -1;
        }
        if (key >= arr.size()) {
            arr.resize(key + 1);
        }
        if (lua_type(L, valueIndex) == LUA_TNUMBER) {
            arr[key] = json11::Json((double)lua_tonumber(L, valueIndex));
            return 0;
        } else if(lua_type(L, valueIndex) == LUA_TSTRING) {
            arr[key] = json11::Json((const char*)lua_tostring(L, valueIndex));
            return 0;
        } else if(lua_type(L, valueIndex) == LUA_TTABLE) {
            arr[key] = this->lua_toobject(L, valueIndex);
            return 0;
        } else if(tolua_isusertype(L, valueIndex, this->TypeName(), 0, &tolua_err)) {
            Json* jsonPtr = ((Json*)  tolua_tousertype(L, valueIndex, 0));
            arr[key] = jsonPtr->object;
            return 0;
        }
    } else if(lua_type(L, index) == LUA_TSTRING) {
        //如果下标是字符串，则要求是字典
        if (!object.is_object()) {
            return -1;
        }
        const char* key = (const char*)lua_tostring(L, index);
        auto& dict = (json11::Json::object&)object.object_items();
        if (lua_type(L, valueIndex) == LUA_TNUMBER) {
            dict[key] = json11::Json((double)lua_tonumber(L, valueIndex));
            return 0;
        } else if(lua_type(L, valueIndex) == LUA_TSTRING) {
            dict[key] = json11::Json((const char*)lua_tostring(L, valueIndex));
            return 0;
        } else if(lua_type(L, valueIndex) == LUA_TTABLE) {
            dict[key] = this->lua_toobject(L, valueIndex);
            return 0;
        } else if(tolua_isusertype(L, valueIndex, this->TypeName(), 0, &tolua_err)) {
            Json* jsonPtr = ((Json*)  tolua_tousertype(L, valueIndex, 0));
            dict[key] = jsonPtr->object;
            return 0;
        }
    }   
    return -1;
}

json11::Json Json::lua_toobject(lua_State* L, int index) {
    tolua_Error tolua_err;
    size_t objlen = lua_objlen(L, index);
    if (objlen != 0) {
        // 有数组部分就忽略字典部分
        json11::Json object = json11::Json(json11::Json::array());
        auto& arr = (json11::Json::array&)object.array_items();
        for (size_t key = 1; key <= objlen; key++) {
            lua_pushnumber(L, key);
            lua_gettable(L, index > 0 ? index : index - 1);  
            if (lua_type(L, -1) == LUA_TNUMBER) {
                arr.push_back(json11::Json((double)lua_tonumber(L, -1)));
            } else if(lua_type(L, -1) == LUA_TSTRING) {
                arr.push_back(json11::Json((const char*)lua_tostring(L, -1)));
            } else if(lua_type(L, -1) == LUA_TTABLE) {
                arr.push_back(this->lua_toobject(L, -1));
            } else if(tolua_isusertype(L, -1, this->TypeName(), 0, &tolua_err)) {
                Json* jsonPtr = ((Json*)  tolua_tousertype(L, -1, 0));
                arr.push_back(jsonPtr->object);
            }
            lua_pop(L, 1);
        }
        return object;
    } else {
        json11::Json object = json11::Json(json11::Json::object());
        auto& dict = (json11::Json::object&)object.object_items();
        /* table is in the stack at index 't' */
        lua_pushnil(L);  /* first key */
        while (lua_next(L, index > 0 ? index : index - 1) != 0) {
            /* uses 'key' (at index -2) and 'value' (at index -1) */
            if(lua_type(L, -2) == LUA_TSTRING) {    
                const char* key = (const char*)lua_tostring(L, -2);
                if (lua_type(L, -1) == LUA_TNUMBER) {
                    dict[key] = json11::Json((double)lua_tonumber(L, -1));
                } else if(lua_type(L, -1) == LUA_TSTRING) {
                    dict[key] = json11::Json((const char*)lua_tostring(L, -1));
                } else if(lua_type(L, -1) == LUA_TTABLE) {
                    dict[key] = this->lua_toobject(L, -1);
                } else if(tolua_isusertype(L, -1, this->TypeName(), 0, &tolua_err)) {
                    Json* jsonPtr = ((Json*)  tolua_tousertype(L, -1, 0));
                    dict[key] = jsonPtr->object;
                }
            }
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
        return object;
    }
}

int Json::Set(lua_State* L) {
    int err = this->set(L, this->object, 2);
    if (err) {
        return 0;
    } else {
        lua_pushboolean(L, 1);
        return 1;
    }
}


}
}
