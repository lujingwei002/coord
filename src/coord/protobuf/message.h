#pragma once 
#include "coord/coordx.h"
#include "coord/memory/type.h"
#include "coord/protobuf/declare.h"

extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {
    namespace protobuf {
        class RepeatMessage;
        class Protobuf;
    }
}
namespace coord {//tolua_export
namespace protobuf {//tolua_export



class Message: public coord::RcObject {//tolua_export
RC_CLASS(Message);
friend RepeatMessage;
friend Protobuf;
private:
    Message(Coord* coord, google::protobuf::Message* message, bool owner);
    Message(Coord* coord, Message* root, google::protobuf::Message* subMessage);
private:
    Coord*                              coord;
    Message*                            root;
    google::protobuf::Message*          message;
    const google::protobuf::Reflection* reflection;
    const google::protobuf::Descriptor* descriptor;
    bool                                owner;
    bool                                dirty;



public:
    virtual ~Message(); //tolua_export
public:
    /// get
    int Get(lua_State* L);                              //tolua_export
    MessageRef GetMessage(const char* fieldName);       
    RepeatMessageRef GetRepeat(const char* fieldName);  
    const char* GetString(const char* fieldName);       
    int32_t GetInt32(const char* fieldName);            
    int64_t GetInt64(const char* fieldName);            
    uint32_t GetUInt32(const char* fieldName);          
    uint64_t GetUInt64(const char* fieldName);          
    float GetFloat(const char* fieldName);              
    double GetDouble(const char* fieldName);            
    bool GetBool(const char* fieldName);                

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
    bool SetInt32(const char* fieldName, int32_t value);                    
    bool SetInt64(const char* fieldName, int64_t value);                    
    bool SetUInt32(const char* fieldName, uint32_t value);                  
    bool SetUInt64(const char* fieldName, uint64_t value);                  
    bool SetFloat(const char* fieldName, float value);                      
    bool SetDouble(const char* fieldName, double value);                    
    bool SetBool(const char* fieldName, bool value);                        
    bool SetNumber(const char* fieldName, double value);                    
    
    bool IsDirty();                                                         //tolua_export
    void SetDirty(bool dirty);                                              //tolua_export

    const char* DebugString();                                              //tolua_export
    const char* ShortDebugString();                                         //tolua_export
    int ByteSize();                                                         //tolua_export
    const char* Name();                                                     //tolua_export
    google::protobuf::Message* GetMessage();

    int CopyFrom(const MessageRef& other);                                           //tolua_export
    int MergeFrom(const MessageRef& other);                                          //tolua_export
    int Serialize(byte_slice& data);
    int ParseFrom(byte_slice& buffer);
    int ParseFrom(const char* data, size_t len);
    
    
};//tolua_export 



}//tolua_export
}//tolua_export
