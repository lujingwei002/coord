#include "coord/protobuf/protobuf.h"
#include "coord/protobuf/reflect.h"
#include "coord/protobuf/array.h"
#include "coord/coord.h"

namespace coord {
namespace protobuf {

CC_IMPLEMENT(Reflect, "coord::protobuf::Reflect")


Reflect::Reflect(Coord* coord) {
    this->coord = coord;
    this->sharePtr = nullptr;
}

Reflect::Reflect(Coord* coord, google::protobuf::Message* message, bool owner) {
    share_ptr* sharePtr = new share_ptr(message);
    sharePtr->root = sharePtr;
    sharePtr->dirty = false;
    sharePtr->owner = owner;

    this->coord = coord; 
    this->sharePtr = sharePtr;
    this->sharePtr->ref++;
}

Reflect::Reflect(Coord* coord, share_ptr* sharePtr, google::protobuf::Message* subMessage) {
    share_ptr* subSharePtr = new share_ptr(subMessage);
    subSharePtr->root = sharePtr->root;
    subSharePtr->owner = false;

    this->coord = coord; 
    this->sharePtr = subSharePtr;
    this->sharePtr->ref++;
}

Reflect::Reflect(const Reflect& other) {
    //printf("Reflect::Reflect(const Reflect& other)\n");
    this->coord = other.coord;
    this->sharePtr = other.sharePtr;
    if (this->sharePtr) {
        this->sharePtr->ref++; 
    } 
}

Reflect& Reflect::operator=(const Reflect& other) {
    //printf("Reflect& Reflect::operator=(const Reflect& other)\n");
    //释放旧消息
    if (this->sharePtr) {
        this->sharePtr->ref--;
        if(this->sharePtr->ref == 0){
            delete this->sharePtr;
        }
        this->sharePtr = nullptr;
    }
    //获得新的
    this->coord = other.coord;
    this->sharePtr = other.sharePtr;
    if (this->sharePtr) {
        this->sharePtr->ref++; 
    } 
    return *this;
}

Reflect::~Reflect() {
    //printf("%s ~Reflect ~Reflect ~Reflect ~Reflect %d\n", this->sharePtr->descriptor->full_name().c_str(), this->sharePtr->ref);
    if (this->sharePtr) {
        this->sharePtr->ref--;
        if(this->sharePtr->ref == 0){
            delete this->sharePtr;
        }
        this->sharePtr = nullptr;
    }
}

int Reflect::CopyFrom(Reflect& other) {
    if (this->sharePtr == nullptr || other.sharePtr == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    google::protobuf::Message* otherReflect = other.sharePtr->message;
    if(message->GetDescriptor() != otherReflect->GetDescriptor()){
        this->coord->CoreLogError("[Reflect] CopyFrom failed, this=%s, from=%s", message->GetTypeName().data(), otherReflect->GetTypeName().data());
        return -1;
    }
    this->SetDirty(true);
    message->CopyFrom(*(otherReflect));
    return 0;
}

int Reflect::MergeFrom(Reflect& other) {
    if (this->sharePtr == nullptr || other.sharePtr == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    google::protobuf::Message* otherReflect = other.sharePtr->message;
    if(message->GetDescriptor() != otherReflect->GetDescriptor()){
        this->coord->CoreLogError("[Reflect] MergeFrom failed, this=%s, from=%s", message->GetTypeName().data(), otherReflect->GetTypeName().data());
        return -1;
    }
    this->SetDirty(true);
    message->MergeFrom(*(otherReflect));
    return 0;
}

google::protobuf::Message* Reflect::GetMessage() {
    if (this->sharePtr == nullptr) {
        return nullptr;
    }
    return this->sharePtr->message;
}

int Reflect::ByteSize() {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    return message->ByteSizeLong();
}

bool Reflect::IsDirty(){
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->sharePtr->root->dirty;
}

void Reflect::SetDirty(bool dirty) {
    if (this->sharePtr == nullptr) {
        return;
    }
    this->sharePtr->root->dirty = dirty;
}

int Reflect::Serialize(byte_slice& buffer) {
    if (this->sharePtr == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    size_t byteSize = this->ByteSize();
    buffer.Reserve(byteSize);
    if(buffer.Capacity() < byteSize){
        return -1;
    }
    char* end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buffer.Data());
    buffer.Resize(end - buffer.Data());
    return 0;
}

int Reflect::ParseFrom(byte_slice& buffer) {
    if (this->sharePtr == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    google::protobuf::io::ArrayInputStream stream(buffer.Data(), buffer.Len());
    if(message->ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[Reflect] ParseFrom failed fail\n");
        return -1;
    }
    return 0;
}

int Reflect::ParseFrom(const char* data, size_t len) {
    if (this->sharePtr == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    google::protobuf::io::ArrayInputStream stream(data, len);
    if(message->ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[Reflect] ParseFrom failed fail\n");
        return -1;
    }
    return 0;
}

const char* Reflect::Name(){
    if (this->sharePtr == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    return message->GetTypeName().data();
}

Reflect Reflect::GetMessage(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return Reflect(this->coord);
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] Get failed, message='%s, field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return Reflect(this->coord);
    }
    google::protobuf::Message* subMessage = reflection->MutableMessage(message, field);
    if(subMessage == nullptr){
        this->coord->CoreLogError("[Reflect] Get failed, message='%s, field='%s', error='message not found'", descriptor->full_name().c_str(), fieldName);
        return Reflect(this->coord);
    } 
    return Reflect(this->coord, this->sharePtr, subMessage);
}

Array Reflect::GetRepeat(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return Array(this->coord);
    }
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetRepeat failed, message='%s, field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return Array(this->coord);
    }
    return Array(this->coord, this->sharePtr, field);
}

const char* Reflect::GetString(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetString failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return nullptr; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        this->coord->CoreLogError("[PrReflectoto] GetString failed, message='%s', field='%s', error='type not string'", descriptor->full_name().c_str(), fieldName);
        return nullptr; 
    } 
    return reflection->GetString(*message, field).c_str();
}

int32_t Reflect::GetInt32(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32) {
        this->coord->CoreLogError("[PrReflectoto] GetInt32 failed, message='%s', field='%s', error='type not int32'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetInt32(*message, field);
}

int64_t Reflect::GetInt64(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
        this->coord->CoreLogError("[PrReflectoto] GetInt64 failed, message='%s', field='%s', error='type not int64'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetInt64(*message, field);
}

uint32_t Reflect::GetUInt32(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetUInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
        this->coord->CoreLogError("[PrReflectoto] GetUInt32 failed, message='%s', field='%s', error='type not uint32'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetUInt32(*message, field);
}

uint64_t Reflect::GetUInt64(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetUInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
        this->coord->CoreLogError("[PrReflectoto] GetUInt64 failed, message='%s', field='%s', error='type not uint64'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetUInt64(*message, field);
}

float Reflect::GetFloat(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetFloat failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT) {
        this->coord->CoreLogError("[PrReflectoto] GetFloat failed, message='%s', field='%s', error='type not float'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetFloat(*message, field);
}

double Reflect::GetDouble(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetDouble failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        this->coord->CoreLogError("[PrReflectoto] GetDouble failed, message='%s', field='%s', error='type not double'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetDouble(*message, field);
}

bool Reflect::GetBool(const char* fieldName) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] GetBool failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        this->coord->CoreLogError("[PrReflectoto] GetBool failed, message='%s', field='%s', error='type not bool'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetBool(*message, field);
}

int Reflect::Get(lua_State* L) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const char *fieldName = lua_tostring(L, 2);
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Reflect] Get failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if (field->is_repeated()){
        Array *repeated = new Array(this->coord, this->sharePtr, field);
        if(repeated == nullptr){
            return 0; 
        } 
        tolua_pushusertype_and_takeownership(L, repeated, "coord::protobuf::Array");
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE){
        google::protobuf::Message* subMessage = reflection->MutableMessage(message, field);
        if(subMessage == nullptr){
            this->coord->CoreLogError("[Reflect] Get failed, message='%s', field='%s', error='MutableMessage not found'", descriptor->full_name().c_str(), fieldName);
            return 0; 
        } 
        Reflect* msg = new Reflect(this->coord, this->sharePtr, subMessage);
        if(msg == nullptr){
            return 0; 
        } 
        tolua_pushusertype_and_takeownership(L, msg, "coord::protobuf::Reflect");
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        std::string str = reflection->GetString(*message, field);
        lua_pushlstring(L, str.data(), str.size());
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        lua_pushinteger(L, reflection->GetInt32(*message, field));
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        lua_pushnumber(L, reflection->GetUInt32(*message, field));
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        lua_pushnumber(L, reflection->GetInt64(*message, field));
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        lua_pushnumber(L, reflection->GetUInt64(*message, field));
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        lua_pushnumber(L, reflection->GetFloat(*message, field));
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        lua_pushnumber(L, reflection->GetDouble(*message, field));
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        lua_pushboolean(L, reflection->GetBool(*message, field));
        return 1;
    } else {
        this->coord->CoreLogError("[Reflect] GetBool failed, message='%s', field='%s', error='type unknown'", descriptor->full_name().c_str(), fieldName);
    }
    return 0;
}

bool Reflect::Set(const char* fieldName, const char* value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetString(fieldName, value);
}

bool Reflect::SetString(const char* fieldName, const char* value, size_t len) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetString failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        this->coord->CoreLogError("[Reflect] SetString failed, message='%s', field='%s', error='type not string'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetString(message, field, std::string(value, len));
    return true;
}

bool Reflect::SetString(const char* fieldName, const char* value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetString failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        this->coord->CoreLogError("[Reflect] SetString failed, message='%s', field='%s', error='type unknown'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetString(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, int64_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetInt64(fieldName, value);
}

bool Reflect::SetInt64(const char* fieldName, int64_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
        this->coord->CoreLogError("[Reflect] SetInt64 failed, message='%s', field='%s', error='type not int64'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetInt64(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, int32_t value) {
    return this->SetInt32(fieldName, value);
}

bool Reflect::SetInt32(const char* fieldName, int32_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32) {
        this->coord->CoreLogError("[Reflect] SetInt32 failed, message='%s', field='%s', error='type not int32'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetInt32(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, uint64_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetUInt64(fieldName, value);
}

bool Reflect::SetUInt64(const char* fieldName, uint64_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetUInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
        this->coord->CoreLogError("[Reflect] SetUInt64 failed, message='%s', field='%s', error='type not uint64'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetUInt64(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, uint32_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetUInt32(fieldName, value);
}

bool Reflect::SetUInt32(const char* fieldName, uint32_t value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetUInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
        this->coord->CoreLogError("[Reflect] SetUInt32 failed, message='%s', field='%s', error='type not uint32'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetUInt32(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, float value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetFloat(fieldName, value);
}

bool Reflect::SetFloat(const char* fieldName, float value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetUInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT) {
        this->coord->CoreLogError("[Reflect] SetUInt32 failed, message='%s', field='%s', error='type not float'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetFloat(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, double value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetDouble(fieldName, value);
}

bool Reflect::SetDouble(const char* fieldName, double value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetDouble failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        this->coord->CoreLogError("[Reflect] SetDouble failed, message='%s', field='%s', error='type not double'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetDouble(message, field, value);
    return true;
}

bool Reflect::Set(const char* fieldName, bool value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    return this->SetBool(fieldName, value);
}

bool Reflect::SetBool(const char* fieldName, bool value) {
    if (this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetBool failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        this->coord->CoreLogError("[Reflect] SetBool failed, message='%s', field='%s', error='type not bool'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetBool(message, field, value);
    return true;
}

bool Reflect::SetNumber(const char* fieldName, double value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] SetBool failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        reflection->SetInt32(message, field, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        reflection->SetInt64(message, field, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        reflection->SetUInt32(message, field, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        reflection->SetUInt64(message, field, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        reflection->SetFloat(message, field, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        reflection->SetDouble(message, field, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        reflection->SetBool(message, field, value);
        this->SetDirty(true);
        return true;
    } else {
        return false;
    }
}

int Reflect::Set(lua_State* L) {
    if (this->sharePtr == nullptr) {
        return 0;
    }
    tolua_Error tolua_err;
    const char *fieldName = lua_tostring(L, 2);
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Descriptor* descriptor = this->sharePtr->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Reflect] Set failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0;
    }
    if(field->is_repeated()){
        this->coord->CoreLogError("[Reflect] Set failed, message='%s', field='%s', error='field is repeated'", descriptor->full_name().c_str(), fieldName);
        return 0;
    }
    if(lua_isnil(L, 3) && field->label() == google::protobuf::FieldDescriptor::LABEL_REQUIRED) {
        this->coord->CoreLogError("[Reflect] Set failed, message='%s', field='%s', error='field is required'", descriptor->full_name().c_str(), fieldName);
        return 0;
    }
    this->SetDirty(true);
    if (lua_isnil(L, 3)) {
        reflection->ClearField(message, field);
        lua_pushinteger(L, 1);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE && lua_isstring(L, 3)){
        size_t str_len = 0;
        const char *str = (const char *)lua_tolstring(L, 3, &str_len);
        google::protobuf::Message *subMessage = reflection->MutableMessage(message, field);
        if(subMessage == nullptr) {
            return 0;
        }
        google::protobuf::io::ArrayInputStream stream(str, str_len);
        if(subMessage->ParseFromZeroCopyStream(&stream) == 0) {
            this->coord->CoreLogError("[Reflect] Set failed, message='%s', field='%s', error='ParseFromZeroCopyStream'", descriptor->full_name().c_str(), fieldName);
            return 0;
        }
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE && tolua_isusertype(L, 3,"coord::protobuf::Reflect", 0, &tolua_err)){
        google::protobuf::Message *subMessage = reflection->MutableMessage(message, field);
        if(subMessage == nullptr) {
            return 0;
        }
        Reflect* otherProto = (Reflect*)  tolua_tousertype(L, 3, 0);
        if(otherProto == nullptr) {
            return 0;
        }
        google::protobuf::Message* otherMessage = otherProto->sharePtr->message;
        if(subMessage->GetDescriptor() != otherMessage->GetDescriptor()) {
            this->coord->CoreLogError("[Proto] Set failed, self=%s, other=%s error='descriptor is conflict'", subMessage->GetTypeName().data(), otherMessage->GetTypeName().data());
            return 0;
        }
        subMessage->CopyFrom(*otherMessage);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING && lua_isstring(L, 3)) {
        size_t len = 0;
        const char *str = (const char *)lua_tolstring(L, 3, &len);
        reflection->SetString(message, field, std::string(str, len));
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32 && lua_isnumber(L, 3)) {
        int32_t val = (int32_t)lua_tonumber(L, 3);
        //对int优化, 如果等于默认值则clear
        if(field->has_default_value() && field->default_value_int32() == val) {
            reflection->ClearField(message, field);
        }else {
            reflection->SetInt32(message, field, val);
        }
        lua_pushboolean(L, true);
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32 && lua_isnumber(L, 3)) {
        reflection->SetUInt32(message, field, (uint32_t)lua_tonumber(L, 3));
        lua_pushboolean(L, true);
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64 && lua_isnumber(L, 3)) {
        int64_t val = (int64_t)lua_tonumber(L, 3);
        reflection->SetInt64(message, field, val);
        lua_pushboolean(L, true);
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64 && lua_isnumber(L, 3)) {
        reflection->SetUInt64(message, field, (uint64_t)lua_tonumber(L, 3));
        lua_pushboolean(L, true);
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT && lua_isnumber(L, 3)) {
        reflection->SetFloat(message, field, (float)lua_tonumber(L, 3));
        lua_pushboolean(L, true);
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE && lua_isnumber(L, 3)) {
        reflection->SetDouble(message, field, (double)lua_tonumber(L, 3));
        lua_pushboolean(L, true);
        return 1;
    }else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL && lua_isboolean(L, 3)) {
        reflection->SetBool(message, field, (int)lua_toboolean(L, 3));
        lua_pushboolean(L, true);
        return 1;
    }
    return 0;
}

const char* Reflect::DebugString() {
    if (this->sharePtr == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    return message->DebugString().data();
}

const char* Reflect::ShortDebugString() {
    if (this->sharePtr == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    return message->ShortDebugString().data();
}

bool Reflect::operator== (std::nullptr_t v) const  {
    return this->sharePtr == nullptr;
}

bool Reflect::operator!= (std::nullptr_t v) const  {
    return this->sharePtr != nullptr;
}

}}