#pragma once 

#include "coord/coordx.h"
#include "coord/memory/type.h"
#include <uv.h>
#include <map>
namespace coord {//tolua_export

class Coord;

namespace pipe {//tolua_export

void uv_pipe_connection_cb(uv_stream_t *server, int status);

class PipeAgent;
class PipeListener;

class IPipeHandler {//tolua_export
friend PipeListener;
protected:
    virtual void EvConnection(PipeListener* listener, PipeAgent* agent) = 0;
    /// 全部连接关闭后才会触发Close事件
    virtual void EvClose(PipeListener* listener) = 0;
};//tolua_export

class PipeListener : public coord::RcObject {//tolua_export
RC_CLASS(PipeListener);
friend PipeAgent;
friend void uv_pipe_connection_cb(uv_stream_t *server, int status);
public:
    PipeListener(Coord* coord);
    virtual ~PipeListener();
public:
    /// 开始侦听
    int Listen(const std::string& path, int backlog = 1024);//tolua_export
    /// 关闭服务器
    int Close();//tolua_export
    /// 设置handler
    void SetHandler(IPipeHandler* handler);
protected:
    // implement RcObject
    virtual void Destory();
    // implement RcObject
private:
    static void uv_close_cb(uv_handle_t* req);
    static void uv_pipe_connection_cb(uv_stream_t *server, int status);
    void evConnection(int status);
    void evClose();
    void recvAgentClose(PipeAgent* agent);
    void ifNotAgentDestoryMySelf();
protected:
    IPipeHandler*               handler;
    Coord*                      coord;
    uv_pipe_t                   server;
    int                         sessionId;
    std::map<int, PipeAgent*>   agentDict;
    int                         status;
    bool                        destoryDelay;
};//tolua_export

PipeListener* NewPipeListener(Coord* coord);

}//tolua_export
}//tolua_export


