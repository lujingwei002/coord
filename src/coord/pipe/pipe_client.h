#pragma once 


#include "coord/coordx.h"
#include "coord/memory/type.h"

#include "coord/net/recv_buffer.h"
#include <uv.h>
#include <string>
namespace coord {//tolua_export
class Coord;
namespace pipe {//tolua_export

class IPipeClientHandler {//tolua_export
public:
    /// 连接成功的话，会触发Connect事件
    virtual void EvConnect() = 0;
    /// 连接失败的话，会触发ConnectError, 接着会触发Close
    virtual void EvConnectError(int err) = 0;
    /// 连接成功后出错才会收到Error事件, 接着会触发Close
    virtual void EvError(int err) = 0;
    /// 连接成功后，收到数据的话会触发Data事件
    virtual int EvData(char* data, size_t len) = 0;
    /// 无论连接是否成功，发起过连接之后,关闭操作都会触发Close事件
    virtual void EvClose() = 0;
};//tolua_export

class PipeClient : public coord::RcObject {//tolua_export
RC_CLASS(PipeClient);
public:
    PipeClient(Coord* coord);
    virtual ~PipeClient();
public:
    /// 链接
    int Connect(const std::string& path, int ipc);
    /// 设置recv buff大小
    void SetRecvBuffer(size_t size);
    /// 设置handler
    void SetHandler(IPipeClientHandler* handler);
    /// 关闭链接
    int Close();
    /// 是否已经关闭, 初始末连接的状态， IsClose也是返回true
    bool IsClose();
    /// 是否已经连接
    bool IsConnected();
    /// 是否正在连接
    bool IsConnecting();
    /// 发送数据
    int Send(const char* data, size_t len);
    /// 发送数据
    int Send(byte_slice& data);
protected:
    // implement RcObject
    virtual void Destory();
    // implement RcObject
private:
    static void uv_connect_cb(uv_connect_t* req, int status);
    static void uv_close_cb(uv_handle_t* req);
    static void uv_alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf);
    static void uv_read_cb(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
    static void uv_shutdown_cb(uv_shutdown_t* req, int status);
    static void uv_write_cb(uv_write_t* req, int status);
    void evError(int err);
    void evClose();
    void evData();
    void evConnectError(int err);
    void evConnect();
    void evShutdown();
    int internalClose(int reason);
private:
    Coord*                  coord;
    uv_pipe_t               handle;    
    uv_shutdown_t           shutdownReq;
    uv_connect_t            connectReq;
    coord::net::RecvBuffer  recvBuffer;  
    IPipeClientHandler*     handler;     
    int                     status;
    int                     closeReason;
    bool                    destoryDelay;
};//tolua_export


}//tolua_export
}//tolua_export


