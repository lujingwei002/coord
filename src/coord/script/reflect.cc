#include "coord/script/reflect.h"
#include "coord/builtin/error.h"
#include "coord/coord.h"
#include <tolua++/tolua++.h>

namespace coord {
namespace script {


Reflect newReflect(Coord* coord, int ref, int type) {
    return Reflect(coord, ref, type);
}

Reflect::Reflect(Coord* coord) {
    this->coord = coord;
    this->ref = LUA_REFNIL;
    this->type = LUA_TNIL;
}

Reflect::Reflect(Coord* coord, int ref, int type) {
    this->coord = coord;
    this->ref = ref;
    this->type = type;    
}

Reflect::~Reflect() {
    if(this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
}

Reflect::Reflect(const Reflect& other) {
    this->coord = other.coord;
    this->ref = other.ref;
    this->type = other.type;
    if (this->ref >= 0) {
        lua_State* L = this->coord->Script->L;
        lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }
}

Reflect& Reflect::operator=(const Reflect& other) {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
    this->coord = other.coord;
    this->ref = other.ref;
    this->type = other.type;
    if (this->ref >= 0) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    return *this;
}

bool Reflect::operator== (std::nullptr_t v) const  {
    return this->ref == LUA_REFNIL;
}

bool Reflect::operator!= (std::nullptr_t v) const  {
    return this->ref != LUA_REFNIL;
}

int Reflect::SetTable() {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
    lua_newtable(L);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TTABLE;
    return 0;
}

int Reflect::SetString(const char* value) {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
    lua_pushstring(L, value);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TSTRING;
    return 0;
}

int Reflect::SetNumber(lua_Number value) {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
    lua_pushnumber(L, value);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TNUMBER;
    return 0;
}

int Reflect::SetBool(bool value) {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
    lua_pushboolean(L, value);
    this->ref = luaL_ref(L, LUA_REGISTRYINDEX);
    this->type = LUA_TNUMBER;
    return 0;
}

int Reflect::SetNil() {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
        this->type = LUA_TNIL;
    }
    this->ref = LUA_REFNIL;
    this->type = LUA_TNIL;
    return 0;
}

const char* Reflect::ToString() {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    const char* buffer = this->coord->Script->ToString(-1);
    lua_pop(L, 1);
    return buffer;
}

const char* Reflect::ToShortString() {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    const char* buffer = this->coord->Script->ToShortString(-1);
    lua_pop(L, 1);
    return buffer;
}

const char* Reflect::GetString() {
    if(this->type != LUA_TSTRING) {
        return nullptr;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    const char* value = lua_tostring(L, -1);
    lua_pop(L, 1);
    return value;
}

lua_Number Reflect::GetNumber() {
    if(this->type != LUA_TNUMBER) {
        return 0;
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_Number value = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return value;
}

const char* Reflect::GetString(const char* key) {
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

Reflect Reflect::GetTable(const char* key) {
    if(this->type != LUA_TTABLE) {
        return Reflect(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    
    if (lua_type(L, -1) == LUA_TTABLE) {
        int ref = luaL_ref(L, LUA_REGISTRYINDEX); 
        if (ref == LUA_NOREF) {
            lua_pop(L, 1);
            return Reflect(this->coord);
        } else {
            lua_pop(L, 1);
            return Reflect(this->coord, ref, LUA_TTABLE);
        }
    }
    lua_pop(L, 2);
    return Reflect(this->coord);
}

bool Reflect::GetBool(const char* key) {
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

lua_Number Reflect::GetNumber(const char* key) {
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

const char* Reflect::GetString(int key) {
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

Reflect Reflect::GetTable(int key) {
    if(this->type != LUA_TTABLE) {
        return Reflect(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    lua_pushinteger(L, key);
    lua_gettable(L, -2);
    
    if (lua_type(L, -1) == LUA_TTABLE) {
        int ref = luaL_ref(L, LUA_REGISTRYINDEX); 
        if (ref == LUA_NOREF) {
            lua_pop(L, 1);
            return Reflect(this->coord);
        } else {
            lua_pop(L, 1);
            return Reflect(this->coord, ref, LUA_TTABLE);
        }
    }
    lua_pop(L, 2);
    return Reflect(this->coord);
}

bool Reflect::GetBool(int key) {
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

lua_Number Reflect::GetNumber(int key) {
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

int Reflect::SetBool(const char* key, bool value) {
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

int Reflect::SetString(const char* key, const char* value) {
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

int Reflect::SetNumber(const char* key, lua_Number value) {
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

Reflect Reflect::SetTable(const char* key) {
    if(this->type != LUA_TTABLE) {
        return Reflect(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref); //table
    lua_pushstring(L, key);                       //table key
    lua_newtable(L);                              //table key value
    lua_pushvalue(L, -1);                         //table key value value
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);     //table key value
    lua_settable(L, -3);                          //table
    lua_pop(L, 1);        
    return Reflect(this->coord, ref, LUA_TTABLE);                 
}

int Reflect::SetTable(const char* key, Reflect& table) {
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

int Reflect::SetBool(int key, bool value) {
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

int Reflect::SetString(int key, const char* value) {
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

int Reflect::SetNumber(int key, lua_Number value) {
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

Reflect Reflect::SetTable(int key) {
    if(this->type != LUA_TTABLE) {
        return Reflect(this->coord);
    }
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref); //table
    lua_pushinteger(L, key);                      //table key
    lua_newtable(L);                              //table key value
    lua_pushvalue(L, -1);                         //table key value value
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);     //table key value
    lua_settable(L, -3);                          //table
    lua_pop(L, 1);        
    return Reflect(this->coord, ref, LUA_TTABLE);                 
}

int Reflect::SetTable(int key, Reflect& table) {
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

bool Reflect::IsBool() {
    return this->type == LUA_TBOOLEAN;
}

bool Reflect::IsString() {
    return this->type == LUA_TSTRING;
}

bool Reflect::IsTable() {
    return this->type == LUA_TTABLE;
}

bool Reflect::IsNumber() {
    return this->type == LUA_TNUMBER;
}

bool Reflect::IsNil() {
    return this->type == LUA_TNIL;
}

int Reflect::Decode(byte_slice& buffer){
    return this->Decode(buffer.Data(), buffer.Len()); 
}   

int Reflect::Decode(const char* data, size_t len) {
    lua_State* L = this->coord->Script->L;
    if (this->ref >= 0) {
        luaL_unref(this->coord->Script->L, LUA_REGISTRYINDEX, this->ref);
        this->ref = LUA_REFNIL;
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

int Reflect::Encode(byte_slice& buffer) {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);       // table
    int err = this->coord->Script->Encode(-1, buffer);
    lua_pop(L, 1);
    return err;
}

void Reflect::Push() {
    lua_State* L = this->coord->Script->L;
    lua_rawgeti(L, LUA_REGISTRYINDEX, this->ref);
    
}

}

}