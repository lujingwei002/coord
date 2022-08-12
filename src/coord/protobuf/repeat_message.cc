#include "coord/protobuf/protobuf.h"
#include "coord/protobuf/repeat_message.h"
#include "coord/protobuf/message.h"
#include "coord/coord.h"

namespace coord {
namespace protobuf {

CC_IMPLEMENT(RepeatMessage, "coord::protobuf::RepeatMessage")

RepeatMessage::RepeatMessage(Coord* coord, Message* root, google::protobuf::Message* message, const google::protobuf::FieldDescriptor *field) {
    this->coord = coord;
    this->root = root;
    this->message = message;
    this->descriptor = message->GetDescriptor();
    this->reflection = message->GetReflection();
    this->field = field;
}

RepeatMessage::~RepeatMessage() {
}

void RepeatMessage::SetDirty(bool dirty) {
    if(this->message == nullptr) {
        return;
    }
    this->root->dirty = dirty;
}

bool RepeatMessage::Clear() {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    this->SetDirty(true);
    reflection->ClearField(message, this->field);
    return true;
} 

bool RepeatMessage::MergeFrom(RepeatMessage* other) {
    if (this->message == nullptr || other == nullptr || other->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    google::protobuf::Message* otherMessage = other->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    const google::protobuf::Reflection* otherReflection = other->reflection;
    int count = otherReflection->FieldSize(*otherMessage, other->field);
    for (int i = 0; i < count; i++){
        if (this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING){
            reflection->AddString(message, this->field, otherReflection->GetRepeatedString(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
            reflection->AddInt32(message, this->field, otherReflection->GetRepeatedInt32(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
            reflection->AddUInt32(message, this->field, otherReflection->GetRepeatedUInt32(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
            reflection->AddInt32(message, this->field, otherReflection->GetRepeatedInt32(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
            reflection->AddUInt32(message, this->field, otherReflection->GetRepeatedUInt32(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
            reflection->AddFloat(message, this->field, otherReflection->GetRepeatedFloat(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
            reflection->AddDouble(message, this->field, otherReflection->GetRepeatedDouble(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
            reflection->AddBool(message, this->field, otherReflection->GetRepeatedBool(*otherMessage, other->field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE){
            google::protobuf::Message* subMessage = reflection->AddMessage(message, this->field);
            const google::protobuf::Message* otherSubMessage = &(otherReflection->GetRepeatedMessage(*otherMessage, other->field, i));
            if(subMessage == NULL || otherSubMessage == NULL){
                this->coord->CoreLogError("[RepeatMessage] MergeFrom failed, error='sub-message is null'");
                break;
            }
            subMessage->CopyFrom(*otherSubMessage);
            this->SetDirty(true);
        } else{
            this->coord->CoreLogError("[RepeatMessage] MergeFrom failed, type=%d, error='type unknown'", this->field->cpp_type());
        }
    }
    return true;
}

bool RepeatMessage::RemoveLast() {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(reflection->FieldSize(*message, field) <= 0) {
        return false;
    }
    this->SetDirty(true);
    reflection->RemoveLast(message, this->field);
    return true;
}

bool RepeatMessage::RemoveAt(int index) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)){
        return false;
    }
    this->SetDirty(true);
    int count = reflection->FieldSize(*message, this->field) - index - 1;
    for(int i = 0; i < count; i++) {
        reflection->SwapElements(message, this->field, i + index, i + index + 1);
    }
    reflection->RemoveLast(message, this->field);
    return true;
}

bool RepeatMessage::Remove(int index) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    this->SetDirty(true);
    reflection->SwapElements(message, this->field, index, reflection->FieldSize(*message, this->field) - 1);
    reflection->RemoveLast(message, this->field);
    return true;
}

int RepeatMessage::Count(){
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    int count = reflection->FieldSize(*message, this->field);
    return count;
}

int RepeatMessage::Set(lua_State *L){
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    int index = (int)lua_tonumber(L, 2) - 1;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        lua_pushboolean(L, false);
        return 1;
    }
    if (field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING && lua_type(L, 3) == LUA_TSTRING){
        const char *str = (const char *)lua_tostring(L, 3);
        reflection->SetRepeatedString(message, this->field, index, str);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32 && lua_type(L, 3) == LUA_TNUMBER){
        int32_t value = (int)lua_tonumber(L, 3);
        reflection->SetRepeatedInt32(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32 && lua_type(L, 3) == LUA_TNUMBER){
        uint32_t value = (unsigned int)lua_tonumber(L, 3);
        reflection->SetRepeatedUInt32(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64 && lua_type(L, 3) == LUA_TNUMBER){
        int64_t value = (int)lua_tonumber(L, 3);
        reflection->SetRepeatedInt64(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64 && lua_type(L, 3) == LUA_TNUMBER){
        uint64_t value = (unsigned int)lua_tonumber(L, 3);
        reflection->SetRepeatedUInt64(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT && lua_type(L, 3) == LUA_TNUMBER){
        float value = (float)lua_tonumber(L, 3);
        reflection->SetRepeatedFloat(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE && lua_type(L, 3) == LUA_TNUMBER){
        double value = (double)lua_tonumber(L, 3);
        reflection->SetRepeatedDouble(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL && lua_type(L, 3) == LUA_TBOOLEAN){
        int value = (int)lua_toboolean(L, 3);
        reflection->SetRepeatedBool(message, this->field, index, value);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else {
        this->coord->CoreLogError("[RepeatMessage] Set failed, error='type unknown'");
        return 0;
    } 
}


bool RepeatMessage::SetInt32(int index, int32_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        return false;
    }
    reflection->SetRepeatedInt32(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}

bool RepeatMessage::SetInt64(int index, int64_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        return false;
    }
    reflection->SetRepeatedInt64(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}

bool RepeatMessage::SetUInt32(int index, uint32_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        return false;
    }
    reflection->SetRepeatedUInt32(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}

bool RepeatMessage::SetUInt64(int index, uint64_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        return false;
    }
    reflection->SetRepeatedUInt64(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}

bool RepeatMessage::SetFloat(int index, float value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        return false;
    }
    reflection->SetRepeatedFloat(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}


bool RepeatMessage::SetDouble(int index, double value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        return false;
    }
    reflection->SetRepeatedDouble(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}

bool RepeatMessage::SetBool(int index, bool value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        return false;
    }
    reflection->SetRepeatedBool(message, this->field, index, value);
    this->SetDirty(true);
    return true;
}

bool RepeatMessage::SetNumber(int index, double value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        reflection->SetRepeatedInt32(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        reflection->SetRepeatedInt64(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        reflection->SetRepeatedUInt32(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        reflection->SetRepeatedUInt64(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        reflection->SetRepeatedFloat(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        reflection->SetRepeatedDouble(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        reflection->SetRepeatedBool(message, this->field, index, value);
        this->SetDirty(true);
        return true;
    } else {
        return false;
    }
}

int RepeatMessage::Get(lua_State *L) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    int index = (int)lua_tonumber(L, 2) - 1;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if (field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE){
        const google::protobuf::Message* subMessage = &(reflection->GetRepeatedMessage(*message, this->field, index));
        if(subMessage == nullptr) {
            lua_pushnil(L);
            return 1;
        }
        Message* proto = new Message(this->coord, this->root, (google::protobuf::Message*)subMessage);
        if(proto == nullptr){
            lua_pushnil(L);
            return 1;
        } 
        tolua_pushusertype_and_takeownership(L, proto, proto->TypeName());
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING){
        lua_pushstring(L, reflection->GetRepeatedString(*message, this->field, index).data());
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        lua_pushinteger(L, reflection->GetRepeatedInt32(*message, this->field, index));
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        lua_pushnumber(L, reflection->GetRepeatedUInt32(*message, this->field, index));
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        lua_pushinteger(L, reflection->GetRepeatedInt64(*message, this->field, index));
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        lua_pushnumber(L, reflection->GetRepeatedUInt64(*message, this->field, index));
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        lua_pushnumber(L, reflection->GetRepeatedFloat(*message, this->field, index));
        return 1;
     } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        lua_pushnumber(L, reflection->GetRepeatedDouble(*message, this->field, index));
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        lua_pushboolean(L, reflection->GetRepeatedBool(*message, this->field, index));
        return 1;
    } else {
        return 0;
    }
}

int32_t RepeatMessage::GetInt32(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        return 0;
    }
    return reflection->GetRepeatedInt32(*message, this->field, index);
}

int64_t RepeatMessage::GetInt64(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        return 0;
    }
    return reflection->GetRepeatedInt64(*message, this->field, index);
}

uint32_t RepeatMessage::GetUInt32(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        return 0;
    }
    return reflection->GetRepeatedUInt32(*message, this->field, index);
}

uint64_t RepeatMessage::GetUInt64(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        return 0;
    }
    return reflection->GetRepeatedUInt64(*message, this->field, index);
}

float RepeatMessage::GetFloat(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        return 0;
    }
    return reflection->GetRepeatedFloat(*message, this->field, index);
}

double RepeatMessage::GetDouble(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        return 0;
    }
    return reflection->GetRepeatedDouble(*message, this->field, index);
}

bool RepeatMessage::GetBool(int index) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        return 0;
    }
    return reflection->GetRepeatedBool(*message, this->field, index);
}

double RepeatMessage::GetNumber(int index) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        return reflection->GetRepeatedInt32(*message, this->field, index);
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        return reflection->GetRepeatedUInt32(*message, this->field, index);
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        return reflection->GetRepeatedInt64(*message, this->field, index);
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        return reflection->GetRepeatedUInt64(*message, this->field, index);
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        return reflection->GetRepeatedFloat(*message, this->field, index);
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        return reflection->GetRepeatedDouble(*message, this->field, index);
    } else {
        return 0;
    }
}

int RepeatMessage::Add(lua_State *L) {
    if(this->message == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if (field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING) {
        const char* val = (const char *)lua_tostring(L, 2);
        reflection->AddString(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        int val = (int)lua_tointeger(L, 2);
        reflection->AddInt32(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        unsigned int val = (unsigned int)lua_tonumber(L, 2);
        reflection->AddUInt32(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        long int val = (int)lua_tointeger(L, 2);
        reflection->AddInt64(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        unsigned long int val = (unsigned int)lua_tonumber(L, 2);
        reflection->AddUInt64(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        float val = (float)lua_tonumber(L, 2);
        reflection->AddFloat(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        double val = (double)lua_tonumber(L, 2);
        reflection->AddDouble(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        int val = (int)lua_toboolean(L, 2);
        reflection->AddBool(message, field, val);
        this->SetDirty(true);
        lua_pushboolean(L, true);
        return 1;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE){
        google::protobuf::Message* subMessage = reflection->AddMessage(message, field);
        if(subMessage == nullptr) {
            return 0;
        }
        this->SetDirty(true);
        Message* newMessage = new Message(this->coord, this->root, subMessage);
        if(newMessage == nullptr){
            return 0;
        } 
        tolua_pushusertype_and_takeownership(L, newMessage, newMessage->TypeName());
        return 1;
    } else{
        this->coord->CoreLogError("[RepeatMessage] Add failed, error='type unknown'");
        lua_pushboolean(L, false);
        return 1;
    }
}

MessageRef RepeatMessage::AddMessage() {
    if(this->message == nullptr) {
        return nullptr;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
        return nullptr;
    }
    google::protobuf::Message* subMessage = reflection->AddMessage(message, field);
    if(subMessage == nullptr) {
        return nullptr;
    }
    this->SetDirty(true);
    return new Message(this->coord, this->root, subMessage);
}

bool RepeatMessage::AddInt32(int32_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddInt32(message, field, value);
    return true;
}

bool RepeatMessage::AddInt64(int64_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddInt64(message, field, value);
    return true;
}

bool RepeatMessage::AddUInt32(uint32_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddUInt32(message, field, value);
    return true;
}

bool RepeatMessage::AddUInt64(uint64_t value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddUInt64(message, field, value);
    return true;
}

bool RepeatMessage::AddFloat(float value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddFloat(message, field, value);
    return true;
}

bool RepeatMessage::AddDouble(double value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddDouble(message, field, value);
    return true;
}

bool RepeatMessage::AddBool(bool value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddBool(message, field, value);
    return true;
}

bool RepeatMessage::AddNumber(double value) {
    if(this->message == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->message;
    const google::protobuf::Reflection* reflection = this->reflection;
    if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        reflection->AddInt32(message, field, (int32_t)value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        reflection->AddUInt32(message, field, (uint32_t)value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        reflection->AddInt64(message, field, (int64_t)value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        reflection->AddUInt64(message, field, (uint64_t)value);
        this->SetDirty(true);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        reflection->AddFloat(message, field, (float)value);
        return true;
    } else if(field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        reflection->AddDouble(message, field, (double)value);
        this->SetDirty(true);
        return true;
    } else {
        return false;
    }
}

}}
