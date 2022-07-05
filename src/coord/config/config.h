#pragma once 

#include "inipp/inipp.h"
#include "coord/gate/gate_config.h"
#include "coord/cluster/cluster_config.h"
#include "coord/cache/cache_config.h"
#include "coord/web/web_config.h"
#include "coord/login/login_config.h"
#include "coord/managed/managed_config.h"
#include <string>

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
};//tolua_export

class Config {//tolua_export
public:
    Config(Coord* coord);
public:
    int SQLConfig(const char* section, sql::SQLConfig* config);
    int RedisConfig(const char* section, redis::RedisConfig* config);
    int LoggerConfig(const char* section, log4cc::LoggerConfig* config);
    bool SectionExist(const char* section);
    template <typename T>
    bool Get(const char* section, const char* key, T& dst) {
        return this->extract(this->Sections[section][key], dst);
    }
    void DebugString();
private:
    template <typename CharT, typename T>
    bool extract(const std::basic_string<CharT> & value, T & dst) {
        CharT c;
        std::basic_istringstream<CharT> is{ value };
        T result;
        if ((is >> std::boolalpha >> result) && !(is >> c)) {
            dst = result;
            return true;
        }
        else {
            return false;
        }
    }
    template <typename CharT>
    bool extract(const std::basic_string<CharT> & value, std::basic_string<CharT> & dst) {
        dst = value;
        return true;
    }
private:
    int scanConfigFile(const std::string& configFilePath);
    int scanConfigMultiLine(const std::string& configFilePath, char* lines, size_t size);
    int scanConfigLine(const std::string& configFilePath, char* data, size_t size);
    int scanConfigDirectiveLine(const std::string& configFilePath, char* data, size_t size);
    int scanConfigSectionLine(char* data, size_t size);
    int scanConfigKey(char* lines, size_t size);
    int scanConfigValue(char* lines, size_t size);
    int scanConfigQuoteValue(char* lines, size_t size);
    int gotConfigKey(char* data, size_t size);
    int gotConfigValue(char* data, size_t size);
    int gotConfigQuoteValue(char* data, size_t size);
    int gotConfigSection(char* data, size_t size);
    int gotConfigLineError(const std::string& configFilePath, int lineNum, char* data, size_t size);
public:
    int parse(const char* filePath);
public:
    std::map<std::string, std::map<std::string, std::string>> Sections;
    //inipp::Ini<char>        ini;        //tolua_export
    Coord*                  coord;      //tolua_export
    BasicConfig             Basic;      //tolua_export
    web::WebConfig          Web;        //tolua_export
    gate::GateConfig        Gate;       //tolua_export
    cache::CacheConfig      Cache;      //tolua_export
    cluster::ClusterConfig  Cluster;    //tolua_export
    managed::ManagedConfig  Managed;    //tolua_export
    login::LoginConfig      Login;      //tolua_export
};//tolua_export

Config *newConfig(Coord* coord);

}//tolua_export
