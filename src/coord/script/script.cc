#include "coord/script/script.h"
#include "coord/script/reflect.h"
#include "coord/coord.h"
#include "coord/config/config.h"
#include "coord/protobuf/init.h"
#include "coord/json/json_mgr.h"
#include "coord/coordx.h"
#include "coord/environment/environment.h"

#include "lua-cjson/lua_cjson.h"

#include <iostream>

extern "C"
{
    int luaopen_coord(lua_State* tolua_S);
}

const char* TAG = "Script";

namespace coord {
namespace script {

Script* newScript(Coord *coord){
    Script* script = new Script(coord);
    return script;
}

Script::Script(Coord *coord) {
    this->coord = coord;
    lua_State* L = lua_open();
    this->L = L;
    luaL_openlibs(L);
    this->jsonParser = cjson_new(L);
}

Script::~Script() {
    if (this->jsonParser) {
        cjson_destroy(this->jsonParser);
        this->jsonParser = nullptr;
    }
}

int Script::DoFile(const char* filePath) {
    lua_State* L = this->L;
    if(luaL_dofile(L, filePath)) {
        if (lua_isstring(L, -1)) {
            this->coord->CoreLogError("[Script] DoFile failed, error='%s'", lua_tostring(L, -1));
            this->lastError = lua_tostring(L, -1);
            lua_pop(L, 1);
            return -1;
        }
    }
    return 0;
}

int Script::DoString(const char* filePath) {
    lua_State* L = this->L;
    if(luaL_dostring(L, filePath)) {
        if (lua_isstring(L, -1)) {
            this->coord->CoreLogError("[Script] DoString failed, error='%s'", lua_tostring(L, -1));
            this->lastError = lua_tostring(L, -1);
            lua_pop(L, 1);
            return -1;
        }
    }
    return 0;
}

int Script::SetNumber(const char* path, lua_Number value) {
    const char* key = this->getTableAndKey(path);
    if (key == nullptr) {
        return -1;
    }
    lua_State* L = this->L;
    if (key == path) {
        lua_pushnumber(L, value);
        lua_setglobal(L, key);
    } else {
        lua_pushstring(L, key);
        lua_pushnumber(L, value);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return 0;
}

int Script::SetString(const char* path, const char* value) {
    const char* key = this->getTableAndKey(path);
    if (key == nullptr) {
        return -1;
    }
    lua_State* L = this->L;
    if (key == path) {
        lua_pushstring(L, value);
        lua_setglobal(L, key);
    } else {
        lua_pushstring(L, key);
        lua_pushstring(L, value);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return 0;
}

int Script::SetBool(const char* path, bool value) {
    const char* key = this->getTableAndKey(path);
    if (key == nullptr) {
        return -1;
    }
    lua_State* L = this->L;
    if (key == path) {
        lua_pushboolean(L, value);
        lua_setglobal(L, key);
    } else {
        lua_pushstring(L, key);
        lua_pushboolean(L, value);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return 0;
}

int Script::SetNil(const char* path) {
    const char* key = this->getTableAndKey(path);
    if (key == nullptr) {
        return -1;
    }
    lua_State* L = this->L;
    if (key == path) {
        lua_pushnil(L);
        lua_setglobal(L, key);
    } else {
        lua_pushstring(L, key);
        lua_pushnil(L);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return 0;
}

int Script::SetTable(const char* path) {
    const char* key = this->getTableAndKey(path);
    if (key == nullptr) {
        return -1;
    }
    lua_State* L = this->L;
    if (key == path) {
        lua_newtable(L);
        lua_setglobal(L, key);
    } else {
        lua_pushstring(L, key);
        lua_newtable(L);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return 0;
}

int Script::Set(const char* path, int index) {
    const char* key = this->getTableAndKey(path);
    if (key == nullptr) {
        return -1;
    }
    lua_State* L = this->L;
    if (key == path) {
        lua_pushvalue(L, index);
        lua_setglobal(L, key);
    } else {
        lua_pushstring(L, key);
        lua_pushvalue(L, index);
        lua_settable(L, -3);
        lua_pop(L, 1);
    }
    return 0;
}

lua_Number Script::GetNumber(const char *name) {
    lua_State* L = this->L;
    if(this->getValue(L, name)) {
        return 0;
    }
    if(lua_type(L, -1) != LUA_TNUMBER) {
        lua_pop(L, 1);
        return 0;
    }
    lua_Number result = (lua_Number)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return result;
}

void Script::regLib(int (*p)(lua_State* L)) {
    lua_State* L = this->L;
    p(L);
}

const char* Script::GetString(const char *name) {
    lua_State* L = this->L;
    if(this->getValue(L, name)) {
        return nullptr;
    }
    if(lua_type(L, -1) != LUA_TSTRING) {
        lua_pop(L, 1);
        return nullptr;
    }
    const char* result = (const char*)lua_tostring(L, -1);
    lua_pop(L, 1);
    return result;
}

bool Script::GetBool(const char *name) {
    lua_State* L = this->L;
    if(this->getValue(L, name)) {
        return false;
    }
    if(lua_type(L, -1) != LUA_TBOOLEAN) {
        lua_pop(L, 1);
        return false;
    }
    bool result = (bool)lua_toboolean(L, -1);
    lua_pop(L, 1);
    return result;
}

bool Script::IsBool(const char* path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return false;
    }
    bool result = lua_type(L, -1) == LUA_TBOOLEAN;
    lua_pop(L, 1);
    return result;
}

bool Script::IsString(const char* path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return false;
    }
    bool result = lua_type(L, -1) == LUA_TSTRING;
    lua_pop(L, 1);
    return result;
}

bool Script::IsNumber(const char* path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return false;
    }
    bool result = lua_type(L, -1) == LUA_TNUMBER;
    lua_pop(L, 1);
    return result;
}

bool Script::IsTable(const char* path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return false;
    }
    bool result = lua_type(L, -1) == LUA_TTABLE;
    lua_pop(L, 1);
    return result;
}

bool Script::IsFunction(const char* path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return false;
    }
    bool result = lua_type(L, -1) == LUA_TFUNCTION;
    lua_pop(L, 1);
    return result;
}

bool Script::IsNil(const char* path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return true;
    }
    bool result = lua_type(L, -1) == LUA_TNIL;
    lua_pop(L, 1);
    return result;
}

Reflect Script::Get(const char *fieldName) {
    lua_State* L = this->L;
    if(this->getValue(L, fieldName)) {
        return Reflect(this->coord);
    }
    int type = lua_type(L, -1);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    return Reflect(this->coord, ref, type);
}

const char* Script::getTableAndKey(const char *path) {
    lua_State* L = this->L;
    char *begin = (char *)path;
    char *varBegin = begin;
    char *it = begin;
    while(*it != 0) {
        if(*it == '.' && varBegin == begin) {
            std::string var(varBegin, it - varBegin);
            lua_getglobal(L, var.c_str());   // value
            if(lua_isnil(L, -1)){               // nil
                lua_pop(L, 1);                  //
                lua_newtable(L);                // table
                lua_pushvalue(L, -1);           // table table
                lua_setglobal(L, var.c_str());     // table
            } else if(!lua_istable(L, -1)) {
                lua_pop(L, 1);                  // 
                return nullptr;
            }
            varBegin = it + 1;
        } else if(*it == '.') {
            lua_pushlstring(L, varBegin, it - varBegin);        // table key
            lua_gettable(L, -2);                                // table value
            if(lua_isnil(L, -1)) {
                lua_pop(L, 1);                  // table
                lua_newtable(L);                // table value
                lua_pushlstring(L, varBegin, it - varBegin);  // table value key
                lua_pushvalue(L, -2);           // table value key value
                lua_settable(L, -4);            // table value
            } else if(!lua_istable(L, -1)) {
                lua_pop(L, 2);                  //
                return nullptr;
            }
            lua_remove(L, -2);//弹出table       // value
            varBegin = it + 1;
        }
        it++;
    }
    return varBegin;
}

int Script::getValue(lua_State* L, const char *fieldName) {;
    char *begin = (char *)fieldName;
    char *varBegin = begin;
    char *it = begin;
    while(*it != 0) {
        if(*it == '.' && varBegin == begin) {
            lua_getglobal(L, std::string(varBegin, it - varBegin).c_str());   // value
            if(lua_isnil(L, -1)){
                lua_pop(L, 1);              //
                return -1;
            }
            varBegin = it + 1;
        } else if(*it == '.') {
            if (!lua_istable(L, -1)) {
                lua_pop(L, 1);
                return -1;
            }
            lua_pushlstring(L, varBegin, it - varBegin);  // table key
            lua_gettable(L, -2);                          // table value
            if(lua_isnil(L, -1)) {
                lua_pop(L, 2);                            //
                return -1;
            }
            lua_remove(L, -2);//弹出table                 // value
            varBegin = it + 1;
        }
        it++;
    }
    if(varBegin == begin) {
        lua_getglobal(L, varBegin);             // value
        // if(lua_isnil(L, -1)) {
        //     lua_pop(L, 1);                      //
        //     return false;
        // }
        return 0;
    }else {
        if (!lua_istable(L, -1)) {
            lua_pop(L, 1);
            return -1;
        }
        lua_pushlstring(L, varBegin, it - varBegin);      // table key
        lua_gettable(L, -2);                              // table value
        // if(lua_isnil(L, -1)) {              
        //     lua_pop(L, 2);                                //
        //     return false;
        // }
        lua_remove(L, -2);//弹出table                     // value
    }
    return 0;
}

int Script::GetFunction(const char *path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return -1;
    }
    if(lua_type(L, -1) != LUA_TFUNCTION) {
        lua_pop(L, 1);
        return -1;
    }
    return 0;
}

