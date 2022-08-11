#pragma once 
#include "coord/builtin/type.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor_database.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <iostream>
#include <cstddef>
#include "coord/builtin/slice.h"
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export
class Coord;

namespace protobuf {//tolua_export


class Protobuf;
class Array;
class share_ptr;

class Reflect : public Destoryable {//tolua_export
CC_CLASS(Reflect);
public:
    Reflect(Coord* coord, google::protobuf::Message* message, bool owner);
    Reflect(Coord* coord, share_ptr* sharePtr, google::protobuf::Message* subMessage);
    Reflect(const Reflect& other);
    Reflect(Coord* coord);
    virtual ~Reflect();
public:
    /// get
    int Get(lua_State* L);                          //tolua_export
    Reflect GetMessage(const char* fieldName);
    Array GetRepeat(const char* fieldName);
    const char* GetString(const char* fieldName);   //tolua_export
    int32_t GetInt32(const char* fieldName);        //tolua_export
    int64_t GetInt64(const char* fieldName);        //tolua_export
    uint32_t GetUInt32(const char* fieldName);      //tolua_export
    uint64_t GetUInt64(const char* fieldName);      //tolua_export
    float GetFloat(const char* fieldName);          //tolua_export
    double GetDouble(const char* fieldName);        //tolua_export
    bool GetBool(const char* fieldName);            //tolua_export

    /// set
    int Set(lua_State* L);                                                  //tolua_export
    bool Set(const char* fieldName, const char* value);
    bool Set(const char* fieldName, int32_t value);
    bool Set(const char* fieldName, int64_t value);
    bool Set(const char* fieldName, uint32_t value);
    bool Set(const char* fieldName, uint64_t value);
    bool Set(const char* fieldName, float value);
    bool Set(const char* fieldName, double value);
    bool Set(const char* fieldName, bool value);
    bool SetString(const char* fieldName, const char* value);
    bool SetString(const char* fieldName, const char* value, size_t len);
    bool SetInt32(const char* fieldName, int32_t value);                    //tolua_export
    bool SetInt64(const char* fieldName, int64_t value);                    //tolua_export
    bool SetUInt32(const char* fieldName, uint32_t value);                  //tolua_export
    bool SetUInt64(const char* fieldName, uint64_t value);                  //tolua_export
    bool SetFloat(const char* fieldName, float value);                      //tolua_export
    bool SetDouble(const char* fieldName, double value);                    //tolua_export
    bool SetBool(const char* fieldName, bool value);                        //tolua_export
    bool SetNumber(const char* fieldName, double value);                    //tolua_export
    
    Reflect& operator=(const Reflect& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;

    const char* DebugString();                          //tolua_export
    const char* ShortDebugString();                     //tolua_export
    int CopyFrom(Reflect& other);                       //tolua_export
    int MergeFrom(Reflect& other);                      //tolua_export
    int ByteSize();                                     //tolua_export
    bool IsDirty();                                     //tolua_export
    void SetDirty(bool dirty);                          //tolua_export
    int Serialize(byte_slice& data);
    int ParseFrom(byte_slice& buffer);
    int ParseFrom(const char* data, size_t len);
    const char* Name();                                 //tolua_export
    google::protobuf::Message* GetMessage();
public:
    Coord*      coord;
    share_ptr*  sharePtr;
    
};//tolua_export 


}//tolua_export
}//tolua_export