#pragma once 
#include "coord/builtin/init.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/error.h"
#include "coord/json/reflect.h"
#include <string>
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

/// ```c++
///
/// auto json = coorda->Json->Decode(R"({"nickname":"ljw"})");
/// json.GetString("nickname");
///
/// auto object = coorda->Json->NewObject();
///
/// ```
///
///
///

namespace coord {//tolua_export
class Coord;
namespace json {//tolua_export

class JsonMgr {
public:
    JsonMgr(Coord* coord);
    virtual ~JsonMgr();
public:
    Reflect NewString(const char* data = nullptr);
    Reflect NewObject();
    Reflect NewArray();
    Reflect NewNull();
    Reflect NewBool(bool value);
    
    Reflect Decode(const char* data);
    Reflect Decode(std::string& data);
    int Encode(Reflect& json, byte_slice& buffer);
    int Encode(Reflect& json, std::string& buffer);
public:
    int main();
    int registerMetatable();
public:
    Coord*    coord;
};//tolua_export

JsonMgr* newJsonMgr(Coord* coord);

}//tolua_export
}//tolua_export