#include "coord/protobuf/protobuf.h"
#include "coord/protobuf/message.h"
#include "coord/protobuf/repeat_message.h"
#include "coord/coord.h"

namespace coord {
namespace protobuf {

CC_IMPLEMENT(Message, "coord::protobuf::Message")


Message::Message(Coord* coord, google::protobuf::Message* message, bool owner) {
    this->coord = coord; 
    this->root = this;
    this->message = message;
    this->descriptor = message->GetDescriptor();
    this->reflection = message->GetReflection();
    this->dirty = false;
    this->owner = owner;
}

Message::Message(Coord* coord, Message* root, google::protobuf::Message* message) {
    this->coord = coord; 
    this->root = root;
    this->message = message;
    this->descriptor = message->GetDescriptor();
    this->reflection = message->GetReflection();
    this->dirty = false;
    this->owner = false;
}

Message::~Message() {
    if(this->owner && this->message){
        delete this->message;
    } 
    this->message = nullptr;
}

int Message::CopyFrom(Message* other) {
    if (this->message == nullptr || other == nullptr || other->message == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->message;
    google::protobuf::Message* otherMessage = other->message;
    if(message->GetDescriptor() != otherMessage->GetDescriptor()){
        this->coord->CoreLogError("[Message] CopyFrom failed, this=%s, from=%s", message->GetTypeName().data(), otherMessage->GetTypeName().data());
        return -1;
    }
    this->SetDirty(true);
    message->CopyFrom(*(otherMessage));
    return 0;
}

int Message::MergeFrom(Message* other) {
    if (this->message == nullptr || other == nullptr || other->message == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->message;
    google::protobuf::Message* otherMessage = other->message;
    if(message->GetDescriptor() != otherMessage->GetDescriptor()){
        this->coord->CoreLogError("[Message] MergeFrom failed, this=%s, from=%s", message->GetTypeName().data(), otherMessage->GetTypeName().data());
        return -1;
    }
    this->SetDirty(true);
    message->MergeFrom(*(otherMessage));
    return 0;
}

google::protobuf::Message* Message::GetMessage() {
    if (this->message == nullptr) {
        return nullptr;
    }
    return this->message;
}

int Message::ByteSize() {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    return message->ByteSizeLong();
}

bool Message::IsDirty(){
    if (this->message == nullptr) {
        return false;
    }
    return this->root->dirty;
}

void Message::SetDirty(bool dirty) {
    if (this->message == nullptr) {
        return;
    }
    this->root->dirty = dirty;
}

int Message::Serialize(byte_slice& buffer) {
    if (this->message == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->message;
    size_t byteSize = this->ByteSize();
    buffer.Reserve(byteSize);
    if(buffer.Capacity() < byteSize){
        return -1;
    }
    char* end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buffer.Data());
    buffer.Resize(end - buffer.Data());
    return 0;
}

int Message::ParseFrom(byte_slice& buffer) {
    if (this->message== nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->message;
    google::protobuf::io::ArrayInputStream stream(buffer.Data(), buffer.Len());
    if(message->ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[Message] ParseFrom failed fail\n");
        return -1;
    }
    return 0;
}

int Message::ParseFrom(const char* data, size_t len) {
    if (this->message == nullptr) {
        return -1;
    }
    google::protobuf::Message* message = this->message;
    google::protobuf::io::ArrayInputStream stream(data, len);
    if(message->ParseFromZeroCopyStream(&stream) == 0){
        this->coord->CoreLogError("[Message] ParseFrom failed fail\n");
        return -1;
    }
    return 0;
}

const char* Message::Name(){
    if (this->message == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->message;
    return message->GetTypeName().data();
}

MessagePtr Message::GetMessage(const char* fieldName) {
    if (this->message == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] Get failed, message='%s, field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return nullptr;
    }
    google::protobuf::Message* subMessage = reflection->MutableMessage(message, field);
    if(subMessage == nullptr){
        this->coord->CoreLogError("[Message] Get failed, message='%s, field='%s', error='message not found'", descriptor->full_name().c_str(), fieldName);
        return nullptr;
    } 
    return new Message(this->coord, this->root, subMessage);
}

RepeatMessagePtr Message::GetRepeat(const char* fieldName) {
    if (this->message == nullptr) {
        return nullptr;
    }
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetRepeat failed, message='%s, field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return nullptr;
    }
    return new RepeatMessage(this->coord, this->root, this->message, field);
}

const char* Message::GetString(const char* fieldName) {
    if (this->message == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetString failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return nullptr; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        this->coord->CoreLogError("[PrReflectoto] GetString failed, message='%s', field='%s', error='type not string'", descriptor->full_name().c_str(), fieldName);
        return nullptr; 
    } 
    return reflection->GetString(*message, field).c_str();
}

int32_t Message::GetInt32(const char* fieldName) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32) {
        this->coord->CoreLogError("[PrReflectoto] GetInt32 failed, message='%s', field='%s', error='type not int32'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetInt32(*message, field);
}

int64_t Message::GetInt64(const char* fieldName) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
        this->coord->CoreLogError("[PrReflectoto] GetInt64 failed, message='%s', field='%s', error='type not int64'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetInt64(*message, field);
}

uint32_t Message::GetUInt32(const char* fieldName) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetUInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
        this->coord->CoreLogError("[PrReflectoto] GetUInt32 failed, message='%s', field='%s', error='type not uint32'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetUInt32(*message, field);
}

uint64_t Message::GetUInt64(const char* fieldName) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetUInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
        this->coord->CoreLogError("[PrReflectoto] GetUInt64 failed, message='%s', field='%s', error='type not uint64'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetUInt64(*message, field);
}

float Message::GetFloat(const char* fieldName) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetFloat failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT) {
        this->coord->CoreLogError("[Message] GetFloat failed, message='%s', field='%s', error='type not float'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetFloat(*message, field);
}

double Message::GetDouble(const char* fieldName) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetDouble failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        this->coord->CoreLogError("[PrReflectoto] GetDouble failed, message='%s', field='%s', error='type not double'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetDouble(*message, field);
}

bool Message::GetBool(const char* fieldName) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] GetBool failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        this->coord->CoreLogError("[PrReflectoto] GetBool failed, message='%s', field='%s', error='type not bool'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    return reflection->GetBool(*message, field);
}

int Message::Get(lua_State* L) {
    if (this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const char *fieldName = lua_tostring(L, 2);
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr) {
        this->coord->CoreLogError("[Message] Get failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0; 
    }
    if (field->is_repeated()){
        RepeatMessage *repeated = new RepeatMessage(this->coord, this->root, this->message, field);
        if(repeated == nullptr){
            return 0; 
        } 
        tolua_pushusertype_and_takeownership(L, repeated, repeated->TypeName());
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE){
        google::protobuf::Message* subMessage = reflection->MutableMessage(message, field);
        if(subMessage == nullptr){
            this->coord->CoreLogError("[Message] Get failed, message='%s', field='%s', error='MutableMessage not found'", descriptor->full_name().c_str(), fieldName);
            return 0; 
        } 
        Message* newMessage = new Message(this->coord, this->root, subMessage);
        if(newMessage == nullptr){
            return 0; 
        } 
        tolua_pushusertype_and_takeownership(L, newMessage, newMessage->TypeName());
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
        this->coord->CoreLogError("[Message] GetBool failed, message='%s', field='%s', error='type unknown'", descriptor->full_name().c_str(), fieldName);
    }
    return 0;
}

bool Message::Set(const char* fieldName, const char* value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetString(fieldName, value);
}

bool Message::SetString(const char* fieldName, const char* value, size_t len) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetString failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        this->coord->CoreLogError("[Message] SetString failed, message='%s', field='%s', error='type not string'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetString(message, field, std::string(value, len));
    return true;
}

bool Message::SetString(const char* fieldName, const char* value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetString failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        this->coord->CoreLogError("[Message] SetString failed, message='%s', field='%s', error='type unknown'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetString(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, int64_t value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetInt64(fieldName, value);
}

bool Message::SetInt64(const char* fieldName, int64_t value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
        this->coord->CoreLogError("[Message] SetInt64 failed, message='%s', field='%s', error='type not int64'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetInt64(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, int32_t value) {
    return this->SetInt32(fieldName, value);
}

bool Message::SetInt32(const char* fieldName, int32_t value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32) {
        this->coord->CoreLogError("[Message] SetInt32 failed, message='%s', field='%s', error='type not int32'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetInt32(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, uint64_t value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetUInt64(fieldName, value);
}

bool Message::SetUInt64(const char* fieldName, uint64_t value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetUInt64 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
        this->coord->CoreLogError("[Message] SetUInt64 failed, message='%s', field='%s', error='type not uint64'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetUInt64(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, uint32_t value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetUInt32(fieldName, value);
}

bool Message::SetUInt32(const char* fieldName, uint32_t value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetUInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
        this->coord->CoreLogError("[Message] SetUInt32 failed, message='%s', field='%s', error='type not uint32'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetUInt32(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, float value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetFloat(fieldName, value);
}

bool Message::SetFloat(const char* fieldName, float value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetUInt32 failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT) {
        this->coord->CoreLogError("[Message] SetUInt32 failed, message='%s', field='%s', error='type not float'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetFloat(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, double value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetDouble(fieldName, value);
}

bool Message::SetDouble(const char* fieldName, double value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetDouble failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        this->coord->CoreLogError("[Message] SetDouble failed, message='%s', field='%s', error='type not double'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetDouble(message, field, value);
    return true;
}

bool Message::Set(const char* fieldName, bool value) {
    if (this->message == nullptr) {
        return false;
    }
    return this->SetBool(fieldName, value);
}

bool Message::SetBool(const char* fieldName, bool value) {
    if (this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetBool failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        this->coord->CoreLogError("[Message] SetBool failed, message='%s', field='%s', error='type not bool'", descriptor->full_name().c_str(), fieldName);
        return false;
    }
    reflection->SetBool(message, field, value);
    return true;
}

bool Message::SetNumber(const char* fieldName, double value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] SetBool failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
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

int Message::Set(lua_State* L) {
    if (this->message == nullptr) {
        return 0;
    }
    tolua_Error tolua_err;
    const char *fieldName = lua_tostring(L, 2);
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Descriptor* descriptor = this->descriptor;
    const google::protobuf::FieldDescriptor* field = descriptor->FindFieldByName(fieldName);
    if(field == nullptr){
        this->coord->CoreLogError("[Message] Set failed, message='%s', field='%s', error='field not found'", descriptor->full_name().c_str(), fieldName);
        return 0;
    }
    if(field->is_repeated()){
        this->coord->CoreLogError("[Message] Set failed, message='%s', field='%s', error='field is repeated'", descriptor->full_name().c_str(), fieldName);
        return 0;
    }
    if(lua_isnil(L, 3) && field->label() == google::protobuf::FieldDescriptor::LABEL_REQUIRED) {
        this->coord->CoreLogError("[Message] Set failed, message='%s', field='%s', error='field is required'", descriptor->full_name().c_str(), fieldName);
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
            this->coord->CoreLogError("[Message] Set failed, message='%s', field='%s', error='ParseFromZeroCopyStream'", descriptor->full_name().c_str(), fieldName);
            return 0;
        }
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE && tolua_isusertype(L, 3,Message::_TypeName, 0, &tolua_err)){
        google::protobuf::Message *subMessage = reflection->MutableMessage(message, field);
        if(subMessage == nullptr) {
            return 0;
        }
        Message* otherProto = (Message*)  tolua_tousertype(L, 3, 0);
        if(otherProto == nullptr) {
            return 0;
        }
        google::protobuf::Message* otherMessage = otherProto->message;
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

const char* Message::DebugString() {
    if (this->message == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->message;
    return message->DebugString().data();
}

const char* Message::ShortDebugString() {
    if (this->message == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->message;
    return message->ShortDebugString().data();
}

}}
