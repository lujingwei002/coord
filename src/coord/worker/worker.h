#pragma once 

#include "coord/builtin/type.h"
#include "coord/protobuf/init.h"
#include "coord/builtin/argument.h"
#include <vector>
#include <iostream>
#include <map>
#include <deque>
#include <uv.h>

namespace coord {//tolua_export
    
class Coord;

namespace protobuf {
class Reflect;
}
namespace worker {//tolua_export

class WorkerSlave;
class Request;
class WorkerRouter;
class Promise;
class Result;
class worker_packet;

class WorkerConfig {//tolua_export
public:
};//tolua_export

class Worker {//tolua_export
CC_CLASS(Worker);
public:
    Worker(Coord *coord);
    virtual ~Worker();
public:
    /// 获取cluser的配置信息
    WorkerConfig* DefaultConfig();
    
    /// 向worker发送request消息
    Promise* Request(const char* route, Argument& argv);
    /// 向worker发送request消息
    Promise* Request(const char* route, const char* data);
    /// 向worker发送request消息
    Promise* Request(const char* route, const char* data, size_t len);
    /// 向worker发送request消息
    Promise* Request(const char* route, protobuf::Reflect& proto);
    /// 向worker发送request消息
    Promise* Request(const char* route, google::protobuf::Message* message);
    /// 向worker发送request消息
    int Request(lua_State* L);//tolua_export
    /// 向worker发送request消息
    Promise* Request(worker_packet* packet);

    /// 向worker发送notify消息
    int Notify(const char* route, Argument& argv);
    /// 向worker发送notify消息
    int Notify(const char* route, const char* data);
    /// 向worker发送notify消息
    int Notify(const char* route, const char* data, size_t len);
    /// 向worker发送notify消息
    int Notify(const char* route, protobuf::Reflect& proto);
    /// 向worker发送notify消息
    int Notify(const char* route, google::protobuf::Message* message);
    /// 向worker发送notify消息
    int Notify(lua_State* L);//tolua_export
    /// 向worker发送notify消息
    int Notify(worker_packet* packet);
    int notify(worker_packet* packet, Coord* slave);

    int Broadcast(const char* route, Argument& argv);
public:
    void onDestory();
    int start(const char* configFile, uint16_t workerNum);
    void recvWorkerResult(Result* result);
    void sendWorkerPacket(worker_packet* packet, worker::Request* request);
    void sendWorkerPacket(worker_packet* packet);
    void recvWorkerPacket(worker_packet* packet);
    void recvSlaveAwake();
    void recvSlaveError(Coord* slave);
    void checkWorkerRequest();
    void onReload();
public:
    Coord*                              coord;
    std::map<uv_thread_t*, Coord*>      slaveDict;
    std::vector<Coord*>                 slaveArr;
    std::deque<Coord*>                  slaveDeque; //工作线程队列
    WorkerConfig                        config;
    uv_mutex_t                          slaveMutex; //slaveArr slaveDict
    uv_mutex_t                          mutex;      //resultArr
    std::map<uint64_t, Promise*>  promiseDict;
    uint64_t                            requestId;
    uv_sem_t*                           sem;        //启动slave时用的信号量
    std::deque<worker_packet*>          resultArr;
    std::deque<worker_packet*>          packetArr;
    uv_async_t                          async;
    
};//tolua_export

Worker* newWorker(Coord* coord);
}//tolua_export
}//tolua_export


