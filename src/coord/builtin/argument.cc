#include "coord/builtin/argument.h"
#include "coord/coord.h"
#include "coord/protobuf/init.h"
#include "coord/script/script.h"
#include <tolua++/tolua++.h>

namespace coord {


Argument::Argument(Coord* coord) {
    this->coord = coord;
}

Argument::~Argument() {
    this->argv.clear();
    while(this->argv.size() > 0){
        argument_item* arg = this->argv.back();
        this->argv.pop_back();
        delete arg;
    }
}

int Argument::Count() {
    return this->argv.size();
}

bool Argument::GetBool(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return false;
    }
    if (this->argv[index]->type != ArgumentTypeBoolean) {
        return false;
    }
    return this->argv[index]->number == 1;
}

int64_t Argument::GetNumber(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return 0;
    }
    if (this->argv[index]->type != ArgumentTypeNumber) {
        return 0;
    }
    return this->argv[index]->number;
}

const char* Argument::GetString(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return nullptr;
    }
    if (this->argv[index]->type != ArgumentTypeString) {
        return nullptr;
    }
    return (const char*)this->argv[index]->str.c_str();
}

protobuf::Reflect& Argument::GetProto(size_t index) {
    static thread_local protobuf::Reflect nullPtr(this->coord);
    if (index < 0 || index >= this->argv.size()) {
        return nullPtr;
    }
    if (this->argv[index]->type != ArgumentTypeProto) {
        return nullPtr;
    }
    return this->argv[index]->proto;
}

script::Reflect& Argument::GetTable(size_t index) {
    static thread_local script::Reflect nullPtr(this->coord);
    if (index < 0 || index >= this->argv.size()) {
        return nullPtr;
    }
    if (this->argv[index]->type != ArgumentTypeTable) {
        return nullPtr;
    }
    return this->argv[index]->table;
}

int Argument::AddBool(bool value) {
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeBoolean;
    arg->number = value ? 1 : 0;
    return 0;
}

int Argument::AddNumber(int64_t value) {
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeNumber;
    arg->number = value;
    return 0;
}

int Argument::AddString(const char* value){
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeString;
    arg->str = value;
    return 0;
}

int Argument::AddNil() {
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeNil;
    return 0;
}

int Argument::AddProto(protobuf::Reflect& proto) {
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeProto;
    arg->proto = proto;
    return 0;
}

int Argument::AddTable(script::Reflect& table) {
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeTable;
    arg->table = table;
    return 0;
}

int Argument::AddTable(int ref, int type) {
    argument_item* arg = new argument_item(this->coord);
    this->argv.push_back(arg);
    arg->type = ArgumentTypeTable;
    script::Reflect table(this->coord, ref, type);
    arg->table = table;
    return 0;
}

void Argument::Trace() {
    /*for (int i = 0; i < this->argc; i++) {
        if (this->argv[i].type == ArgumentTypeNil) {
            printf("[Argument] Nil\n");
        } else if (this->argv[i].type == ArgumentTypeNumber) {
            printf("[Argument] Number:%ld\n", this->argv[i].number);
        } else if (this->argv[i].type == ArgumentTypeString) {
            printf("[Argument] String:%s\n", this->argv[i].str.c_str());        
        } else if (this->argv[i].type == ArgumentTypeBoolean) {
            printf("[Argument] Bool:%d\n", this->argv[i].number);
        }
    }*/
}

int Argument::Type(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return 0;
    }
    return this->argv[index]->type;
}

