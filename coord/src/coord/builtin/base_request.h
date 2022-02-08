#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/argument.h"
#include "coord/json/init.h"
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

class BaseRequest : public Destoryable { //tolua_export
CC_CLASS(BaseRequest);
public:
    BaseRequest(Coord* coord);
    virtual ~BaseRequest();
public:
    ///
    ///  # 返回protobuf格式类型的数据
    ///
    protobuf::Reflect& Proto(const char* name);//tolua_export
    ///
    ///  # 返回protobuf格式类型的数据
    ///
    int Proto(google::protobuf::Message& message);
    ///
    ///  # 返回字符串
    ///
    const char* String();//tolua_export
    ///
    ///  # 返回负载长度
    ///
    size_t Len();//tolua_export
    ///
    ///  # 返回argument格式类型的数据
    ///
    Argument* Args();//tolua_export
    ///
    ///  # 返回字符串
    ///
    int String(lua_State* L);//tolua_export 
    ///
    ///  # 返回argument格式类型的数据,并用unpack展开
    ///
    int Unpack(lua_State* L);//tolua_export 
    ///
    /// # 返回lua table格式类型的数据
    ///  # @return script::Reflect
    ///
    int Table(lua_State* L);//tolua_export
    ///
    /// # 返回argument格式类型的数据
    /// # @return script::Reflect
    ///
    script::Reflect& Table();
    json::Reflect Json();   //tolua_export
public:
    Coord*                      coord;
    uint64_t                    id;
    std::string                 route;
    uint64_t                    reqTime; 
    byte_slice                  payload;
    Argument*                   argv;
    protobuf::Reflect           proto;
    int8_t                      type;
    script::Reflect             table;
};//tolua_export

}//tolua_export