int Script::GetValue(const char *path) {
    lua_State* L = this->L;
    return this->getValue(L, path);
}

int Script::GetFunction(lua_State* L, const char *path) {
    if(this->getValue(L, path)) {
        return -1;
    }
    if(lua_type(L, -1) != LUA_TFUNCTION) {
        lua_pop(L, 1);
        return -1;
    }
    return 0;
}

int Script::GetTable(const char *path) {
    lua_State* L = this->L;
    if(this->getValue(L, path)) {
        return -1;
    }
    if(lua_type(L, -1) != LUA_TTABLE) {
        lua_pop(L, 1);
        return -1;
    }
    return 0;
}

int Script::TraceStack()  {
    lua_State* L = this->L;
    lua_getglobal(L, "debug");  
    lua_getfield(L, -1, "traceback");  
    lua_pcall(L, 0, 1, 0);   
    const char* sz = lua_tostring(L, -1);  
    this->coord->CoreLogError("%s", sz);
    return 0;
}

int Script::onAwake() {
    printf("aaaaaaaaa1\n");
    lua_State* L = this->getThread();
    if (nullptr == L) {
        return ErrorOutOfMemory;
    }
    printf("aaaaaaaaa2\n");
    int err = this->GetFunction(L, "_onAwake_");
    if(err){
        this->coord->CoreLogError("[script] onAwake not found");
        lua_pop(L, lua_gettop(L));
        return ErrorScript;
    }
    printf("aaaaaaaaa2\n");
    err = lua_resume(L, 0);
    if (err == LUA_YIELD) {
        printf("yield %d\n", lua_gettop(L));
        lua_pop(L, lua_gettop(L));
        return 0;
    } else if (err) {
        this->coord->CoreLogError("[script] onAwake fail, error='%s'", lua_tostring(L, -1));
        this->TraceStack();
        lua_pop(L, lua_gettop(L));
        return ErrorScript;
    } else {
        printf("finished %d\n", lua_gettop(L));
        lua_pop(L, lua_gettop(L));
        this->freeThread(L);
        return 0;
    }
    return 0;
}