int Argument::Parse(byte_slice& data) {
    char* offset = data.Data();
    char* end = data.Data() + data.Len();
    while (true) {
        uint8_t type = *((uint8_t*)offset);
        offset += sizeof(uint8_t);
        if (type == ArgumentTypeNil) {
            argument_item* arg = new argument_item(this->coord);
            arg->type = ArgumentTypeNil;
            this->argv.push_back(arg);
        } else if(type == ArgumentTypeBoolean) {            
            if (offset + sizeof(uint8_t) > end) {
                return -1;
            }
            argument_item* arg = new argument_item(this->coord);
            arg->type = ArgumentTypeBoolean;
            arg->number = *((uint8_t*)offset);
            this->argv.push_back(arg);
            offset += sizeof(uint8_t);
        } else if(type == ArgumentTypeNumber) {            
            if (offset + sizeof(int64_t) > end) {
                return -1;
            }
            argument_item* arg = new argument_item(this->coord);
            arg->type = ArgumentTypeNumber;
            arg->number = *((int64_t*)offset);
            this->argv.push_back(arg);
            offset += sizeof(int64_t);
        } else if(type == ArgumentTypeString) {
            if (offset + sizeof(uint16_t) > end) {
                return -1;
            }
            uint16_t len = *((uint16_t*)offset);
            offset += sizeof(uint16_t);
            if (offset + len > end) {
                return -1;
            }
            argument_item* arg = new argument_item(this->coord);
            arg->type = ArgumentTypeString;
            arg->str.assign(offset, len);
            this->argv.push_back(arg);
            offset += len;
        } else if(type == ArgumentTypeTable) {
            size_t len = *((size_t*)offset);
            offset += sizeof(size_t);
            if (len == 0) {
                return -3;
            }
            auto table = this->coord->Script->NewReflect();
            int err = table.Decode(offset, end - offset);
            if (err) {
                return -2;
            }
            argument_item* arg = new argument_item(this->coord);
            arg->type = ArgumentTypeTable;
            arg->table = table;
            this->argv.push_back(arg);
            offset += len;
        } else if(type == ArgumentTypeProto) {
            size_t totalLen = *((size_t*)offset);
            offset += sizeof(size_t);
            if (totalLen == 0) {
                return -1;
            }
            if (offset + sizeof(uint16_t) > end) {
                return -1;
            }
            uint16_t nameLen = *((uint16_t*)offset);
            offset += sizeof(uint16_t);
            if (offset + nameLen > end) {
                return -1;
            }
            std::string name;
            name.assign(offset, nameLen);
            offset += nameLen;

            size_t msgLen = totalLen - sizeof(uint16_t) - nameLen;
            //消息内容
            if (offset + msgLen > end) {
                return -1;
            }
            auto proto = this->coord->Proto->NewReflect(name.c_str());
            if (proto == nullptr) {
                return -1;
            }
            int err = proto.ParseFrom(offset, msgLen);
            if(err) {
                return -1;
            }
            argument_item* arg = new argument_item(this->coord);
            arg->type = ArgumentTypeProto; 
            arg->proto = proto;    
            this->argv.push_back(arg);
            offset += msgLen;       
        } else {
            break;
        }
    }
    return 0;
}

int Argument::Serialize(byte_slice& buffer) {
    for (auto& arg : this->argv) {
        if (arg->type == ArgumentTypeNil) {
            coord::Append(buffer, (char)ArgumentTypeNil);
        } else if (arg->type == ArgumentTypeBoolean) {
            coord::Append(buffer, ArgumentTypeBoolean);
            uint8_t value = arg->number;
            coord::Append(buffer, (char*)(&value), sizeof(value));
        } else if (arg->type == ArgumentTypeNumber) {
            coord::Append(buffer, ArgumentTypeNumber);
            coord::Append(buffer, (char*)(&arg->number), sizeof(arg->number));
        } else if (arg->type == ArgumentTypeString) {
            coord::Append(buffer, ArgumentTypeString);
            uint16_t len = (uint16_t)(arg->str.length());
            coord::Append(buffer, (char*)(&len), sizeof(len));
            coord::Append(buffer, (char*)(arg->str.c_str()), len);
        } else if (arg->type == ArgumentTypeTable) {
            coord::Append(buffer, ArgumentTypeTable);
            byte_slice header = buffer.Slice(buffer.Len(), buffer.Len());
            size_t len = 0;
            coord::Append(buffer, (char*)(&len), sizeof(len));
            byte_slice body = buffer.Slice(buffer.Len(), buffer.Len());
            int err = arg->table.Encode(body);
            if (err) {
                return -1;
            }
            buffer.Resize(buffer.Len() + body.Len());
            len = body.Len();
            coord::Append(header, (char*)(&len), sizeof(len));
        } else if (arg->type == ArgumentTypeProto) {
            //数据类型
            coord::Append(buffer, ArgumentTypeProto);
            google::protobuf::Message* message = arg->proto.GetMessage();
            if (message == NULL) {
                size_t totalLen = 0;
                coord::Append(buffer, (char*)(&totalLen), sizeof(totalLen));
            } else {
                const char* name = message->GetTypeName().data();
                uint16_t nameLen = (uint16_t)(strlen(name));
                size_t msgLen = message->ByteSizeLong();
                size_t totalLen = sizeof(uint16_t) + nameLen + msgLen;
                coord::Append(buffer, (char*)(&totalLen), sizeof(totalLen));
                //消息名字
                coord::Append(buffer, (char*)(&nameLen), sizeof(nameLen));
                coord::Append(buffer, name, nameLen);
                //消息内容
                buffer.Reserve(buffer.Len() + msgLen);
                if(buffer.Capacity() < msgLen){
                    this->coord->CoreLogError("[Proto] Encode failed, capacity=%ld, msgLen=%ld, error='buffer reserve err'", buffer.Capacity(), msgLen);
                    return -1;
                } 
                char* end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)(buffer.Data() + buffer.Len()));
                buffer.Resize(end - buffer.Data());
            }
        }
    }
    coord::Append(buffer, 0);
    return 0;
}

