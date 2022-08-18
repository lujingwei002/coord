#pragma once 

#include "coord/coordx.h"
#include <unistd.h>
#include <stdint.h>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
#include <map>
#include <set>
#include <string>
#include <any>
#include <initializer_list>
#include "coord/script/reflect.h"
namespace coord {
    class Coord;
}


namespace coord {//tolua_export
namespace script {//tolua_export

#define LUA_TPROTO      LUA_TTHREAD + 1
#define LUA_TREFERENCE   LUA_TTHREAD + 2
typedef int (*ScriptOpenFunc) (lua_State* L);

#define PACKAGE_MAX 1024

class Script { //tolua_export
friend Coord;
private:
    Script(Coord *coord);
public:
    ~Script();
private:
    const char* getTableAndKey(const char *path);
    const char* getTableAndKey(lua_State* L, const char *path);
    /// 获取变量并放在栈顶
    int getValue(lua_State* L, const char *path);
    int encode(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& field);
    int formatDebugString(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& space, byte_slice& field, bool isShort);
    int tojson(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& space, byte_slice& field, bool isShort);
    int decode(lua_State* L, const char* data, size_t len);
    int registerLibs();
    int main();
    int onAwake();
    void onDestory();
    void gc();
    int onReload();
    lua_State* getThread(); 
    
private:
    Coord*          coord;
    std::string     lastError;
    void*           jsonParser;
    // 协程
    std::vector<lua_State*> threadArr;
    std::set<lua_State*>    runningThreadSet;

    
public:
    /// 导入脚本库
    int Import(ScriptOpenFunc func);
    /// 执行脚本文件
    int DoFile(const char* filePath);
    int DoString(const char* buffer);

    /// 将栈里的元素设置到变量中,不弹出元素
    int SetValue(const char* name, int index);
    /// 设置全局变量
    int SetNil(const char* name);
    int SetBool(const char* name, bool value);
    int SetString(const char* name, const char* value);
    int SetNumber(const char* name, lua_Number value);
    int SetTable(const char* name);
    /// 初始化列表支持 int const char*
    int SetTable(const char* name, const std::initializer_list<std::any>& arr);
    //int SetTable(const char* name, const std::initializer_list<const char*>& arr);
    int SetGlobal(const char* name, const char* value);
    int SetGlobal(const char* name, const std::initializer_list<std::any>& arr);
   // int SetGlobal(const char* name, const std::initializer_list<const char*>& arr);

    /// 获取全局变量
    lua_Number GetNumber(const char *name);
    const char* GetString(const char *name);
    bool GetBool(const char *name);
    /// 获取全局变量, 放在栈顶
    int GetFunction(const char *path);
    int GetFunction(lua_State* co, const char *name);
    int GetValue(const char *name);
    int GetValue(lua_State* L, const char *name);

    /// 判断全局变量类型
    bool IsBool(const char* name);
    bool IsString(const char* name);
    bool IsNumber(const char* name);
    bool IsTable(const char* name);
    bool IsFunction(const char* name);
    bool IsNil(const char* name);

    /// 获取变量
    Reflect NewReflect(const char *name = nullptr);
    Reflect NewVariable(const char *name);
    Reflect NewVariable(const char *name, const char* value);
    Reflect GetVariable(const char *name);

    int TraceStack(); 

    /// 将栈顶元素转换成字符串格式
    int DebugString(lua_State* L);//tolua_export 
    /// 将栈中第index个元素转换成字符串, 并保存在变量name中 
    const char* DebugString(int index, const char* name); 
    /// 将变量转换成字符串
    const char* DebugString(const char* name); 
    /// 将栈中第index个元素转换成字符串
    const char* DebugString(int index);
    /// 将栈中第index个元素转换成字符串
    int DebugString(int index, byte_slice& buffer);

    /// 将栈顶元素转换成字符串格式
    int ShortDebugString(lua_State* L);//tolua_export 
    /// 将栈中第index个元素转换成字符串, 并保存在变量name中
    const char* ShortDebugString(int index, const char* name); 
    /// 将变量转换成字符串
    const char* ShortDebugString(const char* name); 
    /// 将栈中第index个元素转换成字符串
    const char* ShortDebugString(int index);
    /// 将栈中第index个元素转换成字符串
    int ShortDebugString(int index, byte_slice& buffer);

    /// 将栈顶元素序列化成二进制
    int Encode(lua_State* L);                                //tolua_export 
    /// 将path变量序列化成二进制
    int Encode(const char* path, byte_slice& buffer);
    /// 将栈第index个元素序列化成二进制
    int Encode(int index, byte_slice& buffer); 
    
    /// 反序列化，成功的话元素放在栈顶
    int Decode(lua_State* L);                              //tolua_export
    /// 反序列化，成功的话元素保存在path中
    int Decode(const char* path, byte_slice& buffer);
    /// 反序列化，成功的话元素保存在path中
    int Decode(const char* path, const char* data, size_t len);
    /// 反序列化，成功的话元素放在栈顶
    int Decode(byte_slice& buffer);
    /// 反序列化，成功的话元素放在栈顶
    int Decode(const char* data, size_t len);

    const char* GetLastError();

    /// 将变量转为json字符串
    const char* ToJson(const char* name);
    /// 将栈顶元素转为json字符串
    int ToJson(lua_State* L);                               //tolua_export
    /// 将栈上的变量序列化成json字符串
    const char* ToJson(lua_State* L, int index);
    /// 将栈上的变量序列化成json字符串
    int ToJson(int index, byte_slice& buffer);
    int ToJson(lua_State* L, int index, byte_slice& buffer);


    int FromJson(lua_State* L);                             //tolua_export
    int FromJson(byte_slice& buffer);
    int FromJson(const char* data, size_t len);
    int FromJson(const char* str);
    int FromJson(const char* name, byte_slice& buffer);
    int FromJson(const char* name, const char* data, size_t len);
    int FromJson(const char* name, const char* str);

    /// 释放协程，暂时设置为导出方法。TODO
    void FreeThread(lua_State* co); 
public:
    char            Path[PACKAGE_MAX+1];  //tolua_export
    char            Main[PACKAGE_MAX+1];  //tolua_export
    lua_State*      L;
}; //tolua_export



int lua_pushany(lua_State* L, const std::any& value);

}//tolua_export
} //tolua_export