int Script::main()  {
    std::string package;
    if (this->coord->Environment->Package.length() > 0) {
        package = this->coord->Environment->Package;
    }
    if (this->coord->Config->Basic.Package.length() > 0) {
        package = this->coord->Config->Basic.Package + ";" + package;
    }
    const char* mainPackage = this->coord->Config->Basic.Main.c_str();
    lua_State* L = this->L;
    this->registerLibs();
    if(this->coord->Proto) {
        this->coord->Proto->registerMetatable();
    }
    if(this->coord->Json) {
        this->coord->Json->registerMetatable();
    }
    this->coord->CoreLogInfo("[%s] Package: %s", TAG, package.c_str());
    this->coord->CoreLogInfo("[%s] Main: %s", TAG, mainPackage);

    strncpy(this->Path, package.c_str(), PACKAGE_MAX);
    strncpy(this->Main, mainPackage, PACKAGE_MAX);
    tolua_pushusertype(L, (void*)this->coord, "coord::Coord");
    lua_setglobal(L, "coorda");
    if(this->GetFunction("_main_")){
        this->coord->CoreLogError("[script] _main_ not found");
        lua_pop(L, lua_gettop(L));
        return 1;
    }
    if (lua_pcall(L, 0, 0, 0) != 0){
        this->coord->LogError("[script] _main_ failed, error='%s'", lua_tostring(L, -1));
        this->TraceStack();
        return 1;
    }
    lua_pop(L, lua_gettop(L));
    return 0;
}

int Script::Import(ScriptOpenFunc func) {
    int err = func(this->L);
    if (err != 1) {
        this->coord->CoreLogError("[Script] Import failed, error=%d\n", err);
        return -1;
    }
    return 0;
}

void Script::onDestory()  {
    lua_State* L = this->L;
    if(this->GetFunction("_onDestory_")){
        this->coord->CoreLogError("[script] onDestory not found");
        lua_pop(L, lua_gettop(L));
        return;
    }
    if (lua_pcall(L, 0, 0, 0) != 0){
        this->coord->CoreLogError("[script] onDestory failed, error='%s'", lua_tostring(L, -1));
        this->TraceStack();
        return;
    }
    lua_pop(L, lua_gettop(L));
    return;
}

