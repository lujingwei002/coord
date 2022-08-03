#pragma once 
#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/argument.h"
#include "coord/base/base_reader.h"
#include <uv.h>
#include <map>
#include <tuple>
#include "coord/builtin/slice.h"
#include "coord/gate/gate_message.h"
#include "coord/protobuf/init.h"
#include "coord/script/reflect.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export

class Coord;

class base_agent;
class base_writer { //tolua_export
public:
    base_writer(Coord* coord, base_agent* agent);
    virtual ~base_writer();
public:
    int Json();
    //返回protobuf格式的数据。 
    int Proto(google::protobuf::Message& message);
    //返回protobuf格式的数据。 设置后，不能更改消息类型。
    protobuf::Reflect& Proto(const char* name);         //tolua_export
    int Proto(protobuf::Reflect& proto);                //tolua_export
    protobuf::Reflect& Proto();                         //tolua_export
    int String(const char* data, size_t len);
    int String(const char* data);                       //tolua_export
    Argument* Args();                                   //tolua_export
    int Pack(lua_State* L);                             //tolua_export 
    //返回lua table格式的数据，重复调用会覆盖
    int Table(lua_State* L);                            //tolua_export
    script::Reflect& Table();
    virtual int Flush() = 0;
public:
    Coord*                      coord;
    base_agent*                 agent;
    byte_slice                  payload;
    protobuf::Reflect           proto;
    Argument*                   argv;
    script::Reflect             table;
    int8_t                      type;
};//tolua_export

}//tolua_export
