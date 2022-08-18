#pragma once 
#include "coord/coordx.h"
#include <iostream>
#include "coord/coordx.h"
#include "coord/protobuf/declare.h"
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}
namespace coord {
    class Coord;
    namespace script {
        class Script;
    }
    namespace protobuf {
        class Protobuf;
        class Message;
        class RepeatMessage;
    }
}



namespace coord {//tolua_export
namespace protobuf {//tolua_export

class my_multi_file_error_collector : public google::protobuf::compiler::MultiFileErrorCollector {
    virtual void AddError(const std::string& fileName, int line, int column, const std::string & message);
};


class Protobuf {//tolua_export
friend Coord;
friend script::Script;
private:
    Protobuf(Coord* coord);
private:
    int main();
    int registerMetatable();
private:
    Coord*                                      coord;
    google::protobuf::compiler::DiskSourceTree* sourceTree;
    my_multi_file_error_collector*              errorCollector;
    google::protobuf::compiler::Importer*       importer;
    const google::protobuf::DescriptorPool*     pool;
    google::protobuf::DynamicMessageFactory*    factory;



public:
    ~Protobuf();
public:
    /// 设置目录映射
    int MapPath(const char *name, const char *dir);             //tolua_export
    /// 导入proto协议文件
    int Import(const char *fileName);                           //tolua_export
    // 导入dir目录下的所有proto文件
    int ImportDir(const char *dir);                             //tolua_export
    /// 创建message
    MessageRef NewMessage(google::protobuf::Message* message);
    /// 创建message
    MessageRef NewMessage(const char* name);                    //tolua_export
    /// 创建message
    google::protobuf::Message* CreateMessage(const char* name);
};//tolua_export
 

int Serialize(byte_slice& buffer, google::protobuf::Message* message);
int ParseFrom(byte_slice& buffer, google::protobuf::Message* message);
int CopyFrom(google::protobuf::Message* to, google::protobuf::Message* from);
}//tolua_export
}//tolua_export