void Script::gc() {
    //class_gc_event(this->L);
}

int Script::onReload() {
    if(this->GetFunction("_onReload_")){
        this->coord->CoreLogError("[script] onReload not found");
        lua_pop(L, lua_gettop(L));
        return 1;
    }
    if (lua_pcall(L, 0, 0, 0) != 0){
        this->coord->CoreLogError("[script] onReload failed, error='%s'", lua_tostring(L, -1));
        this->TraceStack();
        return 1;
    }
    lua_pop(L, lua_gettop(L));
    return 0;
}

int Script::registerLibs() {
    lua_State* L = this->L;
    luaopen_coord(L);
    return 0;
}

const char* Script::ToString(const char* path) {
    if (this->getValue(L, path)) {
        return nullptr;
    }
    const char* result = this->ToString(-1);
    lua_pop(this->L, 1);
    return result;
}

const char* Script::ToString(int index, const char* path) {
    if (this->getValue(L, path)) {
        return nullptr;
    }
    const char* result = this->ToString(index);
    lua_pop(this->L, 1);
    return result;
}

int Script::ToString(lua_State* L) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    int err = this->ToString(2, buffer);
    if (err) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlstring(L, buffer.Data(), buffer.Len());
    return 1;
}

const char* Script::ToString(int index) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    int err = this->ToString(index, buffer);
    if (err) {
        return NULL;
    }
    coordx::Append(buffer, 0);
    return buffer.Data();
}

int Script::ToString(int index, byte_slice& buffer) {
    static thread_local byte_slice field;field.Resize(0);
    static thread_local byte_slice space;space.Resize(0);
    std::map<const void*, std::string> recordDict;
    coordx::Appendf(field, "#");
    int err = this->tostring(buffer, this->L, index, recordDict, space, field, false);
    return err;
}

const char* Script::ToShortString(const char* path) {
    if (this->getValue(L, path)) {
        return nullptr;
    }
    const char* result = this->ToShortString(-1);
    lua_pop(this->L, 1);
    return result;
}

const char* Script::ToShortString(int index, const char* path) {
    if (this->getValue(L, path)) {
        return nullptr;
    }
    const char* result = this->ToShortString(index);
    lua_pop(this->L, 1);
    return result;
}

int Script::ToShortString(lua_State* L) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    int err = this->ToShortString(2, buffer);
    if (err) {
        lua_pushnil(L);
        return 1;
    }
    lua_pushlstring(L, buffer.Data(), buffer.Len());
    return 1;
}

const char* Script::ToShortString(int index) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    int err = this->ToShortString(index, buffer);
    if (err) {
        return NULL;
    }
    coordx::Append(buffer, 0);
    return buffer.Data();
}

int Script::ToShortString(int index, byte_slice& buffer) {
    static thread_local byte_slice field;field.Resize(0);
    static thread_local byte_slice space;space.Resize(0);
    std::map<const void*, std::string> recordDict;
    coordx::Appendf(field, "#");
    int err = this->tostring(buffer, this->L, index, recordDict, space, field, true);
    return err;
}

