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
class base_agent : public Destoryable {//tolua_export
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




// 内置协议实现
class internal_agent : public base_agent {
CC_CLASS(internal_agent);
protected:
    internal_agent(Coord *coord);
    virtual ~internal_agent();
public:
    /// ##export method
    /// 推送消息
    int Notify(const std::string& route, protobuf::Reflect& proto);
    /// 推送消息
    int Notify(const std::string& route, ::google::protobuf::Message* message);
    /// 推送消息
    int Notify(const std::string& route, const char* data, size_t len);
    /// 推送消息
    int Notify(const std::string& route, byte_slice& data);
    //响应request
    int Response(uint64_t id, int code, const char* data, size_t len);
    //响应request
    int Response(uint64_t id, int code, byte_slice& data);
    int Response(uint64_t id, int code, protobuf::Reflect& proto);
    int Response(uint64_t id, int code, ::google::protobuf::Message* message);
    int Response(uint64_t id, int code, Argument* argument);
    int SendPacket(base_packet_type type, ::google::protobuf::Message* message);
};

}//tolua_export


