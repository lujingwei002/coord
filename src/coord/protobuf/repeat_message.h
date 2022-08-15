#pragma once 
#include "coord/coordx.h"
#include "coord/protobuf/declare.h"
#include "coord/coordx.h"
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

namespace coord {//tolua_export
namespace protobuf {//tolua_export


class RepeatMessage: public coordx::RcObject {//tolua_export
CC_CLASS(RepeatMessage);
public:
    RepeatMessage(Coord* coord, Message* root, google::protobuf::Message* message, const google::protobuf::FieldDescriptor *field);
    virtual ~RepeatMessage();//tolua_export
public:
    bool Clear();                           //tolua_export
    bool MergeFrom(RepeatMessage* other);   //tolua_export
    bool RemoveLast();              //tolua_export
    bool RemoveAt(int index);       //tolua_export
    bool Remove(int index);         //tolua_export
    int Count();                    //tolua_export
    void SetDirty(bool dirty);      //tolua_export
    /// set
    int Set(lua_State *L);          //tolua_export
    bool SetInt32(int index, int32_t value);    //tolua_export
    bool SetInt64(int index, int64_t value);    //tolua_export
    bool SetUInt32(int index, uint32_t value);  //tolua_export
    bool SetUInt64(int index, uint64_t value);  //tolua_export
    bool SetFloat(int index, float value);      //tolua_export
    bool SetDouble(int index, double value);    //tolua_export
    bool SetBool(int index, bool value);        //tolua_export
    bool SetNumber(int index, double value);    //tolua_export
    /// get
    int Get(lua_State *L);          //tolua_export
    int32_t GetInt32(int index);    //tolua_export
    int64_t GetInt64(int index);    //tolua_export
    uint32_t GetUInt32(int index);  //tolua_export
    uint64_t GetUInt64(int index);  //tolua_export
    float GetFloat(int index);      //tolua_export
    double GetDouble(int index);    //tolua_export
    bool GetBool(int index);        //tolua_export
    double GetNumber(int index);    //tolua_export
    /// add
    int Add(lua_State *L);          //tolua_export
    MessageRef AddMessage();
    bool AddInt32(int32_t value);   //tolua_export
    bool AddInt64(int64_t value);   //tolua_export
    bool AddUInt32(uint32_t value); //tolua_export
    bool AddUInt64(uint64_t value); //tolua_export
    bool AddFloat(float value);     //tolua_export
    bool AddDouble(double value);   //tolua_export
    bool AddBool(bool value);       //tolua_export
    bool AddNumber(double value);   //tolua_export
public:
    Coord*                                      coord;
    Message*                                    root;
    google::protobuf::Message*                  message;
    const google::protobuf::Reflection*         reflection;
    const google::protobuf::Descriptor*         descriptor;
    const google::protobuf::FieldDescriptor*    field;
} ;//tolua_export



}//tolua_export
}//tolua_export
