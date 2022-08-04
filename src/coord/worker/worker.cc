#include "coord/worker/worker.h"
#include "coord/worker/worker_slave.h"
#include "coord/worker/worker_promise.h"
#include "coord/worker/worker_request.h"
#include "coord/worker/worker_result.h"
#include "coord/worker/worker_response.h"
#include "coord/worker/worker_packet.h"
#include "coord/config/config.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"


namespace coord {
namespace worker {
CC_IMPLEMENT(Worker, "coord::worker::Worker")

class worker_data {
public:
    worker_data() {
        this->thread = nullptr;
        this->worker = nullptr;
        this->coord = nullptr;
    }
    ~worker_data() {
        if (nullptr != this->thread) {
            free(this->thread);
            this->thread = nullptr;
        }
    }
public:
    std::string     configPath;
    Worker*         worker;
    Coord*          coord;
    uv_thread_t*    thread;
    int             index;
};

static void coord_worker_thread(void* arg) {
    worker_data* workerData = (worker_data*)arg;
    Worker* master = workerData->worker;
    uv_thread_t* thread = workerData->thread;
    coord::Coord* coordb = coord::NewCoord();
    uv_mutex_lock(&master->slaveMutex);
    master->slaveArr.push_back(coordb);
    master->slaveDict[thread] = coordb;
    //master->slaveDeque.push_front(coordb);
    uv_mutex_unlock(&master->slaveMutex);
    int err = coordb->workerEntryPoint(master, workerData->configPath, workerData->index);
    if(err){
        //master->coord->CoreLogError("coord_worker_thread failed, error=%d", err);
        master->recvSlaveError(coordb);
    }
    delete workerData;
    delete coordb;
}

static void uv_async_cb(uv_async_t *handle) {
    Worker* worker = (Worker*)handle->data;
    worker->checkWorkerRequest();
}

Worker* newWorker(Coord* coord) {
    Worker* self = new Worker(coord);
    return self;
}

Worker::Worker(Coord *coord) {
    this->coord = coord;
    this->requestId = 0;
    this->sem = (uv_sem_t*)malloc(sizeof(uv_sem_t));
    uv_mutex_init(&this->slaveMutex);
    uv_mutex_init(&this->mutex);
}

Worker::~Worker() {
    this->coord->CoreLogDebug("[Worker] ~Worker");
    uv_mutex_destroy(&this->slaveMutex);
    uv_mutex_destroy(&this->mutex);
    if (this->sem) {
        uv_sem_destroy(this->sem);
        free(this->sem);
        this->sem = NULL;
    }
}

void Worker::onDestory() {
    this->coord->CoreLogDebug("[Worker] onDestory, slave=%d", this->slaveDict.size());
    //等级slave结束
    for(auto const it : this->slaveDict){
        
        Coord* slave = it.second;
        slave->Destory(0);
        uv_thread_t* thread = it.first;
        uv_thread_join(thread);
    }
}

//启动工作线程失败
void Worker::recvSlaveError(Coord* slave) {
    this->coord->CoreLogDebug("[Worker] recvSlaveError");
    uv_mutex_lock(&this->slaveMutex);
    for(auto it = this->slaveArr.begin(); it != this->slaveArr.end(); ++it) {
        if (*it == slave) {
            this->slaveArr.erase(it);
            break;
        }
    }
    for(auto it = this->slaveDict.begin(); it != this->slaveDict.end(); ++it) {
        if (it->second == slave) {
            this->slaveDict.erase(it);
            break;
        }
    }
   /* for(auto it = this->slaveDeque.begin(); it != this->slaveDeque.end(); ++it) {
        if (*it == slave) {
            this->slaveDeque.erase(it);
            break;
        }
    }*/
    uv_mutex_unlock(&this->slaveMutex);
    uv_sem_post(this->sem);
}

//收到slave启动完成通知
void Worker::recvSlaveAwake() {
    this->coord->CoreLogDebug("[Worker] recvSlaveAwake");
    uv_sem_post(this->sem);
}

int Worker::start(const std::string& configPath, uint16_t workerNum) {
    this->coord->CoreLogDebug("[Worker] Start, config=%s, worker_num=%d", configPath.c_str(), workerNum);
    int err = uv_async_init(&this->coord->loop, &this->async, uv_async_cb);
    if (err) {
        this->coord->CoreLogError("[Worker] start failed, error=%d", err);
        return err;
    }
    this->async.data = this;
    err = uv_sem_init(this->sem, 0);
    if (err) {
        return err;
    }
    for (int i = 0; i < workerNum; i++) {
        uv_thread_t* thread = (uv_thread_t*)malloc(sizeof(uv_thread_t));
        worker_data* workerData = new worker_data();
        workerData->configPath= configPath;
        workerData->worker = this;
        workerData->thread = thread;
        workerData->index = i + 1;
        int err = uv_thread_create(thread, coord_worker_thread, workerData);
        if (err) {
            this->coord->CoreLogError("[Worker] start failed, error=%d", err);
            delete workerData;
            return err;
        }
    }
    //等待slave启动
    int waitSlaveNum = workerNum;
    while(waitSlaveNum > 0) {
        uv_sem_wait(this->sem);
        waitSlaveNum--;
    }
    uv_sem_destroy(this->sem);
    free(this->sem);
    this->sem = NULL;
    this->coord->CoreLogDebug("[Worker] start, slave=%d", this->slaveArr.size());
    if (this->slaveArr.size() != workerNum) {
        this->coord->CoreLogError("[Worker] start failed, succ=%d, err=%d", this->slaveArr.size(), workerNum - this->slaveArr.size());
        return -1;
    }
    return 0;
}

Promise* Worker::Request(const char* route, const char* data) {
    return this->Request(route, data, strlen(data));
}

Promise* Worker::Request(const char* route, const char* data, size_t len) {
    auto packet = newWorkerPacket(this->coord);
    //Request* request = newRequest(this->coord, this);
    packet->route = route;
    coord::Append(packet->payload, data, len);
    return this->Request(packet);
}

Promise* Worker::Request(const char* route, Argument& argv) {
    auto packet = newWorkerPacket(this->coord);
    packet->route = route;
    argv.Serialize(packet->payload);
    return this->Request(packet);
}

Promise* Worker::Request(const char* route, protobuf::Reflect& proto) {
    return this->Request(route, proto.GetMessage());
}

Promise* Worker::Request(const char* route, google::protobuf::Message* proto) {
    auto packet = newWorkerPacket(this->coord);
    packet->route = route;
    int err = protobuf::Serialize(packet->payload, proto);
    if(err) {
        return NULL;
    }
    return this->Request(packet);
}

int Worker::Request(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isstring(L,2,0,&tolua_err)
    )
        goto tolua_lerror;
    else {
        const char* route = ((const char*)  tolua_tostring(L, 2, 0));
        Argument argv(this->coord);
        int err = argv.pack(L, 3);
        if (err) {
            return 0;
        }
        Promise* tolua_ret = (Promise*)  this->Request(route, argv);
        tolua_pushusertype(L,(void*)tolua_ret,"coord::worker::Promise");
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Request'.",&tolua_err);
    return 0;
}

Promise* Worker::Request(worker_packet* packet) {
    //修改request
    int requestId = ++this->requestId;
    packet->id = requestId;
    packet->type = worker_packet_request;
    //申请promise
    Promise* promise = new worker::Promise(this->coord);
    promise->route = packet->route;
    this->promiseDict[requestId] = promise;
    //分配slave
    int index = (this->slaveArr.size() == 1) ? (0) : (rand() % (this->slaveArr.size() - 1));
    Coord* slave = this->slaveArr[index];
    int err = slave->WorkerSlave->sendWorkerPacket(packet);
    if (err) {
        this->promiseDict.erase(requestId);
        this->coord->Destory(promise);
        return NULL;
    }
    return promise;
}

int Worker::Notify(const char* route, const char* data) {
    return this->Notify(route, data, strlen(data));
}

int Worker::Notify(const char* route, const char* data, size_t len) {
    auto packet = newWorkerPacket(this->coord);
    packet->route = route;
    coord::Append(packet->payload, data, len);
    return this->Notify(packet);
}

int Worker::Notify(const char* route, Argument& argv) {
    auto packet = newWorkerPacket(this->coord);
    packet->route = route;
    argv.Serialize(packet->payload);
    return this->Notify(packet);
}

int Worker::Notify(const char* route, protobuf::Reflect& proto) {
    return this->Notify(route, proto.GetMessage());
}

int Worker::Notify(const char* route, google::protobuf::Message* proto) {
    auto packet = newWorkerPacket(this->coord);
    packet->route = route;
    int err = protobuf::Serialize(packet->payload, proto);
    if(err) {
        return 0;
    }
    return this->Notify(packet);
}

int Worker::Notify(lua_State* L) {
    tolua_Error tolua_err;
    if (
        !tolua_isstring(L,2,0,&tolua_err)
    )
        goto tolua_lerror;
    else {
        const char* route = ((const char*)  tolua_tostring(L, 2, 0));
        Argument argv(this->coord);
        int err = argv.pack(L, 3);
        if (err) {
            lua_pushnumber(L, err);   
            return 1;
        }
        err = this->Notify(route, argv);
        lua_pushnumber(L, err);        
    }
    return 1;
    tolua_lerror:
    tolua_error(L,"#ferror in function 'Notify'.",&tolua_err);
    return 0;
}

int Worker::Notify(worker_packet* packet) {
    int index = (this->slaveArr.size() == 1) ? (0) : (rand() % (this->slaveArr.size() - 1));
    Coord* slave = this->slaveArr[index];
    return this->notify(packet, slave);
}

int Worker::notify(worker_packet* packet, Coord* slave) {
    packet->type = worker_packet_notify;
    int err = slave->WorkerSlave->sendWorkerPacket(packet);
    if (err) {
        return err;
    }
    return 0;
}

int Worker::Broadcast(const char* route, Argument& argv) {
    int succ = 0;
    for(size_t i = 0; i < this->slaveArr.size(); i++) {
        Coord* slave = this->slaveArr[i];
        auto packet = newWorkerPacket(this->coord);
        packet->route = route;
        argv.Serialize(packet->payload);
        int err = this->notify(packet, slave);
        if (!err) {
            succ = succ + 1;
        }
    }
    return succ;
}

//运行在主线程中
void Worker::checkWorkerRequest() {
    //this->coord->CoreLogDebug("[WorkerSlave] checkWorkerRequest");
    //处理result
    while(true) {
        uv_mutex_lock(&this->mutex);
        if (this->resultArr.size() <= 0) {
            uv_mutex_unlock(&this->mutex);
            break;
        }
        worker_packet* packet = this->resultArr.back();
        this->resultArr.pop_back();
        uv_mutex_unlock(&this->mutex);
        this->recvWorkerPacket(packet);
    }
    //处理packet
    /*if (this->packetArr.size() > 0 && this->slaveDeque.size() > 0) {
        worker_packet* packet = this->packetArr.back();
        this->packetArr.pop_back();
        Coord* slave = this->slaveDeque.back();
        this->slaveDeque.pop_back();
        int err = slave->workerSlave->sendWorkerPacket(packet);
        if (err) {
            this->slaveDeque.push_front(slave);
        }
    }*/
}

//slave发送回复给主线程， 运行在工作线程中
void Worker::sendWorkerPacket(worker_packet* packet, worker::Request* request) {
    //this->coord->CoreLogDebug("[Worker] sendWorkerRequest");
    //拷贝结果到packet中
    auto response = request->GetResponse();
    response->Flush();
    packet->type = worker_packet_response;
    packet->id = request->Id;
    packet->code = response->Code;
    packet->payload = response->Payload;
    uv_mutex_lock(&this->mutex);
    this->resultArr.push_front(packet);
    uv_mutex_unlock(&this->mutex);
    int err = uv_async_send(&this->async);
    if (err) {
        this->coord->CoreLogError("[Worker] sendWorkerRequest failed, error=%d", err);
    }
}

//slave发送回复给主线程， 运行在工作线程中
void Worker::sendWorkerPacket(worker_packet* packet) {
    //this->coord->CoreLogDebug("[Worker] sendWorkerRequest");
    uv_mutex_lock(&this->mutex);
    this->resultArr.push_front(packet);
    uv_mutex_unlock(&this->mutex);
    int err = uv_async_send(&this->async);
    if (err) {
        this->coord->CoreLogError("[Worker] sendWorkerRequest failed, error=%d", err);
    }
}

//收到slave的回复， 运行在主线程中
void Worker::recvWorkerPacket(worker_packet* packet) {
    //this->coord->CoreLogDebug("[Worker] recvWorkerPacket");
    if (packet->type == worker_packet_notify) {
        
    } else if (packet->type == worker_packet_response)  {
        auto result = newResult(this->coord);
        result->Id = packet->id;
        result->Code = packet->code;
        result->payload = packet->payload;
        this->recvWorkerResult(result);
        this->coord->Destory(result);
    } else {
        this->coord->CoreLogError("[Worker] recvWorkerPacket, type=%d, error='type err'", packet->type);
    }
    //释放slave
    //this->slaveDeque.push_front(packet->slave);
    //释放request
    this->coord->Destory(packet);
}

//收到slave的回复， 运行在主线程中
void Worker::recvWorkerResult(Result* result) {
    //this->coord->CoreLogError("[Worker] recvWorkerResult");
    auto it = this->promiseDict.find(result->Id);
    if (it == this->promiseDict.end()) {
        this->coord->CoreLogError("[Worker] recvWorkerResult failed, requestId=%d, error='request not found'", result->Id);
        return ;
    }
    Promise* promise = it->second;
    this->promiseDict.erase(it);
    if (result->Code == 0) {
        promise->resolve(this, result);
    } else {
        promise->reject(this, result);
    }
    this->coord->Destory(promise);
    return;
}

void Worker::onReload() {
    this->coord->CoreLogDebug("[Worker] onReload");
    Argument argv(this->coord);
    this->Broadcast("reload", argv);
}

}        
}
