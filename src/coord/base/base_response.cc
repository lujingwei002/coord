#include "coord/base/base_response.h"
#include "coord/base/base_agent.h"
#include "coord/base/base_request.h"
#include "util/date/date.h"
#include "coord/coord.h"
namespace coord {

CC_IMPLEMENT(base_response, "coord::base_response")
CC_IMPLEMENT(internal_response, "coord::internal_response")


base_response::base_response(Coord* coord, base_agent* agent, base_request* request) : proto(coord), table(coord) {
    this->coord = coord;
    this->Code = 0;
    this->agent = agent;
    this->request = request;
    this->DataType = base_message_data_type_none;
    this->ReqTime = uv_hrtime();
}

base_response::~base_response() {
}

void base_response::Resolve() {
    this->Code = 0;
}

void base_response::Reject(int code) {
    this->Code = code;
}

void base_response::DebugLog() {
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%ld|%ld|%10s| RESPONSE | %s", 
            this->TypeName(), 
            this->request->SessionId, 
            this->request->Id, 
            date::FormatNano(duration), 
            this->request->Route.c_str()
            );
}

void base_response::onDestory() {
    this->DebugLog();
    this->Flush();
}



internal_response::internal_response(Coord* coord, internal_agent* agent, base_request* request) : base_response(coord, agent, request) {
    this->agent = agent;
    this->argv = nullptr;
}

internal_response::~internal_response() {
    if(this->argv != nullptr) {
        delete this->argv;
        this->argv = nullptr;
    }
    this->agent = nullptr;
}

int internal_response::String(const char* data, size_t len) {
    this->Payload.Resize(0);
    coord::Append(this->Payload, data, len);
    this->DataType = base_message_data_type_custom;
    return 0;
}

int internal_response::String(const char* data) {
    this->Payload.Resize(0);
    coord::Append(this->Payload, data, strlen(data));
    this->DataType = base_message_data_type_string;
    return 0;
}

int internal_response::Json(){
    this->DataType = base_message_data_type_json;
    return 0;
}

int internal_response::Proto(google::protobuf::Message& message) {
    int err = protobuf::Serialize(this->Payload, &message);
    if (err) {
        this->coord->CoreLogError("[internal_response] Proto failed, error='Serialize err'");
        return -1;
    }
    this->DataType = base_message_data_type_protobuf;
    return 0;
}

int internal_response::Proto(protobuf::Reflect& proto) {
    this->proto = proto;
    this->DataType = base_message_data_type_protobuf;
    return 0;
}

protobuf::Reflect& internal_response::Proto(){
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if(this->proto != nullptr) {
        this->DataType = base_message_data_type_protobuf;
        return this->proto;
    } else {
        return nullPtr;
    }
}

protobuf::Reflect& internal_response::Proto(const char* name){
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if(this->proto != nullptr) {
        this->DataType = base_message_data_type_protobuf;
        return this->proto;
    } else {
        auto proto = this->coord->Proto->NewReflect(name);
        if (proto == nullptr) {
            this->coord->CoreLogError("[base_response] Proto failed, name=%s, error='NewReflect err'", name);
            return nullPtr;
        }
        this->proto = proto;
        this->DataType = base_message_data_type_protobuf;
        return this->proto;
    }
}

int internal_response::Pack(lua_State* L) {
    auto argv = this->Args();
    if (argv == nullptr) {
        return 0;
    }
    return argv->Pack(L);
}

Argument* internal_response::Args() {
    if (this->argv != nullptr) {
        return this->argv;
    }
    auto argv = new Argument(this->coord);
    if (argv == nullptr) {
        return nullptr;
    }
    this->argv = argv;
    this->DataType = base_message_data_type_argument;
    return argv;
}

script::Reflect& internal_response::Table() {
    this->DataType = base_message_data_type_table;
    return this->table;
}

int internal_response::Table(lua_State* L) {
    int type = lua_type(L, -1);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == LUA_NOREF) {
        this->coord->CoreLogError("[internal_response] Table failed, error='luaL_ref err'");
        lua_pushinteger(L, -1);
        return 1;
    }
    this->table = script::newReflect(this->coord, ref, type);
    lua_pushinteger(L, 0);
    this->DataType = base_message_data_type_table;
    return 1;
}

int internal_response::Flush() {
    if(this->DataType == base_message_data_type_none) {
        this->Code = 501;
        return this->agent->Response(this->request->Id, this->Code, nullptr, 0);
    } else if(this->DataType == base_message_data_type_protobuf && this->proto != nullptr) {
        this->Payload.Resize(0);
        int err = this->proto.Serialize(this->Payload);
        if(err){
            this->coord->CoreLogError("[internal_response] write failed");
            return -1;
        }
        return 0;
    } else if(this->DataType == base_message_data_type_argument && this->argv != nullptr){
        return this->agent->Response(this->request->Id, this->Code, this->argv);
    } else if(this->DataType == base_message_data_type_table && this->table != nullptr){
        this->Payload.Resize(0);
        int err = this->table.Encode(this->Payload);
        if(err){
            this->coord->CoreLogError("[internal_response] write failed");
            return -1;
        }
        return 0;
    } else if(this->DataType == base_message_data_type_string){
        return this->agent->Response(this->request->Id, this->Code, this->Payload);
    }
    return 0;
}

}
