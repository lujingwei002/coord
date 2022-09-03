#include "coord/base/base_reader.h"
#include "coord/json/json_mgr.h"
#include "coord/coord.h"
namespace coord {
CC_IMPLEMENT(base_reader, "coord::base_reader")

base_reader::base_reader(Coord* coord) : table(coord){
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

protobuf::MessageRef& base_reader::Proto(const char* name){
    if (this->proto != nullptr) {
        return this->proto;
    }
    auto message = this->coord->Proto->NewMessage(name);
    if (message == nullptr) {
        return protobuf::MessageRef::NullPtr;
    }
    int err = message->ParseFrom(this->payload);
    if (err) {
        return protobuf::MessageRef::NullPtr;
    }
    this->proto = message;
    return this->proto;
}

const char* base_reader::String() const{
    return this->payload.Data();
}

size_t base_reader::Len(){
    return this->payload.Len();
}

int base_reader::String(lua_State* L) const {
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
    script::Variable& table = this->Table();
    table.Push();
    return 1;
}

script::Variable& base_reader::Table() {
    static thread_local script::Variable nullPtr(this->coord);
    int err = this->table.Decode(this->payload);
    if (err) {
        return nullPtr;
    }
    return this->table;
}

json::JsonRef base_reader::Json() {
    return this->coord->Json->Parse(this->payload.Data());
}

}
