#pragma once 

#include "coord/coordx.h"
#include <vector>
#include <iostream>
#include <map>
#include <deque>
#include <uv.h>

namespace coord {//tolua_export
    
class Coord;
namespace worker {//tolua_export
class Worker;
class Request;
class WorkerRouter;
class Request;
class Notify;
class worker_packet;
class WorkerSlave {//tolua_export
public:
    WorkerSlave(Coord *coord, Worker* worker);
    virtual ~WorkerSlave();
public:
    int         start();
    void        recvWorkerRequest(worker_packet* packet, Request* request);
    void        recvWorkerNotify(worker_packet* packet, Notify* notify);
    int         sendWorkerPacket(worker_packet* packet);
    void        checkWorkerRequest();
    uint64_t    onIdle();
    void        onReload();
public:
    WorkerRouter*               Router;                 //tolua_export
public:
    Coord*                      coord;
    Worker*                     worker;
    uv_async_t                  async;
    uv_mutex_t                  mutex;                  //requestArry
    std::deque<worker_packet*>  packetArr;
};//tolua_export

WorkerSlave* newWorkerSlave(Coord* coord, Worker* worker);

}//tolua_export
}//tolua_export


