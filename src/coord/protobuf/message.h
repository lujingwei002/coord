#pragma once 
#include "coord/builtin/type.h"
#include "coord/protobuf/declare.h"
#include "coord/builtin/slice.h"
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export
namespace protobuf {//tolua_export



class Message: public RcObject {//tolua_export
CC_CLASS(Message);
public:
    Message(Coord* coord, google::protobuf::Message* message, bool owner);
    Message(Coord* coord, Message* root, google::protobuf::Message* subMessage);
    virtual ~Message(); //tolua_export
public:
    /// get
    int Get(lua_State* L);                              //tolua_export
    /// get message
    MessageRef GetMessage(const char* fieldName);       //tolua_export
    /// get array
    RepeatMessageRef GetRepeat(const char* fieldName);  //tolua_export
    /// get string
    const char* GetString(const char* fieldName);       //tolua_export
    /// get int32
    int32_t GetInt32(const char* fieldName);            //tolua_export
    /// get int64
    int64_t GetInt64(const char* fieldName);            //tolua_export
    /// get uint32
    uint32_t GetUInt32(const char* fieldName);          //tolua_export
    /// get uint64
    uint64_t GetUInt64(const char* fieldName);          //tolua_export
    /// get float
    float GetFloat(const char* fieldName);              //tolua_export
    /// get double
    double GetDouble(const char* fieldName);            //tolua_export
    /// get bool
    bool GetBool(const char* fieldName);                //tolua_export

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
    
    const char* DebugString();                          //tolua_export
    const char* ShortDebugString();                     //tolua_export
    int CopyFrom(Message* other);                       //tolua_export
    int MergeFrom(Message* other);                      //tolua_export
    int ByteSize();                                     //tolua_export
    bool IsDirty();                                     //tolua_export
    void SetDirty(bool dirty);                          //tolua_export
    int Serialize(byte_slice& data);
    int ParseFrom(byte_slice& buffer);
    int ParseFrom(const char* data, size_t len);
    const char* Name();                                 //tolua_export
    google::protobuf::Message* GetMessage();
public:
    Coord*                              coord;
    Message*                            root;
    google::protobuf::Message*          message;
    const google::protobuf::Reflection* reflection;
    const google::protobuf::Descriptor* descriptor;
    bool                                owner;
    bool                                dirty;
};//tolua_export 



}//tolua_export
}//tolua_export
