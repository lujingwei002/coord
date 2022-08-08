#pragma once 

#include "coord/base/base_agent.h"

namespace coord {

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


