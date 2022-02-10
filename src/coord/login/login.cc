#include "coord/login/login.h"
#include "coord/login/account_controller.h"
#include "coord/login/login_cluster.h"
#include "coord/http/init.h"
#include "coord/coord.h"

namespace coord {
namespace login {

LoginSvr* newLoginSvr(Coord* coord) {
    LoginSvr* self = new LoginSvr(coord);
    return self;
}

LoginSvr::LoginSvr(Coord* coord) {
    this->coord = coord;
    this->httpServer = nullptr;
    this->accountController = nullptr;
    this->loginCluster = nullptr;
}

LoginSvr::~LoginSvr() {
    if (this->httpServer) {
        delete this->httpServer;
        this->httpServer = nullptr;
    }
    if (this->accountController) {
        delete this->accountController;
        this->accountController = nullptr;
    }
    if (this->loginCluster) {
        delete this->loginCluster;
        this->loginCluster = nullptr;
    }
}

int LoginSvr::main() {
    this->httpServer = http::newHttpServer(this->coord);
    http::HttpServerConfig* config = this->httpServer->DefaultConfig();
    config->Host = this->config.Host;
    config->Port = this->config.Port;
    config->Backlog = this->config.Backlog;
    config->RecvBufferSize = this->config.RecvBufferSize;
    config->SSLEncrypt = this->config.SSLEncrypt;
    config->SSLPemFile = this->config.SSLPemFile;
    config->SSLKeyFile = this->config.SSLKeyFile;
    config->UseEtag = false;
    int err = this->httpServer->Start();
    if (err) {
        return err;
    }
    this->loginCluster = newLoginCluster(this->coord, this);
    err = this->loginCluster->main();
    if (err) { 
        return err;
    }
    this->accountController = newAccountController(this->coord, this);
    err = this->accountController->main();
    if (err) { 
        return err;
    }
    this->coord->coreLogError("[LoginSvr] main, host='%s', port=%d, cluster='%s'", this->config.Host.c_str(), this->config.Port, this->config.Cluster.c_str());
    return 0;
} 

void LoginSvr::onDestory() {

}

LoginConfig* LoginSvr::DefaultConfig() {
    return &this->config;
}

}
}