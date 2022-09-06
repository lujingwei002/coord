#pragma once 
#include "coord/coordx.h"
#include "coord/memory/type.h"
#include "coord/json/declare.h"
#include <json11/json11.hpp>
#include <string>
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

///
///
/// 内存, C++是在栈中， 由作用域管理内存。LUA是在堆中，由GC管理内存。
/// json11::Json本身有引用计算。
///  
/// 栈中 c++ ref1 ---> json11:Json
///
/// 堆中 lua ref2----------↑
///

namespace coord {
    class Coord;
}

namespace coord {//tolua_export
namespace json {//tolua_export

class Json : public coord::RcObject {//tolua_export
RC_CLASS(Json);
friend coord::json::JsonMgr;
private:
    Json(Coord* coord, const json11::Json& object);
    Json(Coord* coord);
private:
     int set(lua_State* L, json11::Json& object, int index);
    json11::Json lua_toobject(lua_State* L, int index);
private:
    Coord*          coord;
    // json11:Json  本身有引用计算了
    json11::Json    object;



public:
    virtual ~Json();                                    //tolua_export 
public:
    /// #object.set
    int SetString(const char* key, const char* value);  //tolua_export 
    int SetNumber(const char* key, double value);       //tolua_export 
    int SetInteger(const char* key, int value);         //tolua_export 
    int SetBool(const char* key, bool value);           //tolua_export 
    JsonRef SetObject(const char* key);                 //tolua_export   
    JsonRef SetArray(const char* key);                  //tolua_export 

    /// #object.get
    const char* GetString(const char* key);             //tolua_export 
    double GetNumber(const char* key);                  //tolua_export 
    int GetInteger(const char* key);                    //tolua_export 
    bool GetBool(const char* key);                      //tolua_export 
    JsonRef GetObject(const char* key);                 //tolua_export
    JsonRef GetArray(const char* key);                  //tolua_export
    
    /// #object.is
    bool IsObject(const char* key);                      //tolua_export
    bool IsArray(const char* key);                       //tolua_export
    bool IsString(const char* key);                      //tolua_export
    bool IsNumber(const char* key);                      //tolua_export
    bool IsInteger(const char* key);                     //tolua_export
    bool IsNull(const char* key);                        //tolua_export
    bool IsBool(const char* key);                        //tolua_export

    /// #array add   
    JsonRef AddObject();
    JsonRef AddArray();                 
    int AddNumber(double value);                        //tolua_export
    int AddInteger(int value);                          //tolua_export
    int AddBool(bool value);                            //tolua_export
    int AddString(const char* value);                   //tolua_export

    /// #array get
    const char* GetString(size_t index);   
    double GetNumber(size_t index);                     //tolua_export 
    int GetInteger(size_t index);                       //tolua_export 
    bool GetBool(size_t index);                         //tolua_export
    JsonRef GetObject(size_t index);
    JsonRef GetArray(size_t index);

    /// #array.is
    bool IsObject(size_t index);                        //tolua_export
    bool IsArray(size_t index);                         //tolua_export
    bool IsString(size_t index);                        //tolua_export
    bool IsNumber(size_t index);                        //tolua_export
    bool IsInteger(size_t index);                       //tolua_export
    bool IsNull(size_t index);                          //tolua_export
    bool IsBool(size_t index);                          //tolua_export
    
    /// #array
    int Count(); 

    /// #self
    bool isObject();                                    //tolua_export
    bool isArray();                                     //tolua_export
    bool isString();                                    //tolua_export
    bool isNumber();                                    //tolua_export
    bool isNull();                                      //tolua_export
    bool isBool();                                      //tolua_export
    
    int Get(lua_State* L);                              //tolua_export

    /// 
    /// 支持number, boolean, string, jsonref, table, array类型
    /// 支持在数组，字典里嵌套其他类型
    ///
    /// {1, a = b} 数组和字典都有的情况下，会忽略字典部分
    /// 如果self是数组的情况下， 下标从0开始， 如果下标超过数组的大小，数组大小会扩展，值为null
    ///
    int Set(lua_State* L);                              //tolua_export

   

