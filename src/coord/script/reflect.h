#pragma once 

#include "coord/coordx.h"
#include "coord/protobuf/init.h"
#include <cstdlib>
#include <string>
#include <cstddef>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {//tolua_export

class Coord;

namespace script {//tolua_export

class Reflect : public coordx::RcObject {//tolua_export
public:
    Reflect();
    Reflect(Coord* coord);
    Reflect(Coord* coord, int ref, int type);
    Reflect(const Reflect& other);
    Reflect(Reflect&& other);
    Reflect& operator=(const Reflect& other);
    ~Reflect();
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
    int SetTable();
    int SetString(const char* value);
    int SetNumber(lua_Number value);
    int SetBool(bool value);
    int SetNil();

    /// #table.get operation
    bool GetBool(const char* key);
    lua_Number GetNumber(const char* key);
    const char* GetString(const char* key);
    Reflect GetTable(const char* key);

    /// #table.set operation
    int SetBool(const char* key, bool value);           //tolua_export
    int Set(const char* key, const char* value);  
    int SetString(const char* key, const char* value);  //tolua_export
    int SetNumber(const char* key, lua_Number value);   //tolua_export
    Reflect SetTable(const char* key);                  //tolua_export
    int SetTable(const char* key, Reflect& table);

    /// #array.set operation
    int SetBool(int key, bool value);                   //tolua_export
    int Set(int key, const char* value);          
    int SetString(int key, const char* value);          //tolua_export
    int SetNumber(int key, lua_Number value);           //tolua_export
    Reflect SetTable(int key);                          //tolua_export
    int SetTable(int key, Reflect& table);

    /// #array.get operation
    bool GetBool(int key);
    lua_Number GetNumber(int key);
    const char* GetString(int key);
    Reflect GetTable(int key);

    /// #self operation
    const char* DebugString();                             //tolua_export
    const char* ToShortString();
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
    static Reflect NullPtr;
};//tolua_export

}//tolua_export
}//tolua_export

