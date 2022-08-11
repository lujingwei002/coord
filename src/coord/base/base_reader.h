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
#include "coord/protobuf/init.h"
#include "coord/script/reflect.h"
#include "coord/base/base_message.h"
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export

class Coord;

class IReader { //tolua_export
public:
    ///
    ///  # 返回protobuf格式类型的数据
    ///
    virtual protobuf::Reflect& Proto(const char* name) = 0;//tolua_export
    ///
    ///  # 返回protobuf格式类型的数据
    ///
    virtual int Proto(google::protobuf::Message& message) = 0;
    ///
    ///  # 返回字符串
    ///
    virtual const char* String() = 0;//tolua_export
    ///
    ///  # 返回负载长度
    ///
    virtual size_t Len() = 0;//tolua_export
    ///
    ///  # 返回argument格式类型的数据
    ///
    virtual Argument* Args() = 0;//tolua_export
    ///
    ///  # 返回字符串
    ///
    virtual int String(lua_State* L) = 0;//tolua_export 
    ///
    ///  # 返回argument格式类型的数据,并用unpack展开
    ///
    virtual int Unpack(lua_State* L) = 0;//tolua_export 
    ///
    /// # 返回lua table格式类型的数据
    ///  # @return script::Reflect
    ///
    virtual int Table(lua_State* L) = 0;//tolua_export
    ///
    /// # 返回argument格式类型的数据
    /// # @return script::Reflect
    ///
    virtual script::Reflect& Table() = 0;
    virtual json::JsonRef Json() = 0;   //tolua_export
};//tolua_export

class base_reader { //tolua_export
CC_CLASS(base_reader);
public:
    base_reader(Coord* coord);
    virtual ~base_reader();
public:
    ///
    ///  # 返回protobuf格式类型的数据
    ///
    virtual protobuf::Reflect& Proto(const char* name);//tolua_export
    ///
    ///  # 返回protobuf格式类型的数据
    ///
    virtual int Proto(google::protobuf::Message& message);
    ///
    ///  # 返回字符串
    ///
    virtual const char* String();//tolua_export
    ///
    ///  # 返回负载长度
    ///
    virtual size_t Len();//tolua_export
    ///
    ///  # 返回argument格式类型的数据
    ///
    virtual Argument* Args();//tolua_export
    ///
    ///  # 返回字符串
    ///
    virtual int String(lua_State* L);//tolua_export 
    ///
    ///  # 返回argument格式类型的数据,并用unpack展开
    ///
    virtual int Unpack(lua_State* L);//tolua_export 
    ///
    /// # 返回lua table格式类型的数据
    ///  # @return script::Reflect
    ///
    virtual int Table(lua_State* L);//tolua_export
    ///
    /// # 返回argument格式类型的数据
    /// # @return script::Reflect
    ///
    virtual script::Reflect& Table();
    virtual json::JsonRef Json();   //tolua_export
public:
    Coord*                      coord;
    int                         dataType;
    byte_slice                  payload;
    Argument*                   argv;
    protobuf::Reflect           proto;
    int8_t                      type;
    script::Reflect             table;
};//tolua_export

}//tolua_export
