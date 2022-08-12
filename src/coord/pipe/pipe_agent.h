#pragma once 


#include "coord/builtin/type.h"
#include "coord/builtin/destoryable.h"
#include "coord/net/recv_buffer.h"
#include "coord/builtin/slice.h"
#include <uv.h>
#include <string>
namespace coord {//tolua_export

class Coord;

namespace pipe {//tolua_export

class PipeListener;
class PipeAgent;

class IPipeAgentHandler {//tolua_export
friend PipeAgent;
protected:
    /// 管道关闭时触发
    virtual void EvClose(PipeAgent* agent) = 0;
    /// 管道错误时触发
    virtual void EvError(PipeAgent* agent) = 0;
    /// 管道接收到数据时触发
    virtual int EvData(PipeAgent* agent, char* data, size_t len) = 0;
};//tolua_export

///
/// PipeAgent的生命周期由PipeListener控制
/// PipeAgent关闭后，由PipeListener负责释放
///
class PipeAgent : public RcObject  {//tolua_export
CC_CLASS(PipeAgent);
friend PipeListener;
private:
    PipeAgent(Coord* coord, PipeListener* listen);
    virtual ~PipeAgent();
public:
    /// 发送数据
    int Send(const void* data, size_t len);
    /// 发送数据
    int Send(byte_slice& data);
    /// 设置handler
    void SetHandler(IPipeAgentHandler* handler);
    /// 设置接收缓冲区
    void SetRecvBuffer(size_t size);
    /// 关闭链接
    int Close();
public:
    /// 会话id
    int                 SessionId;
    /// 远程地址
    std::string         RemoteAddr;



private:
    static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void uv_close_cb(uv_handle_t* client);
    static void uv_read_cb(uv_stream_t *client, ssize_t byteRead, const uv_buf_t *buf);
    static void uv_write_cb(uv_write_t* req, int status);
    static void uv_shutdown_cb(uv_shutdown_t* req, int status);
    void evConnection();
    void evError(int status);
    void evData();
    void evClose();
    void evShutdown();
protected:
    Coord*              coord;
    IPipeAgentHandler*  handler;
    PipeListener*       listener;
    uv_pipe_t           handle;
    int                 sockfd;
    net::RecvBuffer     recvBuffer;  
    int                 status;      
    uv_shutdown_t       shutdownReq;
};//tolua_export


}//tolua_export
}//tolua_export


