#include "coord/base/internal_agent.h"
#include "coord/coord.h"
namespace coord {

RC_IMPLEMENT(internal_agent, "coord::internal_agent")


internal_agent::internal_agent(Coord *coord) : base_agent(coord) {
}

internal_agent::~internal_agent() {
}

int internal_agent::Notify(const std::string& route, byte_slice& data) {
    return this->Notify(route, data.Data(), data.Len());
}

int internal_agent::Notify(const std::string& route, const char* data, size_t len) {
    this->coord->CoreLogDebug("[%s] Notify, sessionId=%d, route=%d, len=%d", this->TypeName(), this->SessionId, route.c_str(), len);
    byte_slice packet;
    int err = base_notify_encode(packet, route.c_str(), data, len);
    if (err){
        return err;
    } 
    this->send(packet);
    return 0; 
}

int internal_agent::Notify(const std::string& route, protobuf::MessageRef& proto) {
    return this->Notify(route, proto->GetMessage());
}

int internal_agent::Notify(const std::string& route, ::google::protobuf::Message* proto) {
    this->coord->CoreLogError("[%s] Notify, sessionId=%d, route=%d", this->TypeName(), this->SessionId, route.c_str());
    byte_slice packet;
    int err = base_notify_encode(packet, route.c_str(), proto);
    if (err < 0){
        return err;
    } 
    this->send(packet);
    return 0; 
}

int internal_agent::Response(uint64_t id, int code, byte_slice& data) {
    return this->Response(id, code, data.Data(), data.Len());
}

int internal_agent::Response(uint64_t id, int code, const char* data, size_t len) {
    this->coord->CoreLogDebug("[%s] Response, sessionId=%d, id=%d, len=%d", this->TypeName(), this->SessionId, id, len);
    byte_slice packet;
    int err = base_response_encode(packet, id, code, data, len);
    if (err < 0){
        return err;
    } 
    return this->send(packet);
}

int internal_agent::Response(uint64_t id, int code, protobuf::MessageRef& proto) {
    return this->Response(id, code, proto->GetMessage());
}

int internal_agent::Response(uint64_t id, int code, ::google::protobuf::Message* proto) {
    this->coord->CoreLogError("[%s] Response, sessionId=%d, id=%d", this->TypeName(), this->SessionId, id);
    byte_slice packet;
    int err = base_response_encode(packet, id, code, proto);
    if (err < 0){
        return err;
    } 
    return this->send(packet);
}

int internal_agent::Response(uint64_t id, int code, Argument* argument) {
    this->coord->CoreLogError("[%s] Response, sessionId=%d, id=%d", this->TypeName(), this->SessionId, id);
    byte_slice packet;
    int err = base_response_encode(packet, id, code, argument);
    if (err < 0){
        return err;
    } 
    return this->send(packet);
}

int internal_agent::SendPacket(base_packet_type type, ::google::protobuf::Message* message) {
    byte_slice packet;
    int err = base_packet_encode(packet, type, message);
    if (err < 0){
        return err;
    } 
    return this->send(packet);
}


}  
