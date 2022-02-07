#pragma once 


#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include <libuv/uv.h>
#include "coord/http/http_util.h"
#include "coord/http/http_base.h"
#include "coord/net/tcp_agent.h"
#include "coord/builtin/slice.h"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

namespace coord {//tolua_export
class Coord;

namespace net {
class RecvBuffer;
class TcpAgent;
}
namespace http {//tolua_export
    
class HttpServer;
class HttpAgent;
class HttpRequest;
class HttpResponse;

class IHttpAgentHandler {//tolua_export
public:
    virtual void recvHttpClose(HttpAgent* agent) = 0;
    virtual int recvHttpData(HttpAgent* agent, char* data, size_t len) = 0;
};//tolua_export

class HttpAgent : public Destoryable, public net::ITcpAgentHandler {//tolua_export
CC_CLASS(HttpAgent);
public:
    static HttpAgent* New(Coord* coord, HttpServer* server, net::TcpAgent* tcpAgent);
public:
    HttpAgent(Coord* coord, HttpServer* server, net::TcpAgent* tcpAgent);
    virtual ~HttpAgent();
    void Close();
    void SetHandler(IHttpAgentHandler* handler);
public:
    int send(byte_slice& data);
    int writeBioToSocket();
    void readDecryptData();
    int recvData(char* data, size_t len);
    int recvEncryptData(char* data, size_t len);

    //重置状态, 使HTTP服务端可以转移向该连接上的下一个请求。
    void reset();
    void recvHttpException(HttpRequest* request, HttpException& e);
    void recvPageNotFoundException(HttpRequest* request, HttpPageNotFoundException& e);
    void recvHttpRequest(HttpRequest* request);
    void recvHttpUpgrade(HttpRequest* request);

    //implement net::ITcpAgentHandler
    virtual void recvTcpNew(net::TcpAgent* agent);
    virtual void recvTcpClose(net::TcpAgent* agent);
    virtual void recvTcpError(net::TcpAgent* agent);
    virtual int recvTcpData(net::TcpAgent* agent, char* data, size_t len);
    //implement net::ITcpAgentHandler end

public:
    Coord* coord;
    int sessionId;
    HttpServer* server;
    HttpRequest* request;
    std::string remoteAddr;
    bool isUpgrade;
    bool isKeepAlive;
    SSL *ssl;
    SSL_CTX *ssl_ctx;
    BIO *read_bio;
    BIO *write_bio;  
    net::TcpAgent* tcpAgent;
    IHttpAgentHandler* handler;
};//tolua_export

}//tolua_export
}//tolua_export


