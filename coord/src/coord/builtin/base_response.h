#pragma once 
#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/argument.h"
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

enum response_type {
    response_type_none = 0,
    response_type_string = 1,
    response_type_proto = 2,
    response_type_json = 3,
    response_type_argument = 4,
    response_type_table = 5,
};

class Coord;

class BaseResponse : public Destoryable { //tolua_export
public:
    BaseResponse(Coord* coord);
    virtual ~BaseResponse();
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

    void Resolve();                                     //tolua_export
    void Reject(int code);                              //tolua_export
public:
    virtual int flush();
    void clear();
public:
    Coord*                      coord;
    byte_slice                  payload;
    std::string                 route;
    protobuf::Reflect           proto;
    int                         code;
    Argument*                   argv;
    script::Reflect             table;
    int8_t                      type;
};//tolua_export

}//tolua_export