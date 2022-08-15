#include "coord/gate/gate.h"
#include "coord/gate/gate_packet.h"
#include "coord/gate/gate_message.h"
#include "coord/gate/gate_agent.h"
#include "coord/gate/gate_router.h"
#include "coord/gate/gate_session.h"
#include "coord/gate/gate_cluster.h"
#include "coord/gate/gate_promise.h"
#include "coord/config/config.h"
#include "coord/coord.h"
#include "coord/net/tcp_listener.h"
#include "coord/websocket/websocket_server.h"
#include "coord/websocket/websocket_agent.h"
#include "coord/websocket/websocket_frame.h"
#include "coord/protobuf/init.h"
#include "coord/coordx.h"
#include <fstream>
#include <iostream>
namespace coord {
namespace gate {
CC_IMPLEMENT(Gate, "coord::Gate")

Gate* NewGate(Coord* coord) {
    Gate* gate = new Gate(coord);
    return gate;
}

Gate::Gate(Coord* coord) : coord(coord) {
    this->tcpListener = NULL;
    this->webSocketServer = NULL;
    this->Router = newGateRouter(coord);
    this->status = GateStatus_NIL;
    this->cluster = NULL;
}

Gate::~Gate(){
    this->coord->CoreLogDebug("[Gate] ~Gate");
    delete this->Router;
    this->Router = NULL;
    if(this->webSocketServer) {
        delete this->webSocketServer;
        this->webSocketServer = NULL;
    }
    if(this->tcpListener) {
        delete this->tcpListener;
        this->tcpListener = NULL;
    }
    if(this->cluster) {
        delete this->cluster;
        this->cluster = NULL;
    }
}

GateConfig* Gate::DefaultConfig() {
    return &this->config;
}

void Gate::onDestory() {
    if(this->cluster) {
        this->cluster->onDestory();
    }
}

uint64_t Gate::heartbeatInterval() {
    for(auto const it : this->agentDict){
        GateAgent* agent = it.second;
        agent->heartbeatInterval();
    }
    return 0;
}

uint64_t Gate::agentRegisterInterval() {
    if(!this->cluster) {
        return 0;
    }
    for(auto const it : this->agentDict){
        GateAgent* agent = it.second;
        if (!agent->session->UserId) {
            continue;
        }
        this->cluster->persistAgent(agent->session->UserId);
    }
    return 0;
}

int Gate::main() {
    if (this->status != GateStatus_NIL) {
        this->coord->CoreLogError("[Gate] Start failed, error='gate already running'");
        return -1;
    }
    if (this->config.Network == "tcp") {
        this->address = this->config.ServerName;
    } else if (this->config.Network == "wss") {
        this->address = "wss://"+this->config.ServerName;
    } else if (this->config.Network == "ws") {
        this->address = "ws://"+this->config.ServerName;
    }
    this->coord->CoreLogError("[Gate] Listen, address='%s', host='%s', port=%d", this->address.c_str(), this->config.Host.c_str(), this->config.Port);
    //启动cluster
    if (this->coord->Cluster && this->config.Cluster.length() > 0) {
        this->cluster = newgate_cluster(this->coord, this);
        int err = this->cluster->main();
        if (err) {
            return err;
        }
    }
    //初始化ras key
    if (this->config.RsaEncrypt){
        std::ifstream rsaFile(this->config.RsaKeyFile);
        if(!rsaFile.is_open()){
            this->coord->CoreLogError("[Gate] Start failed, file=%s, error='open rsa file failed'", this->config.RsaKeyFile.c_str());
            return -1;
        }
        this->rsaPrivateKey = std::string((std::istreambuf_iterator<char>(rsaFile)), std::istreambuf_iterator<char>());
        rsaFile.close();
    }
    //侦听tcp or websocket
    if (this->config.Network == "tcp") {
        this->tcpListener = net::NewTcpListener(coord);
        this->tcpListener->SetHandler(this);
        int err = this->tcpListener->Listen(this->config.Host.c_str(), this->config.Port, this->config.Backlog);
        if (err < 0){
            return err;
        }
    } else if (this->config.Network == "wss") {
        websocket::Server* webSocketServer = websocket::newWebSocketServer(coord);
        webSocketServer->SetHandler(this);
        websocket::WebSocketServerConfig* config = webSocketServer->DefaultConfig();
        config->Host = this->config.Host;
        config->Port = this->config.Port;
        config->Backlog = this->config.Backlog;
        config->SSLEncrypt = this->config.SSLEncrypt;
        config->SSLPemFile = this->config.SSLPemFile;
        config->SSLKeyFile = this->config.SSLKeyFile;
        config->RecvBufferSize = this->config.RecvBuffer;
        int err = webSocketServer->Start();
        if (err < 0){
            delete webSocketServer;
            return err;
        }
        this->webSocketServer = webSocketServer;
    } else if (this->config.Network == "ws") {
        websocket::Server* webSocketServer = websocket::newWebSocketServer(coord);
        webSocketServer->SetHandler(this);
        websocket::WebSocketServerConfig* config = webSocketServer->DefaultConfig();
        config->Host = this->config.Host;
        config->Port = this->config.Port;
        config->Backlog = this->config.Backlog;
        config->SSLEncrypt = false;
        config->RecvBufferSize = this->config.RecvBuffer;
        int err = webSocketServer->Start();
        if (err < 0){
            delete webSocketServer;
            return err;
        }
        this->webSocketServer = webSocketServer;
    }
    this->coord->SetInterval(this->config.Heartbeat * 1000, std::bind(&Gate::heartbeatInterval, this));
    //定时注册
    this->coord->SetInterval(this->config.UserRegisterInterval * 1000, std::bind(&Gate::agentRegisterInterval, this));
    return 0;
} 

void Gate::recvTcpNew(net::TcpListener* listener, net::TcpAgent* tcpAgent) {
    uint64_t sessionId = tcpAgent->sessionId;
    this->coord->CoreLogDebug("[Gate] recvTcpNew, sessionId=%ld, remoteAddr=%s", sessionId, tcpAgent->remoteAddr.c_str());
    tcpAgent->SetRecvBuffer(this->config.RecvBuffer);
    GateAgent *agent = newGateAgent(this->coord, this, tcpAgent);
    agent->SessionId = sessionId;
    agent->RemoteAddr = tcpAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
}

void Gate::recvAgentClose(GateAgent* agent){
    this->coord->CoreLogDebug("[Gate] recvAgentClose, sessionId=%ld, ref=%d", agent->SessionId, agent->_ref);
    auto it = this->agentDict.find(agent->SessionId);
    if(it == this->agentDict.end()){
        this->coord->CoreLogDebug("[Gate] recvAgentClose failed, error='agent not found', sessionId=%ld", agent->SessionId);
        return;
    }
    uint64_t userId = agent->session->UserId;
    uint64_t sessionId = agent->SessionId;    
    if (this->cluster && userId) {
        this->cluster->unregisterAgent(sessionId, userId);
    } else {
        this->agentDict.erase(it);
        this->coord->Destory(agent);
    }
}

void Gate::recvWebSocketNew(websocket::Agent* webSocketAgent){
    uint64_t sessionId = webSocketAgent->sessionId;
    this->coord->CoreLogDebug("[Gate] recvWebSocketNew, sessionId=%ld, remoteAddr=%s", sessionId, webSocketAgent->remoteAddr.c_str());
    GateAgent *agent = newGateAgent(this->coord, this, webSocketAgent);
    agent->SessionId = sessionId;
    agent->RemoteAddr = webSocketAgent->remoteAddr;
    this->agentDict[sessionId] = agent;
}

void Gate::recvGateRequest(GateSession* session, GateRequest* request) {
    this->coord->CoreLogDebug("[Gate] recvGateRequest");
    try{ 
        //传递到逻辑层
        this->Router->recvGateRequest(session, request);
    } catch(ScriptException& e){
    }
}

void Gate::recvGateNotify(GateSession* session, GateNotify* notify) {
    this->coord->CoreLogDebug("[Gate] recvGateNotify");
    try{
        //传递到逻辑层
        this->Router->recvGateNotify(session, notify);
    } catch(ScriptException& e){
    }
} 

void Gate::recvGateSessionNew(GateSession* session) {
    this->coord->CoreLogDebug("[Gate] recvGateSessionNew");
    try{ 
        //传递到逻辑层
        this->Router->recvGateSessionNew(session);
    } catch(ScriptException& e){
    }
}

void Gate::recvGateSessionClose(GateSession* session) {
    this->coord->CoreLogDebug("[Gate] recvGateSessionClose");
    try{ 
        //传递到逻辑层
        this->Router->recvGateSessionClose(session);
    } catch(ScriptException& e){
    }
}

void Gate::Kick(uint64_t sessionId, const char* reason) {
    auto it = this->agentDict.find(sessionId);
    if(it == this->agentDict.end()){
        this->coord->CoreLogDebug("[Gate] Kick failed, error=agent not found, sessionId=%ld", sessionId);
        return;
    }
    GateAgent* agent = it->second;
    agent->kick(reason);
}

void Gate::Close() {
    this->status = GateStatus_CLOSED;
}

int Gate::Maintain(bool value) {
    if (value) {
        if( this->status != GateStatus_RUNNING) {
            return - 1;
        }
        this->status = GateStatus_MAINTAIN;
        return 0;
    } else {
         if( this->status != GateStatus_MAINTAIN) {
            return - 1;
        }
        this->status = GateStatus_RUNNING;
        return 0;
    }
}

GatePromise* Gate::login(GateAgent* agent, uint64_t userId) {
    if (this->cluster == NULL) {
        return NULL;
    }
    uint64_t sessionId = agent->SessionId;
    int err = this->cluster->registerAgent(sessionId, userId);
    if (err) {
        return NULL;
    }
    GatePromise* promise = newGatePromise(this->coord);
    this->loginingPromiseDict[sessionId] = promise;
    //promise->pipeline = this->coord->refRequestPipeline();
    return promise;
}

int Gate::Logout(uint64_t userId) {
    //this->Router->recvGateUserLogout(NULL);
    return 0;
}

void Gate::recvUserLogoutSucc(uint64_t sessionId, uint64_t userId) {
    this->coord->CoreLogDebug("[Gate] recvUserLogoutSucc, sessionId=%ld, userId=%ld", sessionId, userId);
    GateAgent* agent = NULL;
    auto it1 = this->agentDict.find(sessionId);
    if (it1 == this->agentDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLogoutSucc failed, sessionId=%ld, uuserId=%ld, error='agent not found'", sessionId, userId);
    } else {
        agent = it1->second;
        this->agentDict.erase(it1);
    }
    auto it2 = this->userDict.find(userId);
    if (it2 == this->userDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLogoutSucc failed, sessionId=%ld, uuserId=%ld, error='user not found'", sessionId, userId);
    } else {
        agent = it1->second;
        this->userDict.erase(it2);
    }
    if (agent) {
        try{ 
        //传递到逻辑层
        this->Router->recvGateUserLogout(agent->session);
        } catch(ScriptException& e){
        }
        this->coord->Destory(agent);
    }
}

void Gate::recvUserLogoutErr(uint64_t sessionId, uint64_t userId) {
    this->coord->CoreLogDebug("[Gate] recvUserLogoutSucc, sessionId=%ld, userId=%ld", sessionId, userId);
    GateAgent* agent = NULL;
    auto it1 = this->agentDict.find(sessionId);
    if (it1 == this->agentDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLogoutSucc failed, sessionId=%ld, uuserId=%ld, error='agent not found'", sessionId, userId);
    } else {
        agent = it1->second;
        this->agentDict.erase(it1);
    }
    auto it2 = this->userDict.find(userId);
    if (it2 == this->userDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLogoutSucc failed, sessionId=%ld, uuserId=%ld, error='user not found'", sessionId, userId);
    } else {
        agent = it2->second;
        this->userDict.erase(it2);
    }
    if (agent) {
        this->coord->Destory(agent);
    }
}

void Gate::recvUserLoginSucc(uint64_t sessionId, uint64_t userId) {
    this->coord->CoreLogDebug("[Gate] recvUserLoginSucc, sessionId=%ld, userId=%ld", sessionId, userId);
    auto it1 = this->loginingPromiseDict.find(sessionId);
    if (it1 == this->loginingPromiseDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLoginSucc failed, sessionId=%ld, userId=%ld, error='login promise not found'", sessionId, userId);
        return;
    }
    GatePromise* promise = it1->second;
    auto it2 = this->agentDict.find(sessionId);
    if (it2 == this->agentDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLoginSucc failed, sessionId=%ld, userId=%ld, error='agent not found'", sessionId, userId);
        this->loginingPromiseDict.erase(it1);
        this->coord->Destory(promise);
        return;
    }
    GateAgent* agent = it2->second;

    auto it3 = this->userDict.find(userId);
    if (it3 != this->userDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLoginSucc failed, sessionId=%ld, userId=%ld, error='other user found'", sessionId, userId);
        this->loginingPromiseDict.erase(it1);   
        promise->reject(agent->session);
        this->coord->Destory(promise);
        return;
    }     
    agent->session->UserId = userId;
    this->userDict[userId] = agent;
    this->loginingPromiseDict.erase(it1);
    //通知登录成功
    promise->resolve(agent->session);
    this->coord->Destory(promise);
    try{ 
        //传递到逻辑层
        this->Router->recvGateUserLogin(agent->session);
    } catch(ScriptException& e){
    }
}

void Gate::recvUserLoginErr(uint64_t sessionId, uint64_t userId) {
    this->coord->CoreLogDebug("[Gate] recvUserLoginErr, sessionId=%ld, userId=%ld", sessionId, userId);
    auto it1 = this->loginingPromiseDict.find(sessionId);
    if (it1 == this->loginingPromiseDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLoginErr failed, sessionId=%ld, userId=%ld, error='login promise not found'", sessionId, userId);
        return;
    }
    GatePromise* promise = it1->second;
    auto it2 = this->agentDict.find(sessionId);
    if (it2 == this->agentDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserLoginErr failed, sessionId=%ld, userId=%ld, error='agent not found'", sessionId, userId);
        this->loginingPromiseDict.erase(it1);
        this->coord->Destory(promise);
        return;
    }
    GateAgent* agent = it2->second;
    this->loginingPromiseDict.erase(it1);
    //通知登录失败
    promise->reject(agent->session);
    this->coord->Destory(promise); 
}

void Gate::recvUserInstead(uint64_t userId) {
    this->coord->CoreLogDebug("[Gate] recvUserInstead, userId=%ld", userId);
    auto it = this->userDict.find(userId);
    if (it == this->userDict.end()) {
        this->coord->CoreLogError("[Gate] recvUserInstead failed, userId=%ld, error='agent not found'", userId);
        return;
    }
    GateAgent* agent = it->second;
    try{ 
        //传递到逻辑层
        this->Router->recvGateUserInstead(agent->session);
    } catch(ScriptException& e){
    }
    agent->kick("账号在其他地方登录");
    agent->close();
}

int Gate::GetOnlineNum() {
    return this->userDict.size();
}

}}  
