#pragma once 

#include "coord/coordx.h"
#include "coord/memory/type.h"
#include "coord/argument/argument.h"
#include "coord/base/base_packet.h"
#include "coord/protobuf/init.h"
#include "proto/coord.pb.h"
#include "coord/base/base_message.h"
#include <google/protobuf/message.h>
#include "coord/coord.h"
#include <vector>
#include <iostream>
#include <map>
#include <google/protobuf/message.h>
namespace coord {//tolua_export

class Coord;

enum base_client_status {
	base_client_status_nil = 0,
    base_client_status_connecting = 1,
    base_client_status_connnected = 2,
	base_client_status_handshake = 3,
	base_client_status_working = 4,
    base_client_status_closing = 5,
	base_client_status_closed = 6,
};

template<typename TRequestPromise>
class base_client : public coord::RcObject, public coord::Reflectable {//tolua_export
public:
    base_client(Coord *coord);
    virtual ~base_client();
public:
    virtual int Send(byte_slice& packet) = 0;
protected:
    int notify(const std::string& route, const char* data, size_t len);
    TRequestPromise* request(const std::string& route, Argument* argument);
    TRequestPromise* request(const std::string& route, const char* data, size_t len);
    TRequestPromise* request(const std::string& route, google::protobuf::Message* proto);
    int sendPacket(base_packet_type type, ::google::protobuf::Message* message);
    int sendPacket(base_packet_type type, const char* data, size_t len);
protected:
    Coord*                              coord;
    int                                 requestId;
    std::map<int, TRequestPromise*>     promiseDict;
};//tolua_export

template<typename TRequestPromise>
base_client<TRequestPromise>::base_client(Coord *coord) {
    this->coord = coord;
    this->requestId = 0;
}

template<typename TRequestPromise>
base_client<TRequestPromise>::~base_client() {
}

template<typename TRequestPromise>
int base_client<TRequestPromise>::notify(const std::string& route, const char* data, size_t len) {
    this->coord->CoreLogError("[%s] notify, route=%s", this->TypeName(), route);
    byte_slice packet;
    int err = base_notify_encode(packet, route.c_str(), data, len);
    if (err < 0){
        return err;
    } 
    return this->Send(packet);
}

template<typename TRequestPromise>
TRequestPromise* base_client<TRequestPromise>::request(const std::string& route, Argument* argument) {
    this->coord->CoreLogDebug("[%s] %s, route=%s", this->TypeName(), __FUNCTION__, route.c_str());
    int requestId = ++this->requestId;
    byte_slice packet;
    int err = base_request_encode(packet, route.c_str(), requestId, argument);
    if (err) {
        this->coord->CoreLogError("[%s] %s fail1, route=%s, error=%d", this->TypeName(), __FUNCTION__, route.c_str(), err);
        return nullptr;
    }
    err =  this->Send(packet);
    if (err) {
        this->coord->CoreLogError("[%s] request fail2, route=%s, error=%d", this->TypeName(), route.c_str(), err);
        return nullptr;
    }
    TRequestPromise* promise = new TRequestPromise(this->coord);
    promise->route = route;
    this->promiseDict[requestId] = promise;
    return promise;
}

template<typename TRequestPromise>
TRequestPromise* base_client<TRequestPromise>::request(const std::string& route, const char* data, size_t len) {
    this->coord->CoreLogDebug("[%s] request, route=%s", this->TypeName(), route);
    int requestId = ++this->requestId;
    byte_slice packet;
    int err = base_request_encode(packet, route.c_str(), requestId, data, len);
    if (err) {
        this->coord->CoreLogError("[%s] %s fail1, route=%s, error=%d", this->TypeName(), __FUNCTION__, route.c_str(), err);
        return nullptr;
    }
    err =  this->Send(packet);
    if (err < 0) {
        return nullptr;
    }
    TRequestPromise* promise = new TRequestPromise(this->coord);
    promise->route = route;
    this->promiseDict[requestId] = promise;
    return promise;
}

template<typename TRequestPromise>
TRequestPromise* base_client<TRequestPromise>::request(const std::string& route, google::protobuf::Message* proto) {
    this->coord->CoreLogDebug("[%s] request, route=%s", this->TypeName(), route);
    int requestId = ++this->requestId;
    byte_slice packet;
    int err = base_request_encode(packet, route.c_str(), requestId, proto);
    if (err) {
        this->coord->CoreLogError("[%s] request fail, route=%s, error=%d", this->TypeName(), route.c_str(), err);
        return nullptr;
    }
    err =  this->Send(packet);
    if (err < 0) {
        return nullptr;
    }
    TRequestPromise* promise = new TRequestPromise(this->coord);
    promise->route = route;
    this->promiseDict[requestId] = promise;
    return promise;
}

template<typename TRequestPromise>
int base_client<TRequestPromise>::sendPacket(base_packet_type type, ::google::protobuf::Message* message) {
    byte_slice packet;
    int err = base_packet_encode(packet, type, message);
    if (err < 0){
        return err;
    } 
    return this->Send(packet);
}

template<typename TRequestPromise>
int base_client<TRequestPromise>::sendPacket(base_packet_type type, const char* data, size_t len) {
    static thread_local byte_slice packet;
    int err = base_packet_encode(packet, type, data, len);
    if (err < 0){
        this->coord->CoreLogDebug("[base_client] Send failed, err=%d", err);
        return err;
    }
    return this->Send(packet);
}

}//tolua_export


