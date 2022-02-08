#pragma once 

#include "coord/builtin/type.h"
#include "coord/protobuf/init.h"
#include <uv.h>
#include <map>
#include <tuple>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}


namespace coord {//tolua_export
class Coord;

namespace protobuf{
class Reflect;
}

namespace gate {//tolua_export

class GateAgent;
class Gate;
class GatePromise;

class GateSession  { //tolua_export
CC_CLASS(GateSession);
public:
    GateSession(Coord* coord, GateAgent* agent);
    virtual ~GateSession();
public:
    //踢用户下线
    void Kick(const char* reason);//tolua_export
    int Push(const char* route, google::protobuf::Message* proto);
    //推送消息
    int Push(const char* route, protobuf::Reflect* proto);//tolua_export
    //关闭链接
    void Close();
    //登录
    GatePromise* Login(uint64_t userId);//tolua_export
    //是否已经登录
    bool IsAuth();//tolua_export
public:
    GateAgent* agent; 
    Gate* gate;
    Coord* coord;
    uint64_t Id;//tolua_export
    std::string RemoteAddr;//tolua_export
    uint64_t UserId;//tolua_export
};//tolua_export

GateSession* newGateSession(Coord* coord, GateAgent* agent);

}//tolua_export
}//tolua_export
