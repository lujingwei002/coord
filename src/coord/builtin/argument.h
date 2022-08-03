#pragma once 

#include "coord/builtin/slice.h"
#include "coord/protobuf/init.h"
#include "coord/script/reflect.h"
#include <cstdlib>
#include <string>
#include <vector>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {//tolua_export

class Coord;

enum ArgumentType {
    ArgumentTypeNone = 0,
    ArgumentTypeNil = 1,
    ArgumentTypeNumber = 2,
    ArgumentTypeString = 3,
    ArgumentTypeBoolean = 4,
    ArgumentTypeProto = 5,
    ArgumentTypeTable = 6,
};

class argument_item {
public:
    argument_item(Coord* coord) : coord(coord), type(0), proto(coord), table(coord) {
    }
    ~argument_item() {
    }
public:
    Coord*              coord;
    int8_t              type;
    int64_t             number;
    void*               data;
    std::string         str;
    protobuf::Reflect   proto;
    script::Reflect     table;
};

class Argument {//tolua_export
public:
    Argument(Coord* coord);
    ~Argument();
public:
    /// # hello
    int64_t GetNumber(size_t index);                  //tolua_export
    bool GetBool(size_t index);                       //tolua_export
    const char* GetString(size_t index);              //tolua_export
    protobuf::Reflect& GetProto(size_t index);        //tolua_export
    script::Reflect& GetTable(size_t index);          //tolua_export

    bool IsNone(size_t index);                     //tolua_export
    bool IsNil(size_t index);                      //tolua_export
    bool IsNumber(size_t index);                   //tolua_export
    bool IsString(size_t index);                   //tolua_export
    bool IsProto(size_t index);                    //tolua_export
    bool IsBool(size_t index);                     //tolua_export
    bool IsTable(size_t index);                    //tolua_export

    int AddNumber(int64_t value);                  //tolua_export    
    int AddString(const char* value);              //tolua_export
    int AddNil();                                  //tolua_export   
    int AddProto(protobuf::Reflect& proto); 
    int AddBool(bool value);                       //tolua_export 
    int AddTable(script::Reflect& table);  
    int AddTable(int ref, int type);  

    int Count();                                    //tolua_export
    int Type(size_t index);
    void Trace();                                   //tolua_export
    int Parse(byte_slice& data);        
    int Serialize(byte_slice& data);    
    int Pack(lua_State* L);                         //tolua_export            
    /*
     *将参数展开并push进lua中
     *返回：参数个数
     */
    int Unpack(lua_State* L);                       //tolua_export
    void DebugPrint();
public:
    /*
     *将参数打包进argument中
     *返回：error
     */
    int pack(lua_State* L, int i);
private:
    Coord*                      coord;
    std::vector<argument_item*> argv; 
};//tolua_export

}//tolua_export

