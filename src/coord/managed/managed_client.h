#pragma once 

#include "coord/pipe/pipe_client.h"
#include "coord/base/base_client.h"
#include <vector>
#include <iostream>
#include <map>

namespace coord {
    class Coord;
    namespace managed {
        class Managed;
        class ManagedPromise;
        class ManagedConnectPromise;
    }
}

namespace coord {//tolua_export
namespace managed {//tolua_export

typedef base_client<ManagedPromise> base_managed_client;
class ManagedClient: public base_managed_client, public pipe::IPipeClientHandler {//tolua_export
CC_CLASS(ManagedClient);
friend coord::Coord;
friend managed::Managed;
private:
    typedef base_packet managed_packet;
    typedef base_packet_header managed_packet_header;
    typedef base_packet_type managed_packet_type;
private:
    ManagedClient(Coord *coord, Managed* managed, const std::string& path, int ipc);
public:
    virtual ~ManagedClient();
public:
    /// 关闭链接
    int Close();
    /// 发起连接
    ManagedPromise* Connect();
    int Notify(const std::string& route, const char* data, size_t len);
    ManagedPromise* Request(const std::string& route, Argument* argument);
    ManagedPromise* Request(const std::string& route, const char* data, size_t len);
    ManagedPromise* Request(const std::string& route, google::protobuf::Message* proto);
    virtual int Send(byte_slice& packet);
protected:
    virtual void onDestory();
private:
    int sendHandshakePacket();
    void flushPacketCache();
    void recvPacket(managed_packet* packet);
    void recvPacketHeartbeat(managed_packet* packet);
    void recvPacketHandShake(managed_packet* packet);
    void recvPacketData(managed_packet* packet);
    void responseConnect(int err);
public:
    //implement pipe::IPipeClientHandler begin
    virtual void EvConnect();
    virtual void EvClose();
    virtual void EvError(int err);
    virtual void EvConnectError(int err);
    virtual int EvData(char* data, size_t len);
    //implement pipe::IPipeClientHandler end
public:
    Managed*                            managed;
    std::string                         name;
    std::string                         path;
    int                                 status;
    int                                 ipc;
    pipe::PipeClient*                   client;
    ManagedPromise*                     connectPromise;
    base_handshake_request              handshakeRequest;
    base_handshake_response             handshakeResponse;
    base_handshake_ack                  handshakeAck;
};//tolua_export

}//tolua_export
}//tolua_export


