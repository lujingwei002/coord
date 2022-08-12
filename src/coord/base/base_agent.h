#pragma once 

#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/base/base_packet.h"
#include "coord/protobuf/init.h"
#include "proto/coord.pb.h"
#include "coord/base/base_message.h"
#include <google/protobuf/message.h>
#include "coord/coord.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>
namespace coord {//tolua_export
    
class Coord;
class base_response;

enum base_agent_status {
	base_agent_status_none = 0,
	base_agent_status_handshake = 1,
	base_agent_status_working = 2,
	base_agent_status_closed = 3,
};


// agent基类
class base_agent : public RcObject {//tolua_export
CC_CLASS(base_agent);
friend base_response;
protected:
    base_agent(Coord *coord);
    virtual ~base_agent();
protected:
    /// 子类需要实现的方法
    virtual int send(const char* data, size_t len) = 0;
    /// 子类需要实现的方法
    virtual int send(byte_slice& data) = 0;
public:
    /// 会话id
    int                     SessionId;
    /// 对方的地址
    std::string             RemoteAddr;
protected:
    Coord*                  coord;
};//tolua_export




}//tolua_export