int Script::tostring(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& space, byte_slice& field, bool isShort) {
    tolua_Error tolua_err;
    if (lua_isstring(L, index) && lua_type(L, index) == LUA_TSTRING) {
        const char* value = (const char*)lua_tostring(L, index);
        coordx::Appendf(buffer, "\'%s\'", value);
    } else if (lua_isnil(L, index)) {
        coordx::Appendf(buffer, "nil");
    } else if (lua_istable(L, index)) {
        auto it = recordDict.find(lua_topointer(L, index));
        if (it != recordDict.end()) {
            coordx::Appendf(buffer, "%s", it->second.c_str());
        } else {
            recordDict[lua_topointer(L, index)] = std::string(field.Data(), field.Len());
            if(isShort)coordx::Appendf(buffer, "{"); else coordx::Appendf(buffer, "{\n");
            lua_pushnil(L); 
            while (lua_next(L, index >= 0 ? index : index - 1) != 0) {
                byte_slice field2 = field.Slice(0, field.Len());
                if(!isShort)coordx::Append(buffer, space.Data(), space.Len());
                if (lua_type(L, -2) == LUA_TNUMBER) {
                    coordx::Appendf(buffer, "[%d]=", lua_tointeger(L, -2));
                    coordx::Appendf(field2, ".[%d]", lua_tointeger(L, -2));
                } else {
                    coordx::Appendf(buffer, "\'%s\'=", lua_tostring(L, -2));
                    coordx::Appendf(field2, ".%s", lua_tostring(L, -2));
                }
                int err = 0;
                if(isShort){
                    /* uses 'key' (at index -2) and 'value' (at index -1) */
                    err = this->tostring(buffer, L, -1, recordDict, space, field2, isShort);
                } else {
                    byte_slice space2 = space.Slice(0, space.Len());
                    coordx::Appendf(space2, "\t");
                    /* uses 'key' (at index -2) and 'value' (at index -1) */
                    err = this->tostring(buffer, L, -1, recordDict, space2, field2, isShort);
                }
                if (err) {
                    if(!isShort)if(space.Len()>0)coordx::Append(buffer, space.Data(), space.Len()-1);
                    coordx::Appendf(buffer, "}");
                    lua_pop(L, 2);
                    break;
                }
                if(isShort) coordx::Appendf(buffer, ","); else coordx::Appendf(buffer, ",\n");
                /* removes 'value'; keeps 'key' for next iteration */
                lua_pop(L, 1);
            }
            if(!isShort)if(space.Len()>0)coordx::Append(buffer, space.Data(), space.Len()-1);
            coordx::Appendf(buffer, "}");
        }
    } else if(tolua_isusertype(L, index, protobuf::Message::_TypeName, 0, &tolua_err)) {
        protobuf::Message* message = ((protobuf::Message*) tolua_tousertype(L, index, 0));
        if (message == nullptr) {
            coordx::Appendf(buffer, "(null)");
        } else {
            coordx::Appendf(buffer, "\'%s\'", message->ShortDebugString());
        }
    } else if (lua_isboolean(L, index)) {
        bool value = (bool)lua_toboolean(L, index);
        if (value) {
            coordx::Appendf(buffer, "true");
        } else {
            coordx::Appendf(buffer, "false");
        }
    } else if (lua_isnumber(L, index)) {
        double value = (double)lua_tonumber(L, index);
        coordx::Appendf(buffer, "%f", value);
    } else if (lua_isuserdata(L, index)) {
        coordx::Appendf(buffer, "userdata: %p", lua_topointer(L, index));
    } else if (lua_isfunction(L, index)) {
        coordx::Appendf(buffer, "function: %p", lua_topointer(L, index));
    } else {
        coordx::Appendf(buffer, "type: %d", lua_type(L, index));
    }
    return 0;
}

int Script::Encode(const char* path, byte_slice& buffer) {
    if (this->getValue(L, path)) {
        return -1;
    }
    int err = this->Encode(-1, buffer);
    lua_pop(this->L, 1);
    return err;
}

int Script::Encode(int index, byte_slice& buffer) {
    static thread_local byte_slice field;
    buffer.Resize(0);
    field.Resize(0);
    std::map<const void*, std::string> recordDict;
    coordx::Appendf(field, "#");
    int err = this->encode(buffer, this->L, index, recordDict, field);
    return err;
}

int Script::Encode(lua_State* L) {
    static thread_local byte_slice buffer;
    static thread_local byte_slice field;
    buffer.Resize(0);
    field.Resize(0);
    std::map<const void*, std::string> recordDict;
    coordx::Appendf(field, "#");
    int err = this->encode(buffer, L, 2, recordDict, field);
    if (err) {
        lua_pushlstring(L, buffer.Data(), buffer.Len());
        return 1;
    }
    lua_pushlstring(L, buffer.Data(), buffer.Len());
    return 1;
} 

