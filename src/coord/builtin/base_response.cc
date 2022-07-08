#include "coord/builtin/base_response.h"
#include "coord/coord.h"
namespace coord {

BaseResponse::BaseResponse(Coord* coord) : proto(coord), table(coord) {
    this->coord = coord;
    this->code = 0;
    this->argv = NULL;
    this->type = response_type_none;
}

BaseResponse::~BaseResponse() {
    if(this->argv != NULL) {
        delete this->argv;
        this->argv = NULL;
    }
}

void BaseResponse::clear() {

}

void BaseResponse::Resolve() {
    this->code = 0;
}

void BaseResponse::Reject(int code) {
    this->code = code;
}

int BaseResponse::String(const char* data, size_t len) {
    this->payload.Resize(0);
    coord::Append(this->payload, data, len);
    this->type = response_type_string;
    return 0;
}

int BaseResponse::String(const char* data) {
    return this->String(data, strlen(data));
}

int BaseResponse::Json(){
    this->type = response_type_json;
    return 0;
}

int BaseResponse::Proto(google::protobuf::Message& message) {
    int err = protobuf::Serialize(this->payload, &message);
    if (err) {
        this->coord->CoreLogError("[BaseResponse] Proto failed, error='Serialize err'");
        return -1;
    }
    this->type = response_type_proto;
    return 0;
}

int BaseResponse::Proto(protobuf::Reflect& proto) {
    this->proto = proto;
    this->type = response_type_proto;
    return 0;
}

protobuf::Reflect& BaseResponse::Proto(){
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if(this->proto != nullptr) {
        this->type = response_type_proto;
        return this->proto;
    } else {
        return nullPtr;
    }
}

protobuf::Reflect& BaseResponse::Proto(const char* name){
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if(this->proto != nullptr) {
        this->type = response_type_proto;
        return this->proto;
    } else {
        auto proto = this->coord->Proto->NewReflect(name);
        if (proto == nullptr) {
            this->coord->CoreLogError("[BaseResponse] Proto failed, name=%s, error='NewReflect err'", name);
            return nullPtr;
        }
        this->proto = proto;
        this->type = response_type_proto;
        return this->proto;
    }
}

int BaseResponse::Pack(lua_State* L) {
    auto argv = this->Args();
    if (argv == NULL) {
        return 0;
    }
    return argv->Pack(L);
}

Argument* BaseResponse::Args() {
    if (this->argv != NULL) {
        return this->argv;
    }
    auto argv = new Argument(this->coord);
    if (argv == NULL) {
        return NULL;
    }
    this->argv = argv;
    this->type = response_type_argument;
    return argv;
}

script::Reflect& BaseResponse::Table() {
    this->type = response_type_table;
    return this->table;
}

int BaseResponse::Table(lua_State* L) {
    int type = lua_type(L, -1);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == LUA_NOREF) {
        this->coord->CoreLogError("[BaseResponse] Table failed, error='luaL_ref err'");
        lua_pushinteger(L, -1);
        return 1;
    }
    this->table = script::newReflect(this->coord, ref, type);
    lua_pushinteger(L, 0);
    this->type = response_type_table;
    return 1;
}

int BaseResponse::flush() {
    if(this->type == response_type_proto && this->proto != nullptr) {
        this->payload.Resize(0);
        int err = this->proto.Serialize(this->payload);
        if(err){
            this->coord->CoreLogError("[BaseResponse] write failed");
            return -1;
        }
        return 0;
    } else if(this->type == response_type_argument && this->argv != nullptr){
        this->payload.Resize(0);
        int err = this->argv->Serialize(this->payload);
        if(err){
            this->coord->CoreLogError("[BaseResponse] write failed");
            return -1;
        }
        return 0;
    } else if(this->type == response_type_table && this->table != nullptr){
        this->payload.Resize(0);
        int err = this->table.Encode(this->payload);
        if(err){
            this->coord->CoreLogError("[BaseResponse] write failed");
            return -1;
        }
        return 0;
    }
    return 0;
}

}