bool Argument::IsNone(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return false;
}

bool Argument::IsNil(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return this->argv[index]->type == ArgumentTypeNil;
}

bool Argument::IsNumber(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return this->argv[index]->type == ArgumentTypeNumber;
}

bool Argument::IsBool(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return this->argv[index]->type == ArgumentTypeBoolean;
}

bool Argument::IsString(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return this->argv[index]->type == ArgumentTypeString;
}

bool Argument::IsProto(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return this->argv[index]->type == ArgumentTypeProto;
}

bool Argument::IsTable(size_t index) {
    if (index < 0 || index >= this->argv.size()) {
        return true;
    }
    return this->argv[index]->type == ArgumentTypeTable;
}

int Argument::Pack(lua_State* L) {
    return this->pack(L, 2);
}

int Argument::pack(lua_State* L, int i) {
    if (this->coord->Script->L != L) {
        this->coord->CoreLogError("[Argument] Unpack failed, error='lua_State err'");
    }
    tolua_Error tolua_err;
    while (true) {
        if(lua_isnone(L, i)){
            break;
        } else if (lua_isnil(L, i)) {
            this->AddNil();
        } else if (lua_isboolean(L, i)) {
            int value = (int)lua_toboolean(L, i);
            this->AddBool(value == 1 ? true : false);
        } else if (lua_isnumber(L, i) && lua_type(L, i) == LUA_TNUMBER) {
            int64_t value = ((int64_t)  lua_tonumber(L, i));
            this->AddNumber(value);
        } else if (lua_isstring(L, i)) {
            const char* value = ((const char*)  lua_tostring(L, i));
            this->AddString(value);
        } else if(tolua_isusertype(L,i,"coord::protobuf::Reflect",0,&tolua_err)) {
            protobuf::Reflect* proto = (protobuf::Reflect*)  tolua_tousertype(L,i,0);
            this->AddProto(*proto);
        } else if(lua_istable(L, i)) {
            lua_pushvalue(L, i);
            int type = lua_type(L, -1);
            int ref = luaL_ref(L, LUA_REGISTRYINDEX);
            this->AddTable(ref, type);
        }  else {
            this->AddNil();
        }
        i++;
    }    
    return 0;
}

int Argument::Unpack(lua_State* L) {
    if (this->coord->Script->L != L) {
        this->coord->CoreLogError("[Argument] Unpack failed, error='lua_State err'");
    }
    for (int i = 0; i < this->Count(); i++) {
        if (this->IsNumber(i)) {
            lua_pushnumber(L, this->GetNumber(i));
        } else if (this->IsBool(i)) {
            lua_pushboolean(L, this->GetBool(i));
        } else if (this->IsString(i)) {
            lua_pushstring(L, this->GetString(i));
        } else if (this->IsProto(i)) {
            void* proto = new protobuf::Reflect(this->GetProto(i));
            tolua_pushusertype_and_takeownership(L, proto, "coord::protobuf::Reflect");
        } else if (this->IsTable(i)) {
            this->GetTable(i).Push();
        } else {
            lua_pushnil(L);
        }
    }
    return this->Count();
}

void Argument::DebugPrint() {
    for (int i = 0; i < this->Count(); i++) {
        if (this->IsString(i)) {
            this->coord->LogDebug("%d) %s", i + 1, this->GetString(i));
        }
    }
}

}