int Script::encode(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& field) {
    tolua_Error tolua_err;
    if (lua_isstring(L, index) && lua_type(L, index) == LUA_TSTRING) {
        uint8_t type = lua_type(L, index);
        coordx::Append(buffer, type);
        size_t len = 0;
        const char* value = (const char*)lua_tolstring(L, index, &len);
        coordx::Append(buffer, (char*)(&len), sizeof(len));
        coordx::Append(buffer, value, len);
    } else if (lua_isnil(L, index) && lua_type(L, index) == LUA_TNIL) {
        uint8_t type = lua_type(L, index);
        coordx::Append(buffer, type);
    } else if (lua_istable(L, index)) {
        auto it = recordDict.find(lua_topointer(L, index));
        if (it != recordDict.end()) {
            uint8_t type = LUA_TREFERENCE;
            coordx::Append(buffer, type);
            uint16_t len = it->second.size();
            const char* value = it->second.c_str();
            coordx::Append(buffer, (char*)(&len), sizeof(len));
            coordx::Append(buffer, value, len);
        } else {
            recordDict[lua_topointer(L, index)] = std::string(field.Data(), field.Len());
            uint8_t type = lua_type(L, index);
            coordx::Append(buffer, type);
            lua_pushnil(L); 
            while (lua_next(L, index >= 0 ? index : index - 1) != 0) {
                byte_slice field2 = field.Slice(0, field.Len());
                if (lua_type(L, -2) == LUA_TNUMBER) {
                    type = LUA_TNUMBER;
                    coordx::Append(buffer, type);
                    lua_Integer value = lua_tointeger(L, -2);
                    coordx::Append(buffer, (char*)(&value), sizeof(value));
                    coordx::Appendf(field2, ".[%d]", lua_tointeger(L, -2));
                } else {
                    type = LUA_TSTRING;
                    coordx::Append(buffer, type);
                    size_t len = 0;
                    const char* key = (const char*)lua_tolstring(L, -2, &len);                    
                    coordx::Append(buffer, (char*)(&len), sizeof(len));
                    coordx::Append(buffer, key, len);
                    coordx::Appendf(field2, ".%s", lua_tostring(L, -2));
                }
                /* uses 'key' (at index -2) and 'value' (at index -1) */
                int err = this->encode(buffer, L, -1, recordDict, field2);
                if (err) {
                    lua_pop(L, 2);
                    break;
                }
                /* removes 'value'; keeps 'key' for next iteration */
                lua_pop(L, 1);
            }
            type = 0;//结束table
            coordx::Append(buffer, type);
        }
    } else if(tolua_isusertype(L, index, protobuf::Message::_TypeName, 0, &tolua_err)) {
        uint8_t type = LUA_TPROTO;
        coordx::Append(buffer, type);
        protobuf::Message* proto = ((protobuf::Message*) tolua_tousertype(L, index, 0));
        google::protobuf::Message* message = proto->GetMessage();
        if (message == nullptr) {
            size_t totalLen = 0;
            coordx::Append(buffer, (char*)(&totalLen), sizeof(totalLen));
        } else {
            const char* name = message->GetTypeName().data();
            uint16_t nameLen = (uint16_t)(strlen(name));
            size_t msgLen = message->ByteSizeLong();
            size_t totalLen = sizeof(uint16_t) + nameLen + msgLen;
            coordx::Append(buffer, (char*)(&totalLen), sizeof(totalLen));
            //消息名字
            coordx::Append(buffer, (char*)(&nameLen), sizeof(nameLen));
            coordx::Append(buffer, name, nameLen);
            //消息内容
            buffer.Reserve(buffer.Len() + msgLen);
            if(buffer.Capacity() < msgLen){
                this->coord->CoreLogError("[Proto] Encode failed, capacity=%ld, msgLen=%ld, error='buffer reserve err'", buffer.Capacity(), msgLen);
                return -1;
            } 
            char* end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)(buffer.Data() + buffer.Len()));
            buffer.Resize(end - buffer.Data());
        }
    } else if (lua_isboolean(L, index)) {
        uint8_t type = lua_type(L, index);
        coordx::Append(buffer, type);
        uint8_t value = (bool)lua_toboolean(L, index) ? 1 : 0;
        coordx::Append(buffer, (char*)(&value), sizeof(value));
    } else if (lua_isnumber(L, index)) {
        uint8_t type = lua_type(L, index);
        coordx::Append(buffer, type);
        lua_Number value = (double)lua_tonumber(L, index);
        coordx::Append(buffer, (char*)(&value), sizeof(value));
    } 
    return 0;
}

int Script::Decode(const char* data, size_t len) {
    int byteRead = this->decode(this->L, data, len);
    if (byteRead <= 0) {
        return -1;
    }
    return 0;
}

int Script::Decode(const char* path, const char* data, size_t len) {
    int err = this->Decode(data, len);
    if (err) {
        return err;
    }
    err = this->Set(path, -1);
    lua_pop(L, 1);
    return err;
}

int Script::Decode(const char* path, byte_slice& buffer) {
    int err = this->Decode(buffer);
    if (err) {
        return err;
    }
    err = this->Set(path, -1);
    lua_pop(L, 1);
    return err;
}

int Script::Decode(byte_slice& buffer) {
    int byteRead = this->decode(this->L, buffer.Data(), buffer.Len());
    if (byteRead < 0) {
        return -1;
    }
    return 0;
}

int Script::Decode(lua_State* L) {
    size_t len = 0;
    const char* data = lua_tolstring(L, -1, &len);
    int byteRead = this->decode(L, data, len);
    if (byteRead < 0) {
        return -1;
    }
    return 0;
}

