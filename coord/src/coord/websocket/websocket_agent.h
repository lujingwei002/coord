#pragma once 


#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <libuv/uv.h>
#include "coord/http/http_agent.h"
#include "coord/builtin/slice.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

namespace coord {//tolua_export
class Coord;

namespace net {

}
namespace http {
class HttpServer;
}
    
namespace websocket {//tolua_export
class Server;
class Frame;
class Agent;

class IAgentHandler {//tolua_export
public:
    virtual void recvWebSocketClose(Agent* agent) = 0;
    virtual void recvWebSocketFrame(Agent* agent, Frame* frame) = 0;
};//tolua_export

class Agent : public Destoryable, public http::IHttpAgentHandler { //tolua_export
CC_CLASS(Agent);
public:
    Agent(Coord* coord, Server* server, http::HttpAgent* httpAgent);
    virtual ~Agent();
public:
    void Close();
    void SetHandler(IAgentHandler* handler);
    //帧发送函数
    int SendBinaryFrame(const char* data, size_t len);//tolua_export
    int SendBinaryFrame(byte_slice& data);
    int SendStringFrame(const char* str);//tolua_export
public:

    //帧发送函数
    int send(byte_slice& data);
    int sendPongFrame();
    int sendFrame(int opcode, const char* data, size_t datalen);
    int sendFrame(int opcode, byte_slice& data);

    //帧处理函数
    void recvWebSocketFrame(Frame* frame);
    void recvWebSocketPingFrame(Frame* frame);
    void recvWebSocketCloseFrame(Frame* frame);
    void recvWebSocketDataFrame(Frame* frame);

    // @implement http::IHttpAgentHandler
    virtual void recvHttpClose(http::HttpAgent* agent);
    virtual int recvHttpData(http::HttpAgent* agent, char* data, size_t len);
    // @implement http::IHttpAgentHandler end
public:
    Coord*                  coord;
    int                     sessionId;
    Server*                 server;
    Frame*                  frame;
    std::string             remoteAddr;
    http::HttpAgent*        httpAgent;
    IAgentHandler*          handler;
};//tolua_export

Agent* newAgent(Coord* coord, Server* server, http::HttpAgent* httpAgent);

}//tolua_export
}//tolua_export