    int Dump(byte_slice& buffer);
    int Dump(std::string& buffer);
    const char* ToString();                             //tolua_export    
};//tolua_export


inline bool Json::isObject() {
    return this->object.is_object();
}  

inline bool Json::isArray(){
    return this->object.is_array();
}  

inline bool Json::isString(){
    return this->object.is_string();
}  

inline bool Json::isNumber(){
    return this->object.is_number();
}   

inline bool Json::isNull(){
    return this->object.is_null();
}                                                                    

inline bool Json::isBool(){
    return this->object.is_bool();
}  

inline int Json::SetNumber(const char* key, double value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline double Json::GetNumber(const char* key) {
    if (!this->object.is_object()) {
        return 0;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return 0;
    }
    if (!it->second.number_value()) {
        return false;
    }
    return it->second.number_value();
}

inline int Json::SetInteger(const char* key, int value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline int Json::SetBool(const char* key, bool value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline int Json::GetInteger(const char* key) {
    if (!this->object.is_object()) {
        return 0;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return 0;
    }
    if (!it->second.int_value()) {
        return false;
    }
    return it->second.int_value();
}

inline bool Json::GetBool(const char* key) {
    if (!this->object.is_object()) {
        return 0;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return 0;
    }
    if (!it->second.is_bool()) {
        return false;
    }
    return it->second.bool_value();
}

inline int Json::SetString(const char* key, const char* value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline bool Json::IsNull(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_null();
}

inline bool Json::IsBool(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_bool();
}

inline bool Json::IsNumber(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_number();
}

inline bool Json::IsObject(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_object();
}

inline bool Json::IsArray(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_array();
}

inline bool Json::IsString(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_string();
}

inline bool Json::IsInteger(const char* key) {
    if (!this->object.is_object()) {
        return false;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return false;
    }
    return it->second.is_number();
}

inline const char* Json::GetString(const char* key) {
    if (!this->object.is_object()) {
        return nullptr;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return nullptr;
    }
    if (!it->second.is_string()) {
        return nullptr;
    }
    return it->second.string_value().c_str();
}

inline JsonRef Json::GetObject(const char* key) {
    if (!this->object.is_object()) {
        return nullptr;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return JsonRef::NullPtr;
    }
    if (!it->second.is_object()) {
        return JsonRef::NullPtr;
    }
    return new Json(this->coord, it->second);
}

inline JsonRef Json::GetArray(const char* key) {
    if (!this->object.is_object()) {
        return nullptr;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return JsonRef::NullPtr;
    }
    if (!it->second.is_array()) {
        return JsonRef::NullPtr;
    }
    return new Json(this->coord, it->second);
}

inline JsonRef Json::SetObject(const char* key) {
    if (!this->object.is_object()) {
        return JsonRef::NullPtr;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    json11::Json json = json11::Json(json11::Json::object());
    dict[key] = json;
    return new Json(this->coord, json);
}

inline JsonRef Json::SetArray(const char* key) {
    if (!this->object.is_object()) {
        return JsonRef::NullPtr;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    json11::Json json = json11::Json(json11::Json::array());
    dict[key] = json;
    return new Json(this->coord, json);
}

inline JsonRef Json::AddObject() {
    if (!this->object.is_array()) {
        return JsonRef::NullPtr;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(json11::Json::object());
    arr.push_back(json);
    return new Json(this->coord, json);
}

inline JsonRef Json::AddArray() {
    if (!this->object.is_array()) {
        return JsonRef::NullPtr;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(json11::Json::array());
    arr.push_back(json);
    return new Json(this->coord, json);
}

inline int Json::AddNumber(double value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Json::AddString(const char* value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Json::AddBool(bool value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Json::AddInteger(int value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Json::Count() {
    if (this->object.is_array()) {
        auto& arr = (json11::Json::array&)this->object.array_items();
        return arr.size();
    } else if (this->object.is_object()) {
        auto& object = (json11::Json::object&)this->object.object_items();
        return object.size();
    }
    return 0;
}

inline bool Json::IsObject(size_t index) {
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_object();
}

inline bool Json::IsArray(size_t index){
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_array();
}   

inline bool Json::IsString(size_t index){
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_string();
}   

inline bool Json::IsNumber(size_t index){
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_number();
}

inline bool Json::IsInteger(size_t index){
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_number();
}

inline bool Json::IsNull(size_t index){
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_null();
}    

inline bool Json::IsBool(size_t index){
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    auto& json = arr.at(index);
    return json.is_bool();
}                        

inline JsonRef Json::GetObject(size_t index) {
    if (!this->object.is_array()) {
        return JsonRef::NullPtr;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return JsonRef::NullPtr;
    }
    auto& json = arr.at(index);
    if (!json.is_object()) {
       return JsonRef::NullPtr;
    }
    return new Json(this->coord, json);
}

inline JsonRef Json::GetArray(size_t index) {
    if (!this->object.is_array()) {
        return JsonRef::NullPtr;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return JsonRef::NullPtr;
    }
    auto& json = arr.at(index);
    if (!json.is_array()) {
        return JsonRef::NullPtr;
    }
    return new Json(this->coord, json);
}

inline const char* Json::GetString(size_t index) {
    if (!this->object.is_array()) {
        return nullptr;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return nullptr;
    }
    const auto& json = arr.at(index);
    if (!json.is_string()) {
        return nullptr;
    }
    return json.string_value().c_str();
}

inline double Json::GetNumber(size_t index) {
    if (!this->object.is_array()) {
        return 0;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return 0;
    }
    const auto& json = arr.at(index);
    if (!json.is_number()) {
        return 0;
    }
    return json.number_value();
}

inline int Json::GetInteger(size_t index) {
    if (!this->object.is_array()) {
        return 0;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return 0;
    }
    const auto& json = arr.at(index);
    if (!json.is_number()) {
        return 0;
    }
    return json.int_value();
}

inline bool Json::GetBool(size_t index) {
    if (!this->object.is_array()) {
        return false;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return false;
    }
    const auto& json = arr.at(index);
    if (!json.is_bool()) {
        return false;
    }
    return json.bool_value();
}

}//tolua_export
}//tolua_export
