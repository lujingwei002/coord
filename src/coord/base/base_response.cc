#include "coord/base/base_response.h"
#include "coord/base/base_agent.h"
#include "coord/base/base_request.h"
#include "util/date/date.h"
#include "coord/coord.h"
namespace coord {

CC_IMPLEMENT(base_response, "coord::base_response")

base_response::base_response(Coord* coord, base_agent* agent, base_request* request) : proto(coord), table(coord) {
    this->coord = coord;
    this->Code = 0;
    this->agent = agent;
    this->request = request;
    this->argv = nullptr;
    this->DataType = base_message_data_type_none;
    this->ReqTime = uv_hrtime();
}

base_response::~base_response() {
    if(this->argv != nullptr) {
        delete this->argv;
        this->argv = nullptr;
    }
}

void base_response::Resolve() {
    this->Code = 0;
}

void base_response::Reject(int code) {
    this->Code = code;
}

int base_response::String(const char* data, size_t len) {
    this->payload.Resize(0);
    coord::Append(this->payload, data, len);
    this->DataType = base_message_data_type_custom;
    return 0;
}

int base_response::String(const char* data) {
    this->payload.Resize(0);
    coord::Append(this->payload, data, strlen(data));
    this->DataType = base_message_data_type_string;
    return 0;
}

int base_response::Json(){
    this->DataType = base_message_data_type_json;
    return 0;
}

int base_response::Proto(google::protobuf::Message& message) {
    int err = protobuf::Serialize(this->payload, &message);
    if (err) {
        this->coord->CoreLogError("[base_response] Proto failed, error='Serialize err'");
        return -1;
    }
    this->DataType = base_message_data_type_protobuf;
    return 0;
}

int base_response::Proto(protobuf::Reflect& proto) {
    this->proto = proto;
    this->DataType = base_message_data_type_protobuf;
    return 0;
}

protobuf::Reflect& base_response::Proto(){
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if(this->proto != nullptr) {
        this->DataType = base_message_data_type_protobuf;
        return this->proto;
    } else {
        return nullPtr;
    }
}

protobuf::Reflect& base_response::Proto(const char* name){
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

int base_response::Pack(lua_State* L) {
    auto argv = this->Args();
    if (argv == nullptr) {
        return 0;
    }
    return argv->Pack(L);
}

Argument* base_response::Args() {
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

script::Reflect& base_response::Table() {
    this->DataType = base_message_data_type_table;
    return this->table;
}

int base_response::Table(lua_State* L) {
    int type = lua_type(L, -1);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == LUA_NOREF) {
        this->coord->CoreLogError("[base_response] Table failed, error='luaL_ref err'");
        lua_pushinteger(L, -1);
        return 1;
    }
    this->table = script::newReflect(this->coord, ref, type);
    lua_pushinteger(L, 0);
    this->DataType = base_message_data_type_table;
    return 1;
}

void base_response::onDestory() {
    this->Flush();
    uint64_t duration = uv_hrtime() - this->ReqTime;
    this->coord->LogDebug("|%10s|%10s| RESPONSE |\t%s", this->TypeName(), date::FormatNano(duration), this->Route.c_str());
}

int base_response::Flush() {
    printf("aaaaaa1 %d\n", this->DataType);
    if(this->DataType == base_message_data_type_none) {
    printf("aaaaaa2\n");
        this->Code = 501;
        return this->agent->response(this->request->Id, this->Code, nullptr, 0);
    } else if(this->DataType == base_message_data_type_protobuf && this->proto != nullptr) {
        this->payload.Resize(0);
        int err = this->proto.Serialize(this->payload);
        if(err){
            this->coord->CoreLogError("[base_response] write failed");
            return -1;
        }
        return 0;
    } else if(this->DataType == base_message_data_type_argument && this->argv != nullptr){
        return this->agent->response(this->request->Id, this->Code, this->argv);
    } else if(this->DataType == base_message_data_type_table && this->table != nullptr){
        this->payload.Resize(0);
        int err = this->table.Encode(this->payload);
        if(err){
            this->coord->CoreLogError("[base_response] write failed");
            return -1;
        }
        return 0;
    } else if(this->DataType == base_message_data_type_string){
        return this->agent->response(this->request->Id, this->Code, this->payload);
    }
    return 0;
}

}