int Script::decode(lua_State* L, const char* data, size_t len) {
    char* offset = (char*)data;
    char* end = (char*)data + len;
    if (offset + sizeof(uint8_t) > end) {
        return -1;
    }
    uint8_t type = *((uint8_t*)offset);
    offset += sizeof(uint8_t);
    if (type == LUA_TSTRING) {
        if (offset + sizeof(size_t) > end) {
            return -1;
        }
        size_t len = *((size_t*)offset);
        offset += sizeof(size_t);

        if (offset + len > end) {
            return -1;
        }
        lua_pushlstring(L, offset, len);
        offset = offset + len;
        return offset - data;
    } else if (type == LUA_TNIL) {
        lua_pushnil(L);
        return offset - data;
    } else if (type == LUA_TTABLE) {
        lua_newtable(L);
        while(true) {
            if (offset + sizeof(uint8_t) > end) {
                lua_pop(L, 1);
                return -1;
            }
            uint8_t type = *((uint8_t*)offset);
            offset += sizeof(uint8_t);
            if (type == 0) {
                break;
            } else if (type == LUA_TNUMBER) {
                if (offset + sizeof(lua_Integer) > end) {
                    lua_pop(L, 1);
                    return -1;
                }
                lua_Integer key = *((lua_Integer*)offset);
                offset += sizeof(lua_Integer);
                lua_pushinteger(L, key);
            } else if (type == LUA_TSTRING) {
                if (offset + sizeof(size_t) > end) {
                    lua_pop(L, 1);
                    return -1;
                }
                size_t len = *((size_t*)offset);
                offset += sizeof(size_t);
                if (offset + len > end) {
                    lua_pop(L, 1);
                    return -1;
                }
                
                lua_pushlstring(L, offset, len);
                offset = offset + len;
            } else {
                lua_pop(L, 1);
                return -1;
            }
            int byteRead = this->decode(L, offset, end - offset);
            if (byteRead < 0) {
                lua_pop(L, 2);//pop key and table
                return -1;                           
            } else  {
                lua_settable(L, -3); 
            }
            offset += byteRead;
        }
        return offset - data;
    } else if (type == LUA_TREFERENCE) {
        if (offset + sizeof(uint16_t) > end) {
            return -1;
        }
        uint16_t len = *((uint16_t*)offset);
        offset += sizeof(uint16_t);
        if (offset + len > end) {
            return -1;
        }
        lua_pushlstring(L, offset, len);
        offset = offset + len;
        return offset - data;
    } else if (type == LUA_TPROTO) {
        if (offset + sizeof(size_t) > end) {
            return -1;
        }
        size_t totalLen = *((size_t*)offset);
        offset += sizeof(size_t);
        if (totalLen == 0) {
            return -1;
        }
        if (offset + sizeof(uint16_t) > end) {
            return -1;
        }
        uint16_t nameLen = *((uint16_t*)offset);
        offset += sizeof(uint16_t);
        if (offset + nameLen > end) {
            return -1;
        }
        std::string name;
        name.assign(offset, nameLen);
        offset += nameLen;

        size_t msgLen = totalLen - sizeof(uint16_t) - nameLen;
        //消息内容
        if (offset + msgLen > end) {
            return -1;
        }
        auto proto = this->coord->Proto->NewMessage(name.c_str());
        if (proto == nullptr) {
            return -1;
        }
        int err = proto->ParseFrom(offset, msgLen);
        if(err) {
            return -1;
        }
        offset += msgLen;   
        void* p = proto.Borrow();
        tolua_pushusertype_and_takeownership(L, p, protobuf::Message::_TypeName);
        return offset - data;
    } else if (type == LUA_TBOOLEAN) {
        if (offset + sizeof(uint8_t) > end) {
            return -1;
        }
        uint8_t value = *((uint8_t*)offset);
        offset += sizeof(uint8_t);
        lua_pushboolean(L, value);
        return offset - data;
    } else if (type == LUA_TNUMBER) {
        if (offset + sizeof(lua_Number) > end) {
            return -1;
        }
        lua_Number value = *((lua_Number*)offset);
        offset += sizeof(lua_Number);
        lua_pushnumber(L, value);
        return offset - data;
    } 
    return -1;
}

Reflect Script::NewReflect() {
    return Reflect(this->coord);
}

Reflect Script::NewTable() {
    auto table = Reflect(this->coord);
    table.SetTable();
    return table;
}

Reflect Script::NewString(const char* value) {
    auto table = Reflect(this->coord);
    table.SetString(value);
    return table;
}

Reflect Script::NewNumber(lua_Number value) {
    auto table = Reflect(this->coord);
    table.SetNumber(value);
    return table;
}

Reflect Script::NewTable(const char* path){
    if(this->SetTable(path)) {
        return Reflect(this->coord);
    }
    return this->Get(path);
}

