#pragma once 
#include "coord/builtin/type.h"
#include <iostream>
#include "coord/builtin/slice.h"
#include "coord/protobuf/declare.h"
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export
class Coord;

namespace protobuf {//tolua_export

class my_multi_file_error_collector : public google::protobuf::compiler::MultiFileErrorCollector {
    virtual void AddError(const std::string& fileName, int line, int column, const std::string & message);
};
class Protobuf;
class Reflect;
class Array;

///
///
///   proto1 -> share_ptr  <-proto2
///                   |
///                   sub share_ptr  <-proto3
///                   |
///                   share_ptr(repeated field)   <-proto_array
///                   |

class share_ptr {
CC_CLASS(share_ptr);
public:
    share_ptr(google::protobuf::Message* message);
    virtual ~share_ptr();
public:
    int                                 ref;
    share_ptr*                          root;
    google::protobuf::Message*          message;
    const google::protobuf::Reflection* reflection;
    const google::protobuf::Descriptor* descriptor;
    bool                                owner;
    bool                                dirty;
};

class Protobuf {//tolua_export
public:
    Protobuf(Coord* coord);
    ~Protobuf();
public:
    /// 设置目录映射
    int MapPath(const char *name, const char *dir);    //tolua_export
    /// 导入proto协议文件
    int Import(const char *fileName);                  //tolua_export
    // 导入dir目录下的所有proto文件
    int ImportDir(const char *dir);                    //tolua_export
    /// 创建message
    Reflect NewReflect(google::protobuf::Message* message);
    /// 创建message
    Reflect NewReflect(const char* name);               //tolua_export

    /// 创建message
    MessagePtr NewMessage(google::protobuf::Message* message);
    /// 创建message
    MessagePtr NewMessage1(const char* name);               //tolua_export


    /// 创建message
    google::protobuf::Message* NewMessage(const char* name);
public:
    int main();
    int registerMetatable();
public:
    Coord*                                      coord;
    google::protobuf::compiler::DiskSourceTree* sourceTree;
    my_multi_file_error_collector*              errorCollector;
    google::protobuf::compiler::Importer*       importer;
    const google::protobuf::DescriptorPool*     pool;
    google::protobuf::DynamicMessageFactory*    factory;
};//tolua_export
 
Protobuf* newProtobuf(Coord* coord);
int Serialize(byte_slice& buffer, google::protobuf::Message* message);
int ParseFrom(byte_slice& buffer, google::protobuf::Message* message);
int CopyFrom(google::protobuf::Message* to, google::protobuf::Message* from);
}//tolua_export
}//tolua_export
