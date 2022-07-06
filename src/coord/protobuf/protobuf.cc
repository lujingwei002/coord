#include "coord/protobuf/protobuf.h"
#include "coord/protobuf/reflect.h"
#include "coord/protobuf/array.h"
#include "coord/config/config.h"
#include "coord/builtin/error.h"
#include "coord/coord.h"

namespace coord {
namespace protobuf {

CC_IMPLEMENT(share_ptr, "coord::protobuf::share_ptr")

void my_multi_file_error_collector::AddError(const std::string& fileName, int line, int column, const std::string & message) {
    // std::cout << line << ":" << column << " " << message << std::endl;
    coorda->coreLogError("[Proto] my_multi_file_error_collector, file='%s', line=%d, column=%d, error='%s'\n", fileName.c_str(), line, column, message.c_str());
}

int Serialize(byte_slice& buffer, google::protobuf::Message* message) {
    size_t byteSize = message->ByteSizeLong();
    buffer.Reserve(byteSize);
    if(buffer.Capacity() < byteSize){
        return ErrorOutOfMemory;
    }
    char* end = (char *)message->SerializeWithCachedSizesToArray((google::protobuf::uint8 *)buffer.Data());
    buffer.Resize(end - buffer.Data());
    return 0;
}

int ParseFrom(byte_slice& buffer, google::protobuf::Message* message) {
    google::protobuf::io::ArrayInputStream stream(buffer.Data(), buffer.Len());
    if(message->ParseFromZeroCopyStream(&stream) == 0){
        return ErrorInvalid;
    }
    return 0;
}

int CopyFrom(google::protobuf::Message* to, google::protobuf::Message* from) {
    if(from->GetDescriptor() != to->GetDescriptor()){
        return ErrorType;
    }
    to->CopyFrom(*from);
    return 0;
} 

share_ptr::share_ptr(google::protobuf::Message* message) {
    this->message = message;
    this->descriptor = message->GetDescriptor();
    this->reflection = message->GetReflection();
    this->ref = 0;
    this->owner = true;
}

share_ptr::~share_ptr(){
    if(this->owner && this->message){
        delete this->message;
    } 
    this->message = nullptr;
}

Protobuf* newProtobuf(Coord* coord) {
    Protobuf* self = new Protobuf(coord);
    return self; 
}

Protobuf::Protobuf(Coord* coord) : coord(coord) {
    this->sourceTree = new google::protobuf::compiler::DiskSourceTree();
    this->errorCollector = new my_multi_file_error_collector();
    this->importer = new google::protobuf::compiler::Importer(sourceTree, errorCollector);
    this->sourceTree->MapPath("", "");
    this->pool = importer->pool();
    this->factory = new google::protobuf::DynamicMessageFactory();
}

Protobuf::~Protobuf(){
    if (this->sourceTree) {
        delete this->sourceTree;
        this->sourceTree = nullptr;
    }
    if (this->errorCollector) {
        delete this->errorCollector;
        this->errorCollector = nullptr;
    }
    if (this->importer) {
        delete this->importer;
        this->importer = nullptr;
    }
    if (this->factory) {
        delete this->factory;
        this->factory = nullptr;
    }
}

int Protobuf::MapPath(const char *name, const char *dir) {
    this->sourceTree->MapPath(name, dir);
    return 0;
}

int Protobuf::Import(const char *fileName) {
    this->coord->coreLogDebug("[Proto] Import, file=%s", fileName);
    const google::protobuf::FileDescriptor* file = importer->Import(fileName);
    if(file == nullptr) {
        this->coord->coreLogError("[Proto] Import failed, file=%s", fileName);
        return ErrorInvalid;
    }
    return 0;
}

int Protobuf::ImportDir(const char *dir) {
    this->coord->coreLogDebug("[Proto] ImportDir, file=%s", dir);
    uv_fs_t req;
    uv_dirent_t ent;
    uv_fs_scandir(&this->coord->loop, &req, dir, 0, NULL);
    static thread_local char path[PATH_MAX];
    while(uv_fs_scandir_next(&req, &ent) != UV_EOF) {
        if (ent.type != UV_DIRENT_FILE) {
            continue;
        }
        if (strstr(ent.name, ".proto") + 6 != (ent.name + strlen(ent.name))) {
            continue;
        }
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, ent.name);
        int err = this->Import(path);
        if (err) {
            return err;
        }
    }
    return 0;
}

Reflect Protobuf::NewReflect(const char *name) {
    google::protobuf::Message* message = this->NewMessage(name);
    if(message == nullptr){
        return Reflect(this->coord);//null
    }
    return Reflect(this->coord, message, true);
} 

static int __index(lua_State* L) {
    lua_getmetatable(L, 1); //self key mt
    lua_pushvalue(L, 2); //self key mt key
    lua_gettable(L, -2); //self key mt value
    if(lua_iscfunction(L, -1)) {
        lua_remove(L, -2);//self key value
        return 1;
    } else {
        lua_pop(L, 2);//self key        
        coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(L,1,0);
        return self->Get(L);
    }
    return 0;
}

static int __newindex(lua_State* L) {
    coord::protobuf::Reflect* self = (coord::protobuf::Reflect*)  tolua_tousertype(L,1,0);
    return self->Set(L);
}

int Protobuf::main() {
    if(this->coord->Config->Basic.Proto.length() > 0) {
        int err = this->ImportDir(this->coord->Config->Basic.Proto.c_str());
        if (err) {
            this->coord->coreLogError("[Proto] main failed, error='import proto err'");
            return err;
        }
    }
    return 0;
}

int Protobuf::registerMetatable() {
    lua_State* L = this->coord->Script->L;
    luaL_getmetatable (L, "coord::protobuf::Reflect");
    if(lua_isnil(L, -1)) {
        this->coord->coreLogError("[Proto] registerMetatable failed, error='metatable not found'");
        return 1;
    }
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, __index);
    lua_settable(L, -3);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, __newindex);
    lua_settable(L, -3);
    return 0;
}

Reflect Protobuf::NewReflect(google::protobuf::Message* message) {
    return Reflect(this->coord, message, false);
} 

google::protobuf::Message* Protobuf::NewMessage(const char* name) {
    google::protobuf::Message* message = NULL;
    const google::protobuf::Descriptor* descriptor = pool->FindMessageTypeByName(name);
    if(descriptor == NULL) {
        this->coord->coreLogError("[Proto] NewMessage failed, name=%s, error='descriptor not found'", name);
        return NULL;
    }
    const google::protobuf::Message* prototype = factory->GetPrototype(descriptor);
    if(prototype == NULL) {
        this->coord->coreLogError("[Proto] NewMessage failed, name=%s, error='prototype not found'", name);
        return NULL;
    }
    message = prototype->New();
    if(message == NULL) {
        this->coord->coreLogError("[Proto] NewMessage failed, name=%s, error='message not found'", name);
        return NULL;
    }
    return message;
}

}}