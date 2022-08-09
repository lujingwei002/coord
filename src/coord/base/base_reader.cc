#include "coord/base/base_reader.h"
#include "coord/json/json_mgr.h"
#include "coord/coord.h"
namespace coord {
CC_IMPLEMENT(base_reader, "coord::base_reader")

base_reader::base_reader(Coord* coord) : proto(coord), table(coord){
    this->coord = coord;
    this->argv = nullptr;
}

base_reader::~base_reader() {
    if(this->argv != NULL) {
        delete this->argv;
        this->argv = NULL;
    }
}

int base_reader::Proto(google::protobuf::Message& message) {
    return protobuf::ParseFrom(this->payload, &message);
}

protobuf::Reflect& base_reader::Proto(const char* name){
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

const char* base_reader::String() {
    return this->payload.Data();
}

size_t base_reader::Len(){
    return this->payload.Len();
}

int base_reader::String(lua_State* L){
    lua_pushlstring(L, this->payload.Data(), this->payload.Len());
    return 1;
}

int base_reader::Unpack(lua_State* L) {
    auto argv = this->Args();
    if (argv == NULL) {
        return 0;
    }
    return argv->Unpack(L);
}

Argument* base_reader::Args() {
    if (this->argv != nullptr) {
        return this->argv;
    }
    auto argv = new Argument(this->coord);
    if (argv == nullptr) {
        return nullptr;
    }
    int err = argv->Parse(this->payload);
    if (err) {
        this->coord->CoreLogError("[base_reader] Args failed, error='%d'", err);
        delete argv;
        return nullptr;
    }
    this->argv = argv;
    return argv;
}

int base_reader::Table(lua_State* L) {
    script::Reflect& table = this->Table();
    table.Push();
    return 1;
}

script::Reflect& base_reader::Table() {
    static thread_local script::Reflect nullPtr(this->coord);
    int err = this->table.Decode(this->payload);
    if (err) {
        return nullPtr;
    }
    return this->table;
}

json::Reflect base_reader::Json() {
    return this->coord->Json->Decode(this->payload.Data());
}

}
