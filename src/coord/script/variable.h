#pragma once 

#include "coord/coordx.h"
#include "coord/protobuf/init.h"
#include <cstdlib>
#include <string>
#include <cstddef>
#include <any>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {//tolua_export

class Coord;

namespace script {//tolua_export

class Variable : public coordx::RcObject {//tolua_export
public:
    Variable();
    Variable(Coord* coord);
    Variable(Coord* coord, int ref, int type);
    Variable(const Variable& other);
    Variable(Variable&& other);
    Variable& operator=(const Variable& other);
    ~Variable();
public:
    
    /// #self.is operation
    bool IsTable();    
    bool IsNumber();    
    bool IsNil();    
    bool IsString();
    bool IsBool();

    /// #self operation
    lua_Number GetNumber();
    const char* GetString();

    /// #self.set operation
    Variable& operator=(const std::any& other);
    Variable& operator=(std::nullptr_t);
   // Variable& operator=(const std::initializer_list<std::any>& value);
     Variable& operator=(const std::initializer_list<std::tuple<std::any, std::any>>& value);
    int SetTable();

    /// #table.get operation
    bool GetBool(const char* key);
    lua_Number GetNumber(const char* key);
    const char* GetString(const char* key);
    Variable GetTable(const char* key);

    /// #table.set operation
    int SetBool(const char* key, bool value);           //tolua_export
    int Set(const char* key, const char* value);  
    int SetString(const char* key, const char* value);  //tolua_export
    int SetNumber(const char* key, lua_Number value);   //tolua_export
    Variable SetTable(const char* key);                  //tolua_export
    int SetTable(const char* key, Variable& table);

    /// #array.set operation
    int SetBool(int key, bool value);                   //tolua_export
    int Set(int key, const char* value);          
    int SetString(int key, const char* value);          //tolua_export
    int SetNumber(int key, lua_Number value);           //tolua_export
    Variable SetTable(int key);                          //tolua_export
    int SetTable(int key, Variable& table);

    /// #array.get operation
    bool GetBool(int key);
    lua_Number GetNumber(int key);
    const char* GetString(int key);
    Variable GetTable(int key);

    /// #self operation
    const char* DebugString();                             //tolua_export
    const char* ShortDebugString();
    int Decode(byte_slice& data);        
    int Decode(const char* data, size_t len);        
    int Encode(byte_slice& data);

    void Push();
public:
	bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
public:
    Coord*  coord;
    int     ref;
    int     type;
public:
    static Variable NullPtr;
};//tolua_export

}//tolua_export
}//tolua_export

