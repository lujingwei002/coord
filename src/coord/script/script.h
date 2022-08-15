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
#include "coord/script/reflect.h"
namespace coord {//tolua_export

class Coord;

namespace script {//tolua_export

#define LUA_TPROTO      LUA_TTHREAD + 1
#define LUA_TREFERENCE   LUA_TTHREAD + 2
typedef int (*ScriptOpenFunc) (lua_State* L);

#define PACKAGE_MAX 1024

class Script { //tolua_export
public:
    Script(Coord *coord);
    ~Script();
public:
    /// 导入脚本库
    int Import(ScriptOpenFunc func);
    /// 执行脚本文件
    int DoFile(const char* filePath);
    int DoString(const char* buffer);

    /// 获取全局变量
    lua_Number GetNumber(const char *path);
    lua_Number GetNumber(lua_State* L, const char *path);
    /// 获取全局变量
    const char* GetString(const char *path);
    const char* GetString(lua_State* L, const char *path);
    /// 获取全局变量
    bool GetBool(const char *path);
    bool GetBool(lua_State* L, const char *path);
    /// 获取全局变量, 放在栈顶
    int GetFunction(const char *path);
    int GetFunction(lua_State* L, const char *path);
    int GetValue(const char *path);
    int GetValue(lua_State* L, const char *path);
    /// 获取全局变量, 放在栈顶
    int GetTable(const char *path);
    int GetTable(lua_State* L, const char *path);
    /// 获取全局变量
    Reflect Get(const char *path);
    Reflect Get(lua_State* L, const char *path);

    /// #set 不存在的话就自动创建table
    /// 设置全局变量
    int SetNumber(const char *path, lua_Number value);
    int SetNumber(lua_State* L, const char *path, lua_Number value);
    /// 设置全局变量
    int SetString(const char *path, const char* value);
    int SetString(lua_State* L, const char *path, const char* value);
    /// 设置全局变量
    int SetBool(const char *path, bool value);
    int SetBool(lua_State* L, const char *path, bool value);
    /// 设置全局变量
    int SetNil(const char *path);
    /// 设置全局变量
    int SetTable(const char *path);
    /// 将栈里的元素设置到变量中,不弹出元素
    int Set(const char* path, int index);

    bool IsBool(const char* path);
    bool IsString(const char* path);
    bool IsNumber(const char* path);
    bool IsTable(const char* path);
    bool IsNil(const char* path);
    bool IsFunction(const char* path);

    /// 创建一个reflect
    Reflect NewReflect();
    /// 创建匿名table
    Reflect NewTable();
    /// 创建匿名string
    Reflect NewString(const char* value);
    /// 创建匿名number
    Reflect NewNumber(lua_Number value);
    Reflect NewTable(const char* path);
    Reflect NewString(const char* path, const char* value);
    Reflect NewNumber(const char* path, lua_Number value);

    int TraceStack(); 

    /// 将栈顶元素转换成字符串格式
    int ToString(lua_State* L);//tolua_export 
    /// 将栈中第index个元素转换成字符串, 并保存在变量path中 
    const char* ToString(int index, const char* path); 
    const char* ToString(const char* path); 
    /// 将栈中第index个元素转换成字符串
    const char* ToString(int index);
    /// 将栈中第index个元素转换成字符串
    int ToString(int index, byte_slice& buffer);

    int ToShortString(lua_State* L);//tolua_export 
    /// 将栈中第index个元素转换成字符串, 并保存在变量path中
    const char* ToShortString(int index, const char* path); 
    const char* ToShortString(const char* path); 
    /// 将栈中第index个元素转换成字符串
    const char* ToShortString(int index);
    /// 将栈中第index个元素转换成字符串
    int ToShortString(int index, byte_slice& buffer);

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

    /// 序列化成json
    const char* ToJson(const char* path);
    int ToJson(lua_State* L);                               //tolua_export
    const char* ToJson(lua_State* L, int index);
    int ToJson(int index, byte_slice& buffer);

    int FromJson(lua_State* L);                             //tolua_export
    int FromJson(byte_slice& buffer);
    int FromJson(const char* data, size_t len);
    int FromJson(const char* str);
    int FromJson(const char* path, byte_slice& buffer);
    int FromJson(const char* path, const char* data, size_t len);
    int FromJson(const char* path, const char* str);
public:
    void regLib(int (*p)(lua_State* L));
    const char* getTableAndKey(const char *path);
    const char* getTableAndKey(lua_State* L, const char *path);
    int getValue(lua_State* L, const char *path);
    int encode(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& field);
    int tostring(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& space, byte_slice& field, bool isShort);
    int tojson(byte_slice& buffer, lua_State* L, int index, std::map<const void*, std::string>& recordDict, byte_slice& space, byte_slice& field, bool isShort);
    int decode(lua_State* L, const char* data, size_t len);
    int registerLibs();
    int main();
    int onAwake();
    void onDestory();
    void gc();
    int onReload();
    lua_State* getThread(); 
    void freeThread(lua_State* L); 
public:
    char            Path[PACKAGE_MAX+1];  //tolua_export
    char            Main[PACKAGE_MAX+1];  //tolua_export
    lua_State*      L;
    Coord*          coord;
    std::string     lastError;
    void*           jsonParser;

private:
    // 协程
    std::vector<lua_State*> threadArr;
    std::set<lua_State*>    runningThreadSet;
}; //tolua_export

Script* newScript(Coord *coord);
}//tolua_export
} //tolua_export


