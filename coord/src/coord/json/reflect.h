#pragma once 
#include "coord/builtin/init.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/error.h"
#include <json11/json11.hpp>
#include <string>
extern "C"
{
#include <lua/lua.h> 
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}

namespace coord {//tolua_export
class Coord;

namespace json {//tolua_export

class Reflect {//tolua_export
CC_CLASS(Reflect);
public:
    Reflect(Coord* coord, const json11::Json& object);
    Reflect(Coord* coord);
    Reflect(const Reflect& other);
    virtual ~Reflect();
public:
    /// #object.set
    int SetString(const char* key, const char* value);  //tolua_export 
    int SetNumber(const char* key, double value);       //tolua_export 
    int SetInteger(const char* key, int value);         //tolua_export 
    int SetBool(const char* key, bool value);           //tolua_export 
    Reflect SetObject(const char* key);                 //tolua_export   
    Reflect SetArray(const char* key);                  //tolua_export 

    /// #object.get
    const char* GetString(const char* key);             //tolua_export 
    double GetNumber(const char* key);                  //tolua_export 
    int GetInteger(const char* key);                    //tolua_export 
    bool GetBool(const char* key);                      //tolua_export 
    Reflect GetObject(const char* key);                 //tolua_export
    Reflect GetArray(const char* key);                  //tolua_export
    
    /// #object.is
    bool IsObject(const char* key);                      //tolua_export
    bool IsArray(const char* key);                       //tolua_export
    bool IsString(const char* key);                      //tolua_export
    bool IsNumber(const char* key);                      //tolua_export
    bool IsInteger(const char* key);                     //tolua_export
    bool IsNull(const char* key);                        //tolua_export
    bool IsBool(const char* key);                        //tolua_export

    /// #array add   
    Reflect AddObject();
    Reflect AddArray();                 
    int AddNumber(double value);                        //tolua_export
    int AddInteger(int value);                          //tolua_export
    int AddBool(bool value);                            //tolua_export
    int AddString(const char* value);                   //tolua_export

    /// #array get
    const char* GetString(size_t index);   
    double GetNumber(size_t index);         //tolua_export 
    int GetInteger(size_t index);           //tolua_export 
    bool GetBool(size_t index);             //tolua_export
    Reflect GetObject(size_t index);
    Reflect GetArray(size_t index);

    /// #array.is
    bool IsObject(size_t index);                      //tolua_export
    bool IsArray(size_t index);                       //tolua_export
    bool IsString(size_t index);                      //tolua_export
    bool IsNumber(size_t index);                      //tolua_export
    bool IsInteger(size_t index);                     //tolua_export
    bool IsNull(size_t index);                        //tolua_export
    bool IsBool(size_t index);                        //tolua_export
    
    /// #array
    int Count(); 

    /// #self
    bool isObject();                                    //tolua_export
    bool isArray();                                     //tolua_export
    bool isString();                                    //tolua_export
    bool isNumber();                                    //tolua_export
    bool isNull();                                      //tolua_export
    bool isBool();                                      //tolua_export
    
    int Get(lua_State* L);
    int Set(lua_State* L);

