#pragma once 

#include "coord/builtin/destoryable.h"
#include "coord/net/tcp_listener.h"
#include "coord/builtin/slice.h"
#include <map>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

namespace coord {
    class Coord;
    namespace net {
        class TcpListener;
        class TcpAgent;
    }
    namespace http {
        class HttpServer;
        class HttpAgent;
        class HttpRequest;
        class HttpResponse;
        class HttpRouter;
    }
    namespace login {
        class LoginSvr;
    }
}

namespace coord {//tolua_export
namespace http {//tolua_export


class IHttpHandler {//tolua_export
friend HttpServer;
protected:
    virtual void recvHttpRequest(HttpRequest* request) = 0;
    virtual void recvHttpUpgrade(HttpAgent* agent, HttpRequest* request) = 0;
};//tolua_export

class HttpServerConfig {//tolua_export
public:
    std::string     Host;               //tolua_export
    unsigned short  Port;               //tolua_export
    int             Backlog;            //tolua_export
    /// 是否使用https, 如果设置为true, 还要设置SSLPemFile, SSLKeyFile
    bool            SSLEncrypt;         //tolua_export
    std::string     SSLPemFile;         //tolua_export
    std::string     SSLKeyFile;         //tolua_export
    int             RecvBufferSize;     //tolua_export
    std::string     AssetDir;           //tolua_export
    bool            UseEtag;            //tolua_export
};//tolua_export

class HttpServer : public net::ITcpHandler, public Destoryable {//tolua_export
CC_CLASS(HttpServer);
friend Coord;
friend HttpAgent;
friend HttpRequest;
friend HttpResponse;
friend HttpRouter;
private:
    HttpServer(Coord* coord);
    virtual ~HttpServer();
private:
    // implement net::ITcpHandler
    virtual void recvTcpNew(net::TcpListener* listener, net::TcpAgent* agent);
    // implement net::ITcpHandler end

    // agent通知server准备关闭
    void recvAgentClose(HttpAgent* agent);
    // agent通知server协议升级
    void recvHttpUpgrade(HttpAgent* agent, HttpRequest* request);
    // agent通知server有新的请求
    void recvHttpRequest(HttpAgent* agent, HttpRequest* request);
private:
    std::map<int, HttpAgent*>   agentDict;
    Coord*                      coord;
    net::TcpListener*           listener;
    IHttpHandler*               handler;
    HttpServerConfig            config;
    SSL_CTX*                    sslContext;






public:
    /// 启动http server
    int Start();                                //tolua_export
    /// 设置handler
    void SetHandler(IHttpHandler* handler);
    /// 关闭http server
    void Close();
    /// 获取配置
    HttpServerConfig* DefaultConfig();          //tolua_export
public:
    /// 路由
    HttpRouter*                 Router;         //tolua_export


    
};//tolua_export


}//tolua_export
}//tolua_export
