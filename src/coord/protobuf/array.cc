#include "coord/protobuf/protobuf.h"
#include "coord/protobuf/reflect.h"
#include "coord/protobuf/array.h"
#include "coord/coord.h"

namespace coord {
namespace protobuf {

CC_IMPLEMENT(Array, "coord::protobuf::Array")

Array::Array(Coord* coord, share_ptr* sharePtr, const google::protobuf::FieldDescriptor *field) {
    this->coord = coord;
    this->sharePtr = sharePtr;
    this->field = field;
    this->sharePtr->ref++;
}

Array::~Array() {
    if (this->sharePtr) {
        this->sharePtr->ref--;
        if(this->sharePtr->ref == 0){
            delete this->sharePtr;
        }
        this->sharePtr = nullptr;
    }
}

Array::Array(Coord* coord) {
    this->coord = coord;
    this->sharePtr = nullptr;
    this->field = nullptr;
}

Array::Array(const Array& other) {
    this->coord = other.coord;
    this->sharePtr = other.sharePtr;
    this->field = other.field;
    if (this->sharePtr) {
        this->sharePtr->ref++;  
    }
} 

Array& Array::operator=(const Array& other) {
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
    this->field = other.field;
    if (this->sharePtr) {
        this->sharePtr->ref++;
    }
    return *this;
}

bool Array::operator== (std::nullptr_t v) const  {
    return this->sharePtr == nullptr;
}

bool Array::operator!= (std::nullptr_t v) const  {
    return this->sharePtr != nullptr;
}

void Array::SetDirty(bool dirty) {
    if(this->sharePtr == nullptr) {
        return;
    }
    this->sharePtr->root->dirty = dirty;
}

bool Array::Clear() {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    this->SetDirty(true);
    reflection->ClearField(message, this->field);
    return true;
} 

bool Array::MergeFrom(Array& other) {
    if (this->sharePtr == nullptr || other.sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    google::protobuf::Message* otherMessage = other.sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    const google::protobuf::Reflection* otherReflection = other.sharePtr->reflection;
    int count = otherReflection->FieldSize(*otherMessage, other.field);
    for (int i = 0; i < count; i++){
        if (this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_STRING){
            reflection->AddString(message, this->field, otherReflection->GetRepeatedString(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT32){
            reflection->AddInt32(message, this->field, otherReflection->GetRepeatedInt32(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
            reflection->AddUInt32(message, this->field, otherReflection->GetRepeatedUInt32(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_INT64){
            reflection->AddInt32(message, this->field, otherReflection->GetRepeatedInt32(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
            reflection->AddUInt32(message, this->field, otherReflection->GetRepeatedUInt32(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
            reflection->AddFloat(message, this->field, otherReflection->GetRepeatedFloat(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
            reflection->AddDouble(message, this->field, otherReflection->GetRepeatedDouble(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
            reflection->AddBool(message, this->field, otherReflection->GetRepeatedBool(*otherMessage, other.field, i));
            this->SetDirty(true);
        } else if(this->field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE){
            google::protobuf::Message* subMessage = reflection->AddMessage(message, this->field);
            const google::protobuf::Message* otherSubMessage = &(otherReflection->GetRepeatedMessage(*otherMessage, other.field, i));
            if(subMessage == NULL || otherSubMessage == NULL){
                this->coord->CoreLogError("[Array] MergeFrom failed, error='sub-message is null'");
                break;
            }
            subMessage->CopyFrom(*otherSubMessage);
            this->SetDirty(true);
        } else{
            this->coord->CoreLogError("[Array] MergeFrom failed, type=%d, error='type unknown'", this->field->cpp_type());
        }
    }
    return true;
}

bool Array::RemoveLast() {
    if(this->sharePtr == NULL) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(reflection->FieldSize(*message, field) <= 0) {
        return false;
    }
    this->SetDirty(true);
    reflection->RemoveLast(message, this->field);
    return true;
}

bool Array::RemoveAt(int index) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::Remove(int index) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return false;
    }
    this->SetDirty(true);
    reflection->SwapElements(message, this->field, index, reflection->FieldSize(*message, this->field) - 1);
    reflection->RemoveLast(message, this->field);
    return true;
}

int Array::Count(){
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    int count = reflection->FieldSize(*message, this->field);
    return count;
}

int Array::Set(lua_State *L){
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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
        this->coord->CoreLogError("[Array] Set failed, error='type unknown'");
        return 0;
    } 
}


bool Array::SetInt32(int index, int32_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::SetInt64(int index, int64_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::SetUInt32(int index, uint32_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::SetUInt64(int index, uint64_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::SetFloat(int index, float value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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


bool Array::SetDouble(int index, double value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::SetBool(int index, bool value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

bool Array::SetNumber(int index, double value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

int Array::Get(lua_State *L) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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
        Reflect *proto = new Reflect(this->coord, this->sharePtr, (google::protobuf::Message*)subMessage);
        if(proto == nullptr){
            lua_pushnil(L);
            return 1;
        } 
        tolua_pushusertype_and_takeownership(L, proto, "coord::protobuf::Reflect");
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

int32_t Array::GetInt32(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32){
        return 0;
    }
    return reflection->GetRepeatedInt32(*message, this->field, index);
}

int64_t Array::GetInt64(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64){
        return 0;
    }
    return reflection->GetRepeatedInt64(*message, this->field, index);
}

uint32_t Array::GetUInt32(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32){
        return 0;
    }
    return reflection->GetRepeatedUInt32(*message, this->field, index);
}

uint64_t Array::GetUInt64(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64){
        return 0;
    }
    return reflection->GetRepeatedUInt64(*message, this->field, index);
}

float Array::GetFloat(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT){
        return 0;
    }
    return reflection->GetRepeatedFloat(*message, this->field, index);
}

double Array::GetDouble(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE){
        return 0;
    }
    return reflection->GetRepeatedDouble(*message, this->field, index);
}

bool Array::GetBool(int index) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(index < 0 || index >= reflection->FieldSize(*message, this->field)) {
        return 0;
    }
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL){
        return 0;
    }
    return reflection->GetRepeatedBool(*message, this->field, index);
}

double Array::GetNumber(int index) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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

int Array::Add(lua_State *L) {
    if(this->sharePtr == nullptr) {
        return 0;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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
        Reflect* msg = new Reflect(this->coord, this->sharePtr, subMessage);
        if(msg == nullptr){
            return 0;
        } 
        tolua_pushusertype_and_takeownership(L, msg, "coord::protobuf::Reflect");
        return 1;
    } else{
        this->coord->CoreLogError("[Array] Add failed, error='type unknown'");
        lua_pushboolean(L, false);
        return 1;
    }
}

Reflect Array::AddMessage() {
    if(this->sharePtr == nullptr) {
        return Reflect(this->coord);
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
        return Reflect(this->coord);
    }
    google::protobuf::Message* subMessage = reflection->AddMessage(message, field);
    if(subMessage == nullptr) {
        return Reflect(this->coord);
    }
    this->SetDirty(true);
    return Reflect(this->coord, this->sharePtr, subMessage);
}

bool Array::AddInt32(int32_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT32) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddInt32(message, field, value);
    return true;
}

bool Array::AddInt64(int64_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_INT64) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddInt64(message, field, value);
    return true;
}

bool Array::AddUInt32(uint32_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddUInt32(message, field, value);
    return true;
}

bool Array::AddUInt64(uint64_t value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_UINT64) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddUInt64(message, field, value);
    return true;
}

bool Array::AddFloat(float value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_FLOAT) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddFloat(message, field, value);
    return true;
}

bool Array::AddDouble(double value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddDouble(message, field, value);
    return true;
}

bool Array::AddBool(bool value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
    if(field->cpp_type() != google::protobuf::FieldDescriptor::CPPTYPE_BOOL) {
        return false;
    }
    this->SetDirty(true);
    reflection->AddBool(message, field, value);
    return true;
}

bool Array::AddNumber(double value) {
    if(this->sharePtr == nullptr) {
        return false;
    }
    google::protobuf::Message* message = this->sharePtr->message;
    const google::protobuf::Reflection* reflection = this->sharePtr->reflection;
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