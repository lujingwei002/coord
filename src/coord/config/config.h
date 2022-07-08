#pragma once 

#include "inipp/inipp.h"
#include "coord/gate/gate_config.h"
#include "coord/cluster/cluster_config.h"
#include "coord/cache/cache_config.h"
#include "coord/web/web_config.h"
#include "coord/login/login_config.h"
#include "coord/managed/managed_config.h"
#include <string>
#include <iostream>
#include <sstream>

namespace coord {//tolua_export

namespace sql {
class SQLConfig;
}
namespace redis {
class RedisConfig;
}
namespace log4cc {
class LoggerConfig;
}
class Coord;

class BasicConfig {//tolua_export
public:
    std::string         Env;                //tolua_export
    /// 脚本的主模块, 必须声明为_package_('main')
    std::string         Main;               //tolua_export
    /// 脚本的主场景构造文件
    std::string         Scene;              //tolua_export
    std::string         Registery;          //tolua_export
    /// 包查找路径,使用分号分隔
    std::string         Package;            //tolua_export
    uint16_t            GC;                 //tolua_export
    uint16_t            Update;             //tolua_export
    /// worker的配置文件
    std::string         Worker;             //tolua_export
    /// 开启worker的数量
    uint16_t            WorkerNum;          //tolua_export
    /// proto文件目录
    std::string         Proto;              //tolua_export
    /// 节点名字
    std::string         Name;               //tolua_export
    /// 保存pid文件的目录
    std::string         Pid;                //tolua_export
    /// 版本
    std::string         Version;            //tolua_export
    /// 短版本
    std::string         ShortVersion;       //tolua_export
    std::string         ProcDir;
};//tolua_export

class Config {//tolua_export
    friend class Coord;
private:
    Config(Coord* coord);
    ~Config();
public:
    /// 获取SQL配置
    int SQLConfig(const std::string& section, sql::SQLConfig* config);

    /// 获取Redis配置
    int RedisConfig(const std::string& section, redis::RedisConfig* config);

    /// 获取Logger配置
    int LoggerConfig(const std::string& section, log4cc::LoggerConfig* config);

    /// 配置分组是否存在
    bool SectionExist(const std::string& section);

    /// 获取配置值
    template <typename T>
    bool Get(const std::string& section, const std::string& key, T& dst); 

    /// 获取配置值
    template <typename T, typename T2>
    bool Get(const std::string& section, const std::string& key, T& dst, T2 defaultValue);

    /// 获取配置值
    template <typename T>
    bool Get(const std::string& path, T& dst); 

    /// 输出调试信息
    void DebugString();
public:
    BasicConfig             Basic;      //tolua_export
    web::WebConfig          Web;        //tolua_export
    gate::GateConfig        Gate;       //tolua_export
    cache::CacheConfig      Cache;      //tolua_export
    cluster::ClusterConfig  Cluster;    //tolua_export
    managed::ManagedConfig  Managed;    //tolua_export
    login::LoginConfig      Login;      //tolua_export
    std::map<std::string, std::map<std::string, std::string>> Sections;

private:
/// 获取配置值
    template <typename T, typename T2>
    bool get(std::map<std::string, std::string> section, const std::string& key, T& dst, T2 defaultValue);

    /// 获取配置值
    template <typename T>
    bool get(std::map<std::string, std::string> section, const std::string& key, T& dst);

    template <typename T>
    bool extract(const std::string & value, T & dst);
    bool extract(const std::string & value, std::string & dst) {
        dst = value;
        return true;
    }
    int scanConfigFile(const std::string& configPath);
    int scanConfigMultiLine(const std::string& configPath, char* lines, size_t size);
    int scanConfigLine(const std::string& configPath, char* data, size_t size);
    int scanConfigDirectiveLine(const std::string& configPath, char* data, size_t size);
    int scanConfigSectionLine(char* data, size_t size);
    int scanConfigKey(char* lines, size_t size);
    int scanConfigValue(char* lines, size_t size);
    int scanConfigQuoteValue(char* lines, size_t size);
    int gotConfigKey(char* data, size_t size);
    int gotConfigValue(char* data, size_t size);
    int gotConfigQuoteValue(char* data, size_t size);
    int gotConfigSection(char* data, size_t size);
    int gotConfigLineError(const std::string& configPath, int lineNum, char* data, size_t size);
    int urlParse(const char* path, std::string& section, std::string& key);
    int urlParse(const char* data, size_t size, std::string& section, std::string& key);
    int parse(const char* filePath);
private:
    Coord*                  coord;      
};//tolua_export

//Config *newConfig(Coord* coord);

template <typename T>
bool Config::Get(const std::string& path, T& dst) {
    std::string section;
    std::string key;
    int err = this->urlParse(path.c_str(), path.length(), section, key);
    if (err) {
        return false;
    }
    return this->Get(section.c_str(), key, dst);
} 

template <typename T>
bool Config::Get(const std::string& section, const std::string& key, T& dst) {
    auto it = this->Sections.find(section);
    if (it == this->Sections.end()) {
        return false;
    }
    auto kv = it->second;
    auto it2 = kv.find(key);
    if (it2 == kv.end()) {
        return false;
    }
    return this->extract(it2->second, dst);
}
template <typename T, typename T2>
bool Config::Get(const std::string& section, const std::string& key, T& dst, T2 defaultValue) {
    auto it = this->Sections.find(section);
    if (it == this->Sections.end()) {
        return false;
    }
    auto kv = it->second;
    auto it2 = kv.find(key);
    if (it2 == kv.end()) {
        dst = defaultValue;
        return true;
    }
    return this->extract(it2->second, dst);
}
template <typename T, typename T2>
bool Config::get(std::map<std::string, std::string> section, const std::string& key, T& dst, T2 defaultValue) {
    auto it = section.find(key);
    if (it == section.end()) {
        dst = defaultValue;
        return true;
    }
    return this->extract(it->second, dst);
}

template <typename T>
bool Config::get(std::map<std::string, std::string> section, const std::string& key, T& dst) {
    auto it = section.find(key);
    if (it == section.end()) {
        return false;
    }
    return this->extract(it->second, dst);
}

template <typename T>
bool Config::extract(const std::string & value, T & dst) {
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
