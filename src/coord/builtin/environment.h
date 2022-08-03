#pragma once 

#include <uv.h>
#include <map>
#include <string>
#include <optional>
#include <algorithm>
#include <cctype>
#include <functional>
#include <cstring>
#include <iostream>
#include <list>
#include <locale>
#include <sstream>
extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <tolua++/tolua++.h>
}
namespace coord {//tolua_export

class Coord;
class Argv;

class Environment {//tolua_export
friend class Coord;
private:
    Environment(Coord* coord) {
        this->coord = coord;
        this->Version = "0.0.1";
    }
    ~Environment() {
    }
public:
    /// 打印调试信息
    void DebugString();

    /// 获取变量
    /// @param name 变量名
    /// @param value 返回的变量值
    /// @param defaultValue 如果变量不存在,就取默认值
    /// @return 值存在返回true, 不存在则返回false
    template <typename T>
    bool Get(const std::string& name, T& dst);

    /// 获取变量
    /// @param name 变量名
    /// @param value 返回的变量值
    /// @param defaultValue 如果变量不存在,就取默认值
    /// @return 值存在返回true, 不存在则返回false
    template <typename T, typename T2>
    bool Get(const std::string& name, T& value, T2 defaultValue);

    int Get(lua_State* L); //tolua_export
public:
    /// coord版本号
    std::string Version;//tolua_export
    /// 执行文件路径
    std::string ExecPath;//tolua_export
    /// 执行文件目录
    std::string ExecDir;//tolua_export
    /// 项目目录
    std::string ProjectDir;//tolua_export
    /// 工作目录
    std::string WorkingDir;//tolua_export
    /// 用户目录
    std::string HomeDir;//tolua_export
    /// coord所有目录
    std::string CoordDir;//tolua_export
    /// 配置文件路径
    std::string ConfigPath;//tolua_export
    /// 配置文件目录
    std::string ConfigDir;//tolua_export
    /// 包查找路径, 以分号分隔
    std::string Package;//tolua_export
    /// proc目录
    std::string ProcDir;//tolua_export
    /// run目录
    std::string RunDir;//tolua_export
    /// pid文件路径
    std::string PidPath;//tolua_export
    /// 服务的名字
    std::string Name;//tolua_export
    /// managed的unix socket路径
    std::string ManagedSockPath; //tolua_export
    /// 环境变量字典
    std::map<std::string, std::string> Variables;

    uv_pid_t    Pid;
private:
    int main(const Argv& argv);
    int searchCoordDir(std::string& coordDir);
    template <typename T>
    bool extract(const std::string & value, T & dst);
    bool extract(const std::string & value, std::string & dst) {
        dst = value;
        return true;
    }
    int scanEnvFile(const std::string& envFilePath);
    int scanEnvMultiLine(const std::string& envFilePath, char* data, size_t size);
    int scanEnvLine(const std::string& envFilePath, char* data, size_t size);
    int scanEnvDirectiveLine(const std::string& envFilePath, char* data, size_t size);
    int scanEnvKey(char* lines, size_t size);
    int scanEnvValue(char* lines, size_t size);
    int scanEnvQuoteValue(char* lines, size_t size);
    int gotEnvKey(char* data, size_t size);
    int gotEnvValue(char* data, size_t size);
    int gotEnvLineError(const std::string& envFilePath, int lineNum, char* data, size_t size);
private:
    Coord* coord;
};//tolua_export

//Environment* newEnvironment(Coord* coord);

template <typename T>
bool Environment::Get(const std::string& name, T& dst) {
    auto it = this->Variables.find(name);
    if (it == this->Variables.end()) {
        return false;
    }
    return this->extract(it->second, dst);
}
template <typename T, typename T2>
bool Environment::Get(const std::string& name, T& dst, T2 defaultValue) {
    auto it = this->Variables.find(name);
    if (it == this->Variables.end()) {
        dst = defaultValue;
        return true;
    }
    return this->extract(it->second, dst);

}
template <typename T>
bool Environment::extract(const std::string& value, T & dst) {
    char c;
    std::istringstream is{ value };
    T result;
    if ((is >> std::boolalpha >> result) && !(is >> c)) {
        dst = result;
        return true;
    }
    else {
        return false;
    }
}


}//tolua_export
