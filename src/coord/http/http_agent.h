#pragma once 


#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/base/base_agent.h"
#include <uv.h>
#include "coord/http/http_util.h"
#include "coord/http/http_base.h"
#include "coord/net/tcp_agent.h"
#include "coord/builtin/slice.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <queue>

namespace coord {
    class Coord;
    namespace net {
        class RecvBuffer;
        class TcpAgent;
    }
    namespace http {
        class HttpServer;
        class HttpAgent;
        class HttpRequest;
        class HttpResponse;
    }
    namespace websocket {
        class Agent;
    }
}



namespace coord {//tolua_export
namespace http {//tolua_export

class IHttpAgentHandler {//tolua_export
public:
    virtual void recvHttpClose(HttpAgent* agent) = 0;
    virtual int recvHttpData(HttpAgent* agent, char* data, size_t len) = 0;
};//tolua_export

class HttpAgent : public base_agent, public net::ITcpAgentHandler {//tolua_export
CC_CLASS(HttpAgent);
friend HttpServer;
friend HttpRequest;
friend HttpResponse;
friend coord::websocket::Agent;
private:
    HttpAgent(Coord* coord, HttpServer* server, net::TcpAgent* tcpAgent);
    virtual ~HttpAgent();
public:
    void Close();
    void SetHandler(IHttpAgentHandler* handler);
public:
    //implement net::ITcpAgentHandler
    virtual void recvTcpNew(net::TcpAgent* agent);
    virtual void recvTcpClose(net::TcpAgent* agent);
    virtual void recvTcpError(net::TcpAgent* agent);
    virtual int recvTcpData(net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end
protected:
    //implement base_agent
    virtual int send(byte_slice& data);
    virtual int send(const char* data, size_t len);
    //implement base_agent
    // 根据id, 保证按顺序返回response给客户端
    int response(uint64_t id, byte_slice& data);
private:
    int writeBioToSocket();
    void readDecryptData();
    int recvData(char* data, size_t len);
    int recvEncryptData(char* data, size_t len);
    void catchHttpException(HttpRequest* request, HttpException& e);
    void catchPageNotFoundException(HttpRequest* request, HttpPageNotFoundException& e);
    void recvHttpRequest(HttpRequest* request);
    void recvHttpUpgrade(HttpRequest* request);
    void responseWaitQueueIfNeed();
private:
    HttpServer*         server;
    HttpRequest*        request;
    bool                isUpgrade;
    bool                isKeepAlive;
    net::TcpAgent*      tcpAgent;
    IHttpAgentHandler*  handler;
    uint64_t            requestId;
    // 保证按顺序返回response
    uint64_t            minimumAlreadyResponseRequestId;
    std::priority_queue<uint64_t, std::vector<uint64_t>, std::less<uint64_t> > requestIdWaitingResponse;
    std::map<uint64_t, byte_slice> payloadWaitingResponse;
    // ssl相关
    SSL*                ssl;
    BIO*                read_bio;
    BIO*                write_bio;  
};//tolua_export

}//tolua_export
}//tolua_export


