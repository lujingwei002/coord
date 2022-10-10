#pragma once 
#include "coord/coordx.h"
#include "coord/coordx.h"
#include "coord/coordx.h"
#include "coord/script/declare.h"
#include "coord/json/json.h"
#include <string>
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

/// ```c++
///
/// auto json = coorda->Json->Parse(R"({"nickname":"ljw"})");
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

class JsonMgr { //tolua_export
COORD_CLASS(JsonMgr);
friend class coord::Coord;
friend class coord::script::Script;
private:
    JsonMgr(Coord* coord);
    virtual ~JsonMgr();
private:
    int main();
    /// 将coord::json::JsonRef注册到lua中
    int registerMetatable();
private:
    Coord*    coord;





public:
    /// 创建JSON空值
    ///
    /// ```
    /// null
    /// ```
    ///
    JsonRef NewNull();                              //tolua_export

    /// 创建JSON字符串 
    ///
    /// ```
    /// "test"
    /// ```
    ///
    JsonRef NewString(const char* data = nullptr);  //tolua_export

    /// 创建JSON对象
    ///
    /// ```
    /// {"name": "coord"}
    /// ```
    ///
    JsonRef NewObject();                            //tolua_export

    /// 创建JSON数组
    ///
    /// ```
    /// [1, 2, "3"]
    /// ```
    ///
    JsonRef NewArray();                             //tolua_export

    /// 创建JSON布尔值
    ///
    /// ```
    /// true
    /// ```
    ///
    JsonRef NewBool(bool value);                    //tolua_export

    /// 创建JSON Number值
    ///
    /// ```
    /// true
    /// ```
    ///
    JsonRef NewNumber(int value);                   //tolua_export    
    
    /// 创建JSON Number值
    ///
    /// ```
    /// true
    /// ```
    ///
    JsonRef NewNumber(double value);                //tolua_export

    /// 将字节流中解析成JSON对象
    JsonRef Parse(const char* data);

    /// 将字节流中解析成JSON对象
    JsonRef Parse(const std::string& data);

    /// 将JSON对象序列化成字节流
    int Dump(JsonRef& json, byte_slice& buffer);

    /// 将JSON对象序列化成字节流
    int Dump(JsonRef& json, std::string& buffer);
};//tolua_export


JsonRef NewObject();
JsonRef Parse(const std::string& data);
JsonRef NewArray();                             
JsonRef NewString(const char* data = nullptr);
JsonRef NewNull();
JsonRef NewBool(bool value);


}//tolua_export
}//tolua_export
