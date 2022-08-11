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
class Reflect;
class share_ptr;

class Array : public Destoryable {//tolua_export
CC_CLASS(Array);
public:
    Array(Coord* coord, share_ptr* message, const google::protobuf::FieldDescriptor* field);
    Array(const Array& other);
    Array(Coord* coord);
    virtual ~Array();//tolua_export
public:
    Array& operator=(const Array& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;
    bool Clear();                   //tolua_export
    bool MergeFrom(Array& other);   //tolua_export
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
    Reflect AddMessage();
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
    share_ptr*                                  sharePtr;
    const google::protobuf::FieldDescriptor*    field;
} ;//tolua_export

}//tolua_export
}//tolua_export