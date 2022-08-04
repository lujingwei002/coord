#pragma once 
#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/argument.h"
#include "coord/base/base_reader.h"
#include "coord/base/base_writer.h"
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

namespace coord {
    class base_request;
    class Coord;
    class base_agent;
    class internal_agent;
}

namespace coord {//tolua_export


class base_response : public Destoryable { //tolua_export
CC_CLASS(base_response);
protected:
    base_response(Coord* coord, base_agent* agent, base_request* request);
    virtual ~base_response();
public:
    /// 将数据刷新到远端
    virtual int Flush() = 0;
    virtual void DebugLog();
    void Resolve();                                     //tolua_export
    void Reject(int code);                              //tolua_export
public:
    Coord*                      coord;
    int                         Code;                   //tolua_export
    byte_slice                  Payload;
    uint64_t                    ReqTime; 
    /// 数据类型
    int                         DataType;
protected:
    virtual void onDestory(); 
protected:
    base_agent*                 agent;
    base_request*               request;
    protobuf::Reflect           proto;
    Argument*                   argv;
    script::Reflect             table;
};//tolua_export








class internal_response : public base_response {//tolua_export
CC_CLASS(internal_response);
protected:
    internal_response(Coord* coord, internal_agent* agent, base_request* request);
    virtual ~internal_response();
public:
    virtual int Flush();
    /// ##export method
    /// 返回JSON格式的数据
    int Json();

    /// 返回protobuf格式的数据。 
    int Proto(google::protobuf::Message& message);
    protobuf::Reflect& Proto(const char* name);         //tolua_export
    int Proto(protobuf::Reflect& proto);                //tolua_export
    protobuf::Reflect& Proto();                         //tolua_export

    /// 返回字符串类型的数据
    int String(const char* data, size_t len);
    int String(const char* data);                       //tolua_export

    /// 返回argument类型的数据
    Argument* Args();                                   //tolua_export
    int Pack(lua_State* L);                             //tolua_export 

    /// 返回table类型的数据
    int Table(lua_State* L);                            //tolua_export
    script::Reflect& Table();
private:
    internal_agent* agent;
};//tolua_export
}//tolua_export
