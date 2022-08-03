#pragma once 

#include "coord/component/component.h"
#include "coord/base/base_agent.h"
#include "coord/gate/gate_packet.h"
#include "coord/builtin/destoryable.h"
#include "coord/protobuf/init.h"
#include "coord/net/tcp_agent.h"
#include "coord/websocket/websocket_agent.h"
#include <stdlib.h>
#include <uv.h>
#include <map>
#include <string>

namespace coord {//tolua_export
namespace protobuf {
class Reflect;
}
class Coord;
namespace gate {

enum GateAgentStatus {
	GateAgentStatus_Start = 0,
	GateAgentStatus_Handshake = 1,
	GateAgentStatus_Working = 2,
	GateAgentStatus_Closed = 3,
};

class Gate;
class Packet;
class GateSession;

class GateAgent : public base_agent, public net::ITcpAgentHandler, public websocket::IAgentHandler {
CC_CLASS(GateAgent);  
public:
    GateAgent(Coord* coord, Gate* gate, net::TcpAgent* tcpAgent);
    GateAgent(Coord* coord, Gate* gate, websocket::Agent* webSocketAgent);
    virtual ~GateAgent();
public:
    // 发送接口
    virtual int send(const char* data, size_t len);
    virtual int send(byte_slice& data);
    int send(PacketType type, const char* data, size_t len);
    int response(uint64_t id, const char* route, const byte_slice& data);
    int response(uint64_t id, const char* route, const char* data, size_t len);
    int response(uint64_t id, const char* route, protobuf::Reflect* proto);
    int response(uint64_t id, const char* route, ::google::protobuf::Message* message);
    int push(const char* route, google::protobuf::Message* proto);
    int push(const char* route, protobuf::Reflect* proto);
    void sendHandShakeFail();
    //踢下线
    void kick(const char* reason);
    void recvClose();
    void heartbeatInterval();
    void registerInterval();
    void close();
    //implement net::ITcpAgentHandler begin
    virtual void recvTcpNew(net::TcpAgent* agent);
    virtual void recvTcpClose(net::TcpAgent* agent);
    virtual void recvTcpError(net::TcpAgent* agent);
    virtual int recvTcpData(net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end
    // implement websocket::IAgentHandler begin
    virtual void recvWebSocketClose(websocket::Agent* agent);
    virtual void recvWebSocketFrame(websocket::Agent* agent, websocket::Frame* frame);
    // implement websocket::IAgentHandler end
    // packet处理函数
    int recvData(char* data, size_t len);
    void recvPacket(Packet* packet);
    void recvHandShake(Packet* packet);
    void recvHandShakeAck(Packet* packet);
    void recvData(Packet* packet);
public:
    Gate*               gate;
    GateSession*        session;
    std::string         secret;
    bool                encrypt;
    int                 status;
    uint64_t            lastHeartbeatTime;
    net::TcpAgent*      tcpAgent;
    websocket::Agent*   webSocketAgent;
};

GateAgent* newGateAgent(Coord* coord, Gate* gate, net::TcpAgent* tcpAgent);
GateAgent* newGateAgent(Coord* coord, Gate* gate, websocket::Agent* webSocketAgent);


}//tolua_export
}//tolua_export


