#include "coord/managed/managed.h"
#include "coord/managed/managed_server.h"
#include "coord/managed/managed_router.h"
#include "coord/managed/managed_client.h"
#include "coord/managed/managed_notify.h"
#include "coord/managed/managed_response.h"
#include "coord/managed/managed_request.h"
#include "coord/config/config.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"

namespace coord {
namespace managed {

CC_IMPLEMENT(Managed, "coord::managed::Managed")

Managed::Managed(Coord *coord) {
    this->coord = coord;
    this->server = nullptr;
    this->Router = nullptr;
}

Managed::~Managed() {
    if(this->server) {
        delete this->server;
        this->server = nullptr;
    }
    if(this->Router) {
        delete this->Router;
        this->Router = nullptr;
    }
}

int Managed::Close() {
    if (nullptr == this->server) {
        return ErrorInvalidStatus;
    } 
    return this->server->close();
}

ManagedClient* Managed::NewClient(const std::string& path) {
    auto client = new ManagedClient(this->coord, this, path, 1);
    return client;
}

void Managed::recvRequest_stop(ManagedRequest* request) {
    this->coord->Destory(0);
    auto response = request->GetResponse();
    response->Args()->AddString("Ok");
}

void Managed::recvRequest_status(ManagedRequest* request) {
    auto argument = request->Args();
    argument->DebugPrint();
    auto response = request->GetResponse();
    response->Args()->AddString("alive");
}

int Managed::main() {
    int err = 0; 
    //启动server
    this->server = new managed_server(this->coord, this);
    err = this->server->start();
    if (err < 0){
        return err;
    } 
    this->Router = new ManagedRouter(this->coord, this);
    this->Router->Request("status", std::bind(&Managed::recvRequest_status, this, std::placeholders::_1));
    this->Router->Request("stop", std::bind(&Managed::recvRequest_stop, this, std::placeholders::_1));
    return 0;
}

void Managed::recvRequest(ManagedRequest* request) {
    this->coord->CoreLogDebug("[%s] recvRequest", this->TypeName());
    try{
        //传递到逻辑层
        this->Router->recvRequest(request);
    } catch(ScriptException& e){
        //Response* response = request->GetResponse();
        //response->String(e.What());
        //response->Reject(500);
    }
}

void Managed::recvNotify(ManagedNotify* notify) {
    this->coord->CoreLogDebug("[%s] recvNotify", this->TypeName());
    try{
        //传递到逻辑层
        this->Router->recvNotify(notify);
    } catch(ScriptException& e){
    }
}


}
}        