Reflect Script::NewString(const char* path, const char* value){
    if(this->SetString(path, value)) {
        return Reflect(this->coord);
    }
    return this->Get(path);
}

Reflect Script::NewNumber(const char* path, lua_Number value){
    if(this->SetNumber(path, value)) {
        return Reflect(this->coord);
    }
    return this->Get(path);
}

const char* Script::GetLastError() {
    return this->lastError.c_str();
}

const char* Script::ToJson(const char* path) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    if (this->getValue(L, path)) {
        return nullptr;
    }
    size_t len;
    const char* str = cjson_encode(this->L, this->jsonParser, -1, &len);
    lua_pop(this->L, 1);
    if (str == nullptr) {
        return nullptr;
    }
    coordx::Append(buffer, str, len);
    coordx::Append(buffer, 0);
    buffer.Resize(buffer.Len() - 1);
    return buffer.Data();
}

int Script::ToJson(lua_State* L) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    size_t len;
    const char* str = cjson_encode(this->L, this->jsonParser, -1, &len);
    lua_pop(this->L, 1);
    if (str == nullptr) {
         return 0;
    }
    lua_pushlstring(this->L, str, len);
    return 1;
}

const char* Script::ToJson(lua_State* L, int index) {
    static thread_local byte_slice buffer;buffer.Resize(0);
    size_t len;
    const char* str = cjson_encode(this->L, this->jsonParser, index, &len);
    lua_pop(this->L, 1);
    if (str == nullptr) {
        return nullptr;
    }
    coordx::Append(buffer, str, len);
    coordx::Append(buffer, 0);
    buffer.Resize(buffer.Len() - 1);
    return buffer.Data();
}

int Script::ToJson(int index, byte_slice& buffer) {
    size_t len;
    const char* str = cjson_encode(this->L, this->jsonParser, index, &len);
    lua_pop(this->L, 1);
    if (str == nullptr) {
        return -1;
    }
    coordx::Append(buffer, str, len);
    coordx::Append(buffer, 0);
    buffer.Resize(buffer.Len() - 1);
    return 0;
}

int Script::FromJson(lua_State* L) {
    size_t len = 0;
    const char* data = lua_tolstring(L, -1, &len);
    int err = cjson_decode(this->L, this->jsonParser, data, len);
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return 0;
    }
    return 1;
}

int Script::FromJson(byte_slice& buffer) {
    int err = cjson_decode(this->L, this->jsonParser, buffer.Data(), buffer.Len());
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return err;
    }
    return 0;
}

int Script::FromJson(const char* data, size_t len) {
    int err = cjson_decode(this->L, this->jsonParser, data, len);
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return err;
    }
    return 0;
}

int Script::FromJson(const char* str) {
    int err = cjson_decode(this->L, this->jsonParser, str, strlen(str));
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return err;
    }
    return 0;
}

int Script::FromJson(const char* path, byte_slice& buffer) {
    int err = cjson_decode(this->L, this->jsonParser, buffer.Data(), buffer.Len());
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return err;
    }
    err = this->Set(path, -1);
    lua_pop(L, 1);
    return err;
}

int Script::FromJson(const char* path, const char* data, size_t len) {
    int err = cjson_decode(this->L, this->jsonParser, data, len);
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return err;
    }
    err = this->Set(path, -1);
    lua_pop(L, 1);
    return err;
}

int Script::FromJson(const char* path, const char* str) {
    int err = cjson_decode(this->L, this->jsonParser, str, strlen(str));
    if (err) {
        this->coord->CoreLogError("[Script] FromJson failed, error='%s'", cjson_error(this->L, this->jsonParser));
        return err;
    }
    err = this->Set(path, -1);
    lua_pop(L, 1);
    return err;
}


lua_State* Script::getThread() {
    if (this->threadArr.size() > 0) {
        lua_State* L = this->threadArr.back();
        this->threadArr.pop_back();
        return L;
    } else {
        lua_State* L = lua_newthread(this->L);
        if (nullptr == L) {
            this->coord->CoreLogError("[Script] getThread failed, error='lua_newthread'");
            return nullptr;
        }
        this->runningThreadSet.insert(L);
        return L;
    }
}

void Script::freeThread(lua_State* L) {
    auto it = this->runningThreadSet.find(L);
    if (it == this->runningThreadSet.end()) {
        this->coord->CoreLogError("[Script] freeThread failed, error='thread not found'");
        return;
    }
    this->runningThreadSet.erase(it);
    this->threadArr.push_back(L);
    lua_gc(L, LUA_GCCOLLECT, 0);
}

}
}


