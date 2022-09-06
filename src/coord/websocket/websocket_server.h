#pragma once 


#include "coord/component/component.h"
#include "coord/http/http_server.h"
#include "coord/http/http_agent.h"
#include "coord/coordx.h"
#include <map>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
namespace coord {//tolua_export

class Coord;
namespace http {
class HttpRequest;
class HttpResponse;
class HttpAgent;
class HttpServer;
}
namespace websocket {//tolua_export

class Agent;
class Frame;
class Router;

class IWebSocketHandler {//tolua_export
public:
    virtual void recvWebSocketNew(Agent* agent) = 0;
};//tolua_export

class WebSocketServerConfig {//tolua_export
public:
    std::string     Host;               //tolua_export
    unsigned short  Port;               //tolua_export
    int             Backlog;            //tolua_export
    bool            SSLEncrypt;         //tolua_export
    std::string     SSLPemFile;         //tolua_export
    std::string     SSLKeyFile;         //tolua_export
    int             RecvBufferSize;     //tolua_export
};//tolua_export

class Server : public http::IHttpHandler {//tolua_export
RC_CLASS(Server);
public:
    Server(Coord* coord);
    virtual ~Server();
public:
    int Start();//tolua_export
    void SetHandler(IWebSocketHandler* handler);
    void Close();
    WebSocketServerConfig* DefaultConfig();//tolua_export
public:
    // implement http::IHttpHandler
    virtual void recvHttpRequest(http::HttpRequest* request);
    virtual void recvHttpUpgrade(http::HttpAgent* httpAgent, http::HttpRequest* request);
    // implement http::IHttpHandler end

    // agent通知server准备关闭
    void recvAgentClose(Agent* agent);
    // agent通知server协议升级
    void recvWebSocketNew(Agent* agent);
    // agent通知server连接断开
    void recvWebSocketClose(Agent* agent);
    // agent通知server收到数据帧
    void recvWebSocketFrame(Agent* agent, Frame* frame);
public:
    websocket::Router*              Router;//tolua_export
public:
    std::map<int, Agent*>           agentDict;
    Coord*                          coord;
    IWebSocketHandler*              handler;
    WebSocketServerConfig           config;
    http::HttpServer*               httpServer;
};//tolua_export

Server* newWebSocketServer(Coord* coord);

}//tolua_export
}//tolua_export
