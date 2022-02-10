#include "coord/managed/managed.h"
#include "coord/managed/managed_server.h"
#include "coord/config/config.h"
#include "coord/builtin/exception.h"
#include "coord/coord.h"

namespace coord {
namespace managed {

CC_IMPLEMENT(Managed, "coord::managed::Managed")

Managed* newManaged(Coord* coord) {
    auto self = new Managed(coord);
    return self;
}

Managed::Managed(Coord *coord) {
    this->coord = coord;
    this->server = NULL;
}

Managed::~Managed() {
    if(this->server) {
        delete this->server;
        this->server = NULL;
    }
}

int Managed::start() {
    this->coord->coreLogDebug("[Managed] Start");
    int err = 0; 
    //启动server
    this->server = newManagedServer(this->coord, this);
    err = this->server->start();
    if (err < 0){
        return err;
    } 
    return 0;
}



ManagedConfig* Managed::DefaultConfig() {
    return &this->config;
}



}
}        