    int Encode(byte_slice& buffer);
    int Encode(std::string& buffer);
    const char* ToString();                         //tolua_export    
    Reflect& operator=(const Reflect& other);
    bool operator== (std::nullptr_t v) const;
	bool operator!= (std::nullptr_t v) const;  
public:
    Coord*          coord;
    json11::Json    object;
};//tolua_export

inline bool Reflect::operator== (std::nullptr_t v) const  {
    return this->object.is_null();
}

inline bool Reflect::operator!= (std::nullptr_t v) const  {
    return !this->object.is_null();
}

inline bool Reflect::isObject() {
    return this->object.is_object();
}  

inline bool Reflect::isArray(){
    return this->object.is_array();
}  

inline bool Reflect::isString(){
    return this->object.is_string();
}  

inline bool Reflect::isNumber(){
    return this->object.is_number();
}   

inline bool Reflect::isNull(){
    return this->object.is_null();
}                                                                    

inline bool Reflect::isBool(){
    return this->object.is_bool();
}  

inline int Reflect::SetNumber(const char* key, double value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline double Reflect::GetNumber(const char* key) {
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

inline int Reflect::SetInteger(const char* key, int value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline int Reflect::SetBool(const char* key, bool value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline int Reflect::GetInteger(const char* key) {
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

inline bool Reflect::GetBool(const char* key) {
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

inline int Reflect::SetString(const char* key, const char* value) {
    if (!this->object.is_object()) {
        return ErrorType;
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    dict[key] = json11::Json(value);
    return 0;
}

inline bool Reflect::IsNull(const char* key) {
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

inline bool Reflect::IsBool(const char* key) {
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

inline bool Reflect::IsNumber(const char* key) {
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

inline bool Reflect::IsObject(const char* key) {
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

inline bool Reflect::IsArray(const char* key) {
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

inline bool Reflect::IsString(const char* key) {
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

inline bool Reflect::IsInteger(const char* key) {
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

inline const char* Reflect::GetString(const char* key) {
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

inline Reflect Reflect::GetObject(const char* key) {
    if (!this->object.is_object()) {
        return nullptr;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return Reflect(this->coord);
    }
    if (!it->second.is_object()) {
        return Reflect(this->coord);
    }
    return Reflect(this->coord, it->second);
}

inline Reflect Reflect::GetArray(const char* key) {
    if (!this->object.is_object()) {
        return nullptr;
    }
    const auto& dict = this->object.object_items();
    const auto it = dict.find(key);
    if (it == dict.end()) {
        return Reflect(this->coord);
    }
    if (!it->second.is_array()) {
        return Reflect(this->coord);
    }
    return Reflect(this->coord, it->second);
}

inline Reflect Reflect::SetObject(const char* key) {
    if (!this->object.is_object()) {
        return Reflect(this->coord);
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    json11::Json json = json11::Json(json11::Json::object());
    dict[key] = json;
    return Reflect(this->coord, json);
}

inline Reflect Reflect::SetArray(const char* key) {
    if (!this->object.is_object()) {
        return Reflect(this->coord);
    }
    auto& dict = (json11::Json::object&)this->object.object_items();
    json11::Json json = json11::Json(json11::Json::array());
    dict[key] = json;
    return Reflect(this->coord, json);
}

inline Reflect Reflect::AddObject() {
    if (!this->object.is_array()) {
        return Reflect(this->coord);
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(json11::Json::object());
    arr.push_back(json);
    return Reflect(this->coord, json);
}

inline Reflect Reflect::AddArray() {
    if (!this->object.is_array()) {
        return Reflect(this->coord);
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(json11::Json::array());
    arr.push_back(json);
    return Reflect(this->coord, json);
}

inline int Reflect::AddNumber(double value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Reflect::AddString(const char* value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Reflect::AddBool(bool value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Reflect::AddInteger(int value) {
    if (!this->object.is_array()) {
        return ErrorType;
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    json11::Json json = json11::Json(value);
    arr.push_back(json);
    return 0;
}

inline int Reflect::Count() {
    if (this->object.is_array()) {
        auto& arr = (json11::Json::array&)this->object.array_items();
        return arr.size();
    } else if (this->object.is_object()) {
        auto& object = (json11::Json::object&)this->object.object_items();
        return object.size();
    }
    return 0;
}

inline bool Reflect::IsObject(size_t index) {
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

inline bool Reflect::IsArray(size_t index){
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

inline bool Reflect::IsString(size_t index){
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

inline bool Reflect::IsNumber(size_t index){
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

inline bool Reflect::IsInteger(size_t index){
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

inline bool Reflect::IsNull(size_t index){
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

inline bool Reflect::IsBool(size_t index){
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

inline Reflect Reflect::GetObject(size_t index) {
    if (!this->object.is_array()) {
        return Reflect(this->coord);
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return Reflect(this->coord);
    }
    auto& json = arr.at(index);
    if (!json.is_object()) {
        return Reflect(this->coord);
    }
    return Reflect(this->coord, json);
}

inline Reflect Reflect::GetArray(size_t index) {
    if (!this->object.is_array()) {
        return Reflect(this->coord);
    }
    auto& arr = (json11::Json::array&)this->object.array_items();
    if (index < 0 || index >= arr.size()) {
        return Reflect(this->coord);
    }
    auto& json = arr.at(index);
    if (!json.is_array()) {
        return Reflect(this->coord);
    }
    return Reflect(this->coord, json);
}

inline const char* Reflect::GetString(size_t index) {
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

inline double Reflect::GetNumber(size_t index) {
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

inline int Reflect::GetInteger(size_t index) {
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

inline bool Reflect::GetBool(size_t index) {
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