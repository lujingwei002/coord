#pragma once 
#include "coord/coordx.h"
#include "coord/memory/type.h"
#include "coord/protobuf/declare.h"
#include "coord/coordx.h"
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {
    namespace protobuf {
        class Message;
    }
}

namespace coord {//tolua_export
namespace protobuf {//tolua_export


class RepeatMessage: public coord::RcObject {//tolua_export
RC_CLASS(RepeatMessage);
friend Message;
private:
    RepeatMessage(Coord* coord, Message* root, google::protobuf::Message* message, const google::protobuf::FieldDescriptor *field);
private:
    Coord*                                      coord;
    Message*                                    root;
    google::protobuf::Message*                  message;
    const google::protobuf::Reflection*         reflection;
    const google::protobuf::Descriptor*         descriptor;
    const google::protobuf::FieldDescriptor*    field;

























/// ------------------------------------ 
/// ###公共方法
public:
    virtual ~RepeatMessage();//tolua_export
public:
    bool Clear();                               //tolua_export
    bool MergeFrom(RepeatMessageRef other);     //tolua_export
    bool RemoveLast();                          //tolua_export
    bool RemoveAt(int index);                   //tolua_export
    bool Remove(int index);                     //tolua_export
    int Count();                                //tolua_export
    void SetDirty(bool dirty);                  //tolua_export
    google::protobuf::Message* GetMessage();
    /// set
    int Set(lua_State *L);                      //tolua_export
    bool SetInt32(int index, int32_t value);    
    bool SetInt64(int index, int64_t value);    
    bool SetUInt32(int index, uint32_t value);  
    bool SetUInt64(int index, uint64_t value);  
    bool SetFloat(int index, float value);      
    bool SetDouble(int index, double value);    
    bool SetBool(int index, bool value);        
    bool SetNumber(int index, double value);    
    /// get
    int Get(lua_State *L);                      //tolua_export
    int32_t GetInt32(int index);    
    int64_t GetInt64(int index);    
    uint32_t GetUInt32(int index);  
    uint64_t GetUInt64(int index);  
    float GetFloat(int index);      
    double GetDouble(int index);    
    bool GetBool(int index);        
    double GetNumber(int index);    
    /// add
    int Add(lua_State *L);                      //tolua_export
    MessageRef AddMessage();
    bool AddInt32(int32_t value);   
    bool AddInt64(int64_t value);   
    bool AddUInt32(uint32_t value); 
    bool AddUInt64(uint64_t value); 
    bool AddFloat(float value);     
    bool AddDouble(double value);   
    bool AddBool(bool value);       
    bool AddNumber(double value);   
} ;//tolua_export



}//tolua_export
}//tolua_export
