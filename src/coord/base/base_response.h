#pragma once 
#include "coord/coordx.h"
#include "coord/argument/argument.h"
#include "coord/base/base_reader.h"
#include "coord/base/base_writer.h"
#include <uv.h>
#include <map>
#include <tuple>
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


class base_response : public coordx::RcObject { //tolua_export
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
    protobuf::MessageRef        proto;
    Argument*                   argv;
    script::Reflect             table;
};//tolua_export






}//tolua_export
