#include "coord/builtin/base_request.h"
#include "coord/builtin/base_response.h"
#include "coord/json/json_mgr.h"
#include "coord/coord.h"
namespace coord {
CC_IMPLEMENT(BaseRequest, "coord::BaseRequest")

BaseRequest::BaseRequest(Coord* coord) : proto(coord), table(coord){
    this->coord = coord;
    this->reqTime = uv_hrtime();
    this->argv = NULL;
    this->type = response_type_none;
}

BaseRequest::~BaseRequest() {
    if(this->argv != NULL) {
        delete this->argv;
        this->argv = NULL;
    }
}

int BaseRequest::Proto(google::protobuf::Message& message) {
    return protobuf::ParseFrom(this->payload, &message);
}

protobuf::Reflect& BaseRequest::Proto(const char* name){
    static thread_local protobuf::Reflect nullPtr(this->coord);

    if (this->proto != nullptr) {
        return this->proto;
    }
    auto proto = this->coord->Proto->NewReflect(name);
    if (proto == nullptr) {
        return nullPtr;
    }
    int err = proto.ParseFrom(this->payload);
    if (err) {
        return nullPtr;
    }
    this->proto = proto;
    return this->proto;
}

const char* BaseRequest::String() {
    return this->payload.Data();
}

size_t BaseRequest::Len(){
    return this->payload.Len();
}

int BaseRequest::String(lua_State* L){
    lua_pushlstring(L, this->payload.Data(), this->payload.Len());
    return 1;
}

int BaseRequest::Unpack(lua_State* L) {
    auto argv = this->Args();
    if (argv == NULL) {
        return 0;
    }
    return argv->Unpack(L);
}

Argument* BaseRequest::Args() {
    if (this->argv != NULL) {
        return this->argv;
    }
    auto argv = new Argument(this->coord);
    if (argv == NULL) {
        return NULL;
    }
    int err = argv->Parse(this->payload);
    if (err) {
        this->coord->CoreLogError("[BaseRequest] Args failed, error='%d'", err);
        delete argv;
        return NULL;
    }
    this->argv = argv;
    return argv;
}

int BaseRequest::Table(lua_State* L) {
    script::Reflect& table = this->Table();
    table.Push();
    return 1;
}

script::Reflect& BaseRequest::Table() {
    static thread_local script::Reflect nullPtr(this->coord);
    int err = this->table.Decode(this->payload);
    if (err) {
        return nullPtr;
    }
    return this->table;
}

json::Reflect BaseRequest::Json() {
    return this->coord->Json->Decode(this->payload.Data());
}

}