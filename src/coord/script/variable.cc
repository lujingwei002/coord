#include "coord/script/variable.h"
#include "coord/coordx.h"
#include "coord/coord.h"
#include "coord/script/script.h"
#include <tolua++/tolua++.h>

namespace coord {
namespace script {


Variable::Variable() {
    this->coord = coorda;
    this->ref = LUA_NOREF;
    this->type = LUA_TNIL;
}

Variable::Variable(Coord* coord) {
    this->coord = coord;
    this->ref = LUA_NOREF;
    this->type = LUA_TNIL;
}

Variable::Variable(Coord* coord, int ref, int type) {
    this->coord = coord;
    this->ref = ref;
    this->type = type;    
}

Variable::~Variable() {
    if(this->ref != LUA_NOREF) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
}

Variable::Variable(Variable&& other) {
    this->coord = other.coord;
    this->ref = other.ref;
    this->type = other.type;
    other.ref = LUA_NOREF;
    other.type = LUA_TNIL;
}

Variable::Variable(const Variable& other) {
    this->coord = other.coord;
    this->ref = other.ref;
    this->type = other.type;
    if(this->ref != LUA_NOREF) {
        lua_State* L = this->coord->Script->L;
        lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }
}

Variable& Variable::operator=(const Variable& other) {
    lua_State* L = this->coord->Script->L;
    if(this->ref != LUA_NOREF) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    this->coord = other.coord;
    this->ref = other.ref;
    this->type = other.type;
    if(this->ref != LUA_NOREF) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    return *this;
}

bool Variable::operator== (std::nullptr_t v) const  {
    return this->ref == LUA_NOREF;
}

bool Variable::operator!= (std::nullptr_t v) const  {
    return this->ref != LUA_NOREF;
}

Variable& Variable::operator=(std::nullptr_t) {
    lua_State* L = this->coord->Script->L;
    if (this->ref != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    this->ref = LUA_NOREF;
    this->type = LUA_TNIL;
    return *this;
}

Variable& Variable::operator=(const std::any& value) {
    lua_State* L = this->coord->Script->L;
    if (this->ref != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    lua_pushany(L, value);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TNUMBER;
    return *this;
}

Variable& Variable::operator=(const std::initializer_list<std::tuple<std::any, std::any>>& value) {
    lua_State* L = this->coord->Script->L;
    if (this->ref != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    lua_newtable(L);
    int index = 1;
    for (const auto& v : value) {
        const auto& v1 = std::get<0>(v);
        const auto& v2 = std::get<1>(v);
        lua_pushany(L, v1);
        lua_pushany(L, v2);
        lua_settable(L, -3);
        index++;
    }
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TNUMBER;
    return *this;
    return *this;
}

/*Variable& Variable::operator=(const std::initializer_list<std::any>& value) {
    lua_State* L = this->coord->Script->L;
    if (this->ref != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    lua_newtable(L);
    int index = 1;
    for (const auto& v : value) {
        lua_pushinteger(L, index);
        lua_pushany(L, v);
        lua_settable(L, -3);
        index++;
    }
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TNUMBER;
    return *this;
}*/

int Variable::SetTable() {
    lua_State* L = this->coord->Script->L;
    if (this->ref != LUA_NOREF) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    lua_newtable(L);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TTABLE;
    return 0;
}


const char* Variable::DebugString() {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    const char* buffer = this->coord->Script->DebugString(-1);
    lua_pop(L, 1);
    return buffer;
}

const char* Variable::ShortDebugString() {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    const char* buffer = this->coord->Script->ShortDebugString(-1);
    lua_pop(L, 1);
    return buffer;
}

const char* Variable::GetString() {
    if(this->type != LUA_TSTRING) {
        return nullptr;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    const char* value = lua_tostring(L, -1);
    lua_pop(L, 1);
    return value;
}

lua_Number Variable::GetNumber() {
    if(this->type != LUA_TNUMBER) {
        return 0;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_Number value = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return value;
}

const char* Variable::GetString(const char* key) {
    if(this->type != LUA_TTABLE) {
        return nullptr;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    if (lua_type(L, -1) == LUA_TSTRING) {
        const char* value = lua_tostring(L, -1);
        lua_pop(L, 2);
        return value;
    }
    lua_pop(L, 2);
    return nullptr;
}

Variable Variable::GetTable(const char* key) {
    if(this->type != LUA_TTABLE) {
        return Variable(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    
    if (lua_type(L, -1) == LUA_TTABLE) {
        int ref = luaL_ref(L, LUA_REGISTRYINDEX); 
        if (ref == LUA_NOREF) {
            lua_pop(L, 1);
            return Variable(this->coord);
        } else {
            lua_pop(L, 1);
            return Variable(this->coord, ref, LUA_TTABLE);
        }
    }
    lua_pop(L, 2);
    return Variable(this->coord);
}

bool Variable::GetBool(const char* key) {
    if(this->type != LUA_TTABLE) {
        return false;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    if (lua_type(L, -1) == LUA_TNUMBER) {
        bool value = (bool)lua_toboolean(L, -1);
        lua_pop(L, 2);
        return value;
    }
    lua_pop(L, 2);
    return false;
}

lua_Number Variable::GetNumber(const char* key) {
    if(this->type != LUA_TTABLE) {
        return 0;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    if (lua_type(L, -1) == LUA_TNUMBER) {
        lua_Number value = lua_tonumber(L, -1);
        lua_pop(L, 2);
        return value;
    }
    lua_pop(L, 2);
    return 0;
}

const char* Variable::GetString(int key) {
    if(this->type != LUA_TTABLE) {
        return nullptr;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_gettable(L, -2);
    if (lua_type(L, -1) == LUA_TSTRING) {
        const char* value = lua_tostring(L, -1);
        lua_pop(L, 2);
        return value;
    }
    lua_pop(L, 2);
    return nullptr;
}

Variable Variable::GetTable(int key) {
    if(this->type != LUA_TTABLE) {
        return Variable(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_gettable(L, -2);
    
    if (lua_type(L, -1) == LUA_TTABLE) {
        int ref = luaL_ref(L, LUA_REGISTRYINDEX); 
        if (ref == LUA_NOREF) {
            lua_pop(L, 1);
            return Variable(this->coord);
        } else {
            lua_pop(L, 1);
            return Variable(this->coord, ref, LUA_TTABLE);
        }
    }
    lua_pop(L, 2);
    return Variable(this->coord);
}

bool Variable::GetBool(int key) {
    if(this->type != LUA_TTABLE) {
        return false;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_gettable(L, -2);
    if (lua_type(L, -1) == LUA_TNUMBER) {
        bool value = (bool)lua_toboolean(L, -1);
        lua_pop(L, 2);
        return value;
    }
    lua_pop(L, 2);
    return false;
}

lua_Number Variable::GetNumber(int key) {
    if(this->type != LUA_TTABLE) {
        return 0;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_gettable(L, -2);
    if (lua_type(L, -1) == LUA_TNUMBER) {
        lua_Number value = lua_tonumber(L, -1);
        lua_pop(L, 2);
        return value;
    }
    lua_pop(L, 2);
    return 0;
}

int Variable::SetBool(const char* key, bool value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_pushboolean(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

int Variable::Set(const char* key, const char* value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_pushstring(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

int Variable::SetString(const char* key, const char* value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_pushstring(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}
int Variable::SetNumber(const char* key, lua_Number value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

Variable Variable::SetTable(const char* key) {
    if(this->type != LUA_TTABLE) {
        return Variable(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref); //table
    lua_pushstring(L, key);                       //table key
    lua_newtable(L);                              //table key value
    lua_pushvalue(L, -1);                         //table key value value
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);     //table key value
    lua_settable(L, -3);                          //table
    lua_pop(L, 1);        
    return Variable(this->coord, ref, LUA_TTABLE);                 
}

int Variable::SetTable(const char* key, Variable& table) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref); //table
    lua_pushstring(L, key);                       //table key
    lua_rawgeti(L, LUA_REGISTRYINDEX, table.ref); //table key value
    lua_settable(L, -3);                          //table
    lua_pop(L, 1);        
    return 0;  
}

int Variable::SetBool(int key, bool value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_pushboolean(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

int Variable::Set(int key, const char* value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_pushstring(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

int Variable::SetString(int key, const char* value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_pushstring(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}
int Variable::SetNumber(int key, lua_Number value) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
    lua_pop(L, 1);
    return 0;
}

Variable Variable::SetTable(int key) {
    if(this->type != LUA_TTABLE) {
        return Variable(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref); //table
    lua_pushinteger(L, key);                      //table key
    lua_newtable(L);                              //table key value
    lua_pushvalue(L, -1);                         //table key value value
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);     //table key value
    lua_settable(L, -3);                          //table
    lua_pop(L, 1);        
    return Variable(this->coord, ref, LUA_TTABLE);                 
}

int Variable::SetTable(int key, Variable& table) {
    if(this->type != LUA_TTABLE) {
        return ErrorType;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref); //table
    lua_pushinteger(L, key);                      //table key
    lua_rawgeti(L, LUA_REGISTRYINDEX, table.ref); //table key value
    lua_settable(L, -3);                          //table
    lua_pop(L, 1);        
    return 0;  
}

bool Variable::IsBool() {
    return this->type == LUA_TBOOLEAN;
}

bool Variable::IsString() {
    return this->type == LUA_TSTRING;
}

bool Variable::IsTable() {
    return this->type == LUA_TTABLE;
}

bool Variable::IsNumber() {
    return this->type == LUA_TNUMBER;
}

bool Variable::IsNil() {
    return this->type == LUA_TNIL;
}

int Variable::Decode(byte_slice& buffer){
    return this->Decode(buffer.Data(), buffer.Len()); 
}   

int Variable::Decode(const char* data, size_t len) {
    lua_State* L = this->coord->Script->L;
    if (this->ref != LUA_NOREF) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_NOREF;
        this->type = LUA_TNIL;
    }
    int err = this->coord->Script->Decode(data, len);
    if (err) {
        return err;
    }
    this->type = lua_type(L, -1);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    return 0;   
}

int Variable::Encode(byte_slice& buffer) {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);       // table
    int err = this->coord->Script->Encode(-1, buffer);
    lua_pop(L, 1);
    return err;
}

void Variable::Push() {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    
}

}

}
