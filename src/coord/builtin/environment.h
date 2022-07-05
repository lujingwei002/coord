#pragma once 

#include <map>
#include <string>
#include <optional>

namespace coord {//tolua_export

class Coord;

class Environment {//tolua_export
public:
    Environment(Coord* coord) {
        this->coord = coord;
        this->Version = "0.0.1";
    }
    ~Environment() {
    }
    void DebugString();
public:
    std::optional<std::string> GetString(const char* name);
    int main(const char* configFilePath);
    int searchCoordDir(char* buffer, size_t* len);
public:
    std::string Version;//tolua_export
    // 执行文件路径
    std::string ExecPath;//tolua_export
    // 执行文件目录
    std::string ExecDir;//tolua_export
    // 项目目录
    std::string ProjectDir;//tolua_export
    // 工作目录
    std::string WorkingDir;//tolua_export
    // 用户目录
    std::string HomeDir;//tolua_export
    //
    std::string CoordDir;//tolua_export
    // 配置文件路径
    std::string ConfigFilePath;//tolua_export
    // 配置文件目录
    std::string ConfigFileDir;//tolua_export
    // 包查找路径, 以分号分隔
    std::string Package;//tolua_export
    std::map<std::string, std::string> Variables;
private:
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

Environment* newEnvironment(Coord* coord);

}//tolua_export
