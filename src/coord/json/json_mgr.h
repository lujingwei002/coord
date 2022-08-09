#pragma once 
#include "coord/builtin/init.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/error.h"
#include "coord/script/declare.h"
#include "coord/json/reflect.h"
#include <string>
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

/// ```c++
///
/// auto json = coorda->Json->Decode(R"({"nickname":"ljw"})");
/// json.GetString("nickname");
///
/// auto object = coorda->Json->NewObject();
///
/// ```
///
///
///
namespace coord {
    class Coord;
}

namespace coord {//tolua_export
namespace json {//tolua_export

class JsonMgr {
CC_CLASS(JsonMgr);
friend class coord::Coord;
friend class coord::script::Script;
private:
    JsonMgr(Coord* coord);
    virtual ~JsonMgr();
private:
    int main();
    /// 将coord::json::Reflect注册到lua中
    int registerMetatable();
private:
    Coord*    coord;





public:
    /// 创建JSON字符串 
    ///
    /// ```
    /// "test"
    /// ```
    ///
    Reflect NewString(const char* data = nullptr);

    /// 创建JSON对象
    ///
    /// ```
    /// {"name": "coord"}
    /// ```
    ///
    Reflect NewObject();

    /// 创建JSON数组
    ///
    /// ```
    /// [1, 2, "3"]
    /// ```
    ///
    Reflect NewArray();

    /// 创建JSON空值
    ///
    /// ```
    /// null
    /// ```
    ///
    Reflect NewNull();

    /// 创建JSON布尔值
    ///
    /// ```
    /// true
    /// ```
    ///
    Reflect NewBool(bool value);

    /// 创建JSON Number值
    ///
    /// ```
    /// true
    /// ```
    ///
    Reflect NewNumber(int value);
    
    /// 创建JSON Number值
    ///
    /// ```
    /// true
    /// ```
    ///
    Reflect NewNumber(double value);

    /// 将字节流中解析成JSON对象
    Reflect Decode(const char* data);

    /// 将字节流中解析成JSON对象
    Reflect Decode(std::string& data);

    /// 将JSON对象序列化成字节流
    int Encode(Reflect& json, byte_slice& buffer);

    /// 将JSON对象序列化成字节流
    int Encode(Reflect& json, std::string& buffer);
};//tolua_export


}//tolua_export
}//tolua_export