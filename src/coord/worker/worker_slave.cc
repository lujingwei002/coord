#include "coord/worker/worker_slave.h"
#include "coord/worker/worker.h"
#include "coord/net/tcp_listener.h"
#include "coord/config/config.h"
#include "coord/coord.h"
#include "coord/worker/worker_router.h"
#include "coord/worker/worker_response.h"
#include "coord/worker/worker_request.h"
#include "coord/worker/worker_packet.h"
#include "coord/worker/worker_notify.h"
#include "coord/builtin/exception.h"
namespace coord {
namespace worker {
    
WorkerSlave* newWorkerSlave(Coord* coord, Worker* worker) {
    WorkerSlave* self = new WorkerSlave(coord, worker);
    return self;
}

static void uv_async_cb(uv_async_t *handle) {
    //printf("uv_async_cb\n");
    WorkerSlave* slave = (WorkerSlave*)handle->data;
    slave->checkWorkerRequest();
}

WorkerSlave::WorkerSlave(Coord *coord, Worker* worker) {
    this->coord = coord;
    this->worker = worker;
    this->Router = newWorkerRouter(this->coord);
    uv_mutex_init(&this->mutex);
}

WorkerSlave::~WorkerSlave() {
    if(this->Router) {
        delete this->Router;
        this->Router = NULL;
    }
    uv_mutex_destroy(&this->mutex);
}

int WorkerSlave::start() {
    //this->coord->CoreLogDebug("[WorkerSlave] start");
    int err = uv_async_init(&this->coord->loop, &this->async, uv_async_cb);
    if (err) {
        this->coord->CoreLogError("[WorkerSlave] start failed, error=%d", err);
    }
    this->async.data = this;
    this->coord->SetInterval(500, std::bind(&WorkerSlave::onIdle, this));
    return 0;
}

uint64_t WorkerSlave::onIdle() {
    return 0;
}

void WorkerSlave::onReload() {
    this->coord->Reload();
}

//检查request队列, 运行在工作线程中
void WorkerSlave::checkWorkerRequest() {
    //this->coord->CoreLogDebug("[WorkerSlave] checkWorkerRequest");
    while(true) {
        uv_mutex_lock(&this->mutex);
        if (this->packetArr.size() <= 0) {
            uv_mutex_unlock(&this->mutex);
            break;
        }
        worker_packet* packet = this->packetArr.back();
        this->packetArr.pop_back();
        uv_mutex_unlock(&this->mutex);
        if (packet->type == worker_packet_request) {
            auto request = newRequest(this->coord);
            request->Id = packet->id;
            request->Route = packet->route;
            request->payload = packet->payload;
            this->recvWorkerRequest(packet, request);
            this->coord->Destory(request);
        } else if (packet->type == worker_packet_notify) {
            auto notify = newNotify(this->coord);
            notify->Route = packet->route;
            notify->payload = packet->payload;
            this->recvWorkerNotify(packet, notify);
            this->coord->Destory(notify);
        }
    }
}

//slave处理request, 运行在工作线程中
void WorkerSlave::recvWorkerRequest(worker_packet* packet, Request* request){
    //this->coord->CoreLogDebug("[WorkerSlave] recvWorkerRequest");
    try{
        //传递到逻辑层
        this->Router->recvWorkerRequest(request);
    } catch(ScriptException& e){
        Response* response = request->GetResponse();
        response->String(e.What());
        response->Reject(500);
    }
    packet->coord->Worker->sendWorkerPacket(packet, request);
}

//slave处理request, 运行在工作线程中
void WorkerSlave::recvWorkerNotify(worker_packet* packet, Notify* notify){
    //this->coord->CoreLogDebug("[WorkerSlave] recvWorkerNotify");
    try{
        if (strcmp(notify->Route.c_str(), "reload") == 0) {
            this->coord->Reload();
        } else {
            //传递到逻辑层
            this->Router->recvWorkerNotify(notify);
        }
    } catch(ScriptException& e){
        
    }
    packet->coord->Worker->sendWorkerPacket(packet);
}

//主线程发送请求到slave, 运行在主线程中
int WorkerSlave::sendWorkerPacket(worker_packet* packet) {
    //this->coord->CoreLogDebug("[WorkerSlave] sendWorkerPacket");
    packet->slave = this->coord;
    uv_mutex_lock(&this->mutex);
    this->packetArr.push_front(packet);
    uv_mutex_unlock(&this->mutex);
    int err = uv_async_send(&this->async);
    if (err) {
        return err;
    }
    return 0;
}


}        
}