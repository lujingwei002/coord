#pragma once 

#include <map>
#include <string>

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
public:
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
private:
    Coord* coord;
};//tolua_export

Environment* newEnvironment(Coord* coord);

}//tolua_export
