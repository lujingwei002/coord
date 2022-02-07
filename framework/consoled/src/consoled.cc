#include "consoled.h"
#include "consoled/consoled_server.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace consoled {

CC_IMPLEMENT(Consoled, "consoled::Consoled")

Consoled* NewConsoled() {
    Consoled* self = new Consoled(coorda);
    return self;
}

Consoled::Consoled(coord::Coord *coord) {
    this->coord = coord;
    this->server = nullptr;
}

Consoled::~Consoled() {
    if(this->server) {
        delete this->server;
        this->server = nullptr;
    }
}

void Consoled::onAwake() {
    this->coord->LogDebug("[Consoled] Awake");
    int err = 0; 
    err = this->readConfig();
    if (err < 0){
        this->coord->LogDebug("[Consoled] Awake failed, error=%d", err);
        return;
    }
    //启动server
    this->server = newConsoledServer(this->coord, this);
    err = this->server->start();
    if (err < 0){
        this->coord->LogDebug("[Consoled] Awake failed, error=%d", err);
        return;
    } 
}

int Consoled::readConfig() {
    ConsoledConfig* config = &this->config;
    if(!this->coord->config->Get("Consoled", "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!this->coord->config->Get("Consoled", "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!this->coord->config->Get("Consoled", "user", config->User)) {
        return ErrorConfigNotExist;
    }
    if(!this->coord->config->Get("Consoled", "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

ConsoledConfig* Consoled::DefaultConfig() {
    return &this->config;
}



}
      