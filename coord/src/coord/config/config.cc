#include "coord/config/config.h"
#include "coord/log/log.h"
#include "coord/sql/sql_client.h"
#include "coord/redis/redis_client.h"
#include "coord/builtin/init.h"
#include "inipp/inipp.h"
#include <fstream>
#include <iostream>

namespace coord {

template <typename CharT, typename T>
inline bool get_value(const std::map<std::basic_string<CharT>, std::basic_string<CharT>> & sec, const std::basic_string<CharT> & key, T & dst) {
    const auto it = sec.find(key);
    if (it == sec.end()) return false;
    return inipp::extract(it->second, dst);
}

template <typename CharT, typename T>
inline bool get_value(const std::map<std::basic_string<CharT>, std::basic_string<CharT>>& sec, const CharT* key, T& dst) {
    return get_value(sec, std::basic_string<CharT>(key), dst);
}


Config *newConfig(Coord* coord) {
    Config *config = new Config(coord);
    return config;
}

Config::Config(Coord* coord) {
    this->coord = coord;

    this->Basic.GC = 0;
    this->Basic.Update = 100;
    this->Basic.WorkerNum = 0;
    this->Basic.CoreLoggerMaxByte = 4*1024*1024;
    this->Basic.CoreLogger = "./";
    this->Basic.LoggerMaxByte = 4*1024*1024;
    this->Basic.Logger = "./";
    this->Basic.Pid = "./";
    this->Basic.Version = "0.0.0";
    
    this->Web.Port = 0;
    this->Web.Backlog = 1024;
    this->Web.RecvBuffer = 4096;
    this->Web.SSLEncrypt = false;
    this->Web.AssetDir = "./";
    this->Web.UseEtag = true;

    this->Gate.ServerName = "127.0.0.1";
    this->Gate.Port = 0;
    this->Gate.Network = "tcp";
    this->Gate.RsaEncrypt = false;
    this->Gate.Heartbeat = 60000;
    this->Gate.Backlog = 1024;
    this->Gate.RecvBuffer = 4096;
    this->Gate.SSLEncrypt = false;
    this->Gate.MaxUser = 10000;
    this->Gate.MaxConnection = 20000;
    this->Gate.UserRegisterExpire = 60;
    this->Gate.UserRegisterInterval = 30;
    this->Gate.RegisterExpire = 60;
    this->Gate.RegisterInterval = 30;

    this->Cluster.Heartbeat = 30;
    this->Cluster.Expire = 60;
    this->Cluster.RegisterInterval = 60;
    this->Cluster.ReloadInterval = 60;
    this->Cluster.ReconnectInterval = 30;
    this->Cluster.RecvBuffer = 4096;
}

int Config::parse(const char* filePath) {
    std::ifstream is(filePath);
    if(!is.is_open()){
        printf("config file not found, %s\n", filePath);
        return 1;
    }
    this->ini.parse(is);
    if(this->ini.errors.size() > 0){
        printf("parse config file failed %s\n", filePath);
        for(auto const &error : this->ini.errors){
            std::cout << error << std::endl;
        }
        return 1;
    }
    get_value(this->ini.sections["DEFAULT"], "registery", this->Basic.Registery);
    get_value(this->ini.sections["DEFAULT"], "main", this->Basic.Main);
    get_value(this->ini.sections["DEFAULT"], "scene", this->Basic.Scene);
    get_value(this->ini.sections["DEFAULT"], "package", this->Basic.Package);
    get_value(this->ini.sections["DEFAULT"], "gc", this->Basic.GC);
    get_value(this->ini.sections["DEFAULT"], "update", this->Basic.Update);
    get_value(this->ini.sections["DEFAULT"], "worker", this->Basic.Worker);
    get_value(this->ini.sections["DEFAULT"], "worker_num", this->Basic.WorkerNum);
    get_value(this->ini.sections["DEFAULT"], "proto", this->Basic.Proto);
    get_value(this->ini.sections["DEFAULT"], "name", this->Basic.Name);
    get_value(this->ini.sections["DEFAULT"], "core_logger", this->Basic.CoreLogger);
    get_value(this->ini.sections["DEFAULT"], "core_logger_maxbyte", this->Basic.CoreLoggerMaxByte);
    get_value(this->ini.sections["DEFAULT"], "logger", this->Basic.Logger);
    get_value(this->ini.sections["DEFAULT"], "logger_maxbyte", this->Basic.LoggerMaxByte);
    get_value(this->ini.sections["DEFAULT"], "pid", this->Basic.Pid);
    get_value(this->ini.sections["DEFAULT"], "version", this->Basic.Version);
    int first = 0;
    auto it = std::find_if(this->Basic.Version.begin(), this->Basic.Version.end(), [&first](char c) {
        if (c == '.')first++;
        return first >= 2;
    });
    if (it == this->Basic.Version.end()) {
        return -1;
    }
    this->Basic.ShortVersion = this->Basic.Version.substr(0, it - this->Basic.Version.begin());


    if(this->ini.sections.find("WEB") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("WEB");
        get_value(it->second, "port", this->Web.Port);
        get_value(it->second, "host", this->Web.Host);
        get_value(it->second, "backlog", this->Web.Backlog);
        get_value(it->second, "recv_buffer", this->Web.RecvBuffer);
        get_value(it->second, "ssl_encrypt", this->Web.SSLEncrypt);
        get_value(it->second, "ssl_pem", this->Web.SSLPemFile);
        get_value(it->second, "ssl_key", this->Web.SSLKeyFile);
        get_value(it->second, "asset_dir", this->Web.AssetDir);
        get_value(it->second, "use_etag", this->Web.UseEtag);
    }

    if(this->ini.sections.find("Login") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("Login");
        get_value(it->second, "port", this->Login.Port);
        get_value(it->second, "host", this->Login.Host);
        get_value(it->second, "backlog", this->Login.Backlog);
        get_value(it->second, "recv_buffer", this->Login.RecvBufferSize);
        get_value(it->second, "ssl_encrypt", this->Login.SSLEncrypt);
        get_value(it->second, "ssl_pem", this->Login.SSLPemFile);
        get_value(it->second, "ssl_key", this->Login.SSLKeyFile);
        get_value(it->second, "cluster", this->Login.Cluster);
    } 

    if(this->ini.sections.find("GATE") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("GATE");
        get_value(it->second, "server_name", this->Gate.ServerName);
        get_value(it->second, "port", this->Gate.Port);
        get_value(it->second, "host", this->Gate.Host);
        get_value(it->second, "network", this->Gate.Network);
        get_value(it->second, "rsa_encrypt", this->Gate.RsaEncrypt);
        get_value(it->second, "rsa_keyfile", this->Gate.RsaKeyFile);
        get_value(it->second, "heartbeat", this->Gate.Heartbeat);
        get_value(it->second, "backlog", this->Gate.Backlog);
        get_value(it->second, "recv_buffer", this->Gate.RecvBuffer);
        get_value(it->second, "ssl_encrypt", this->Gate.SSLEncrypt);
        get_value(it->second, "ssl_pem", this->Gate.SSLPemFile);
        get_value(it->second, "ssl_key", this->Gate.SSLKeyFile);
        get_value(it->second, "max_user", this->Gate.MaxUser);
        get_value(it->second, "max_connection", this->Gate.MaxConnection);
        get_value(it->second, "cluster", this->Gate.Cluster);
        get_value(it->second, "register_expire", this->Gate.RegisterExpire);
        get_value(it->second, "register_interval", this->Gate.RegisterInterval);
    }
    if(this->ini.sections.find("CACHE") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("CACHE");
        get_value(it->second, "password", this->Cache.Password);
        get_value(it->second, "db", this->Cache.DB);
        get_value(it->second, "port", this->Cache.Port);
        get_value(it->second, "host", this->Cache.Host);
        get_value(it->second, "expire", this->Cache.ExpireTime);
    }

    if(this->ini.sections.find("CLUSTER") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("CLUSTER");
        get_value(it->second, "port", this->Cluster.Port);
        get_value(it->second, "host", this->Cluster.Host);
        get_value(it->second, "driver", this->Cluster.Driver);
        get_value(it->second, "heartbeat", this->Cluster.Heartbeat);
        get_value(it->second, "expire", this->Cluster.Expire);
        get_value(it->second, "reload_interval", this->Cluster.ReloadInterval);
        get_value(it->second, "reconnect_interval", this->Cluster.ReconnectInterval);
        get_value(it->second, "register_interval", this->Cluster.RegisterInterval);
        get_value(it->second, "name", this->Cluster.Name);
        get_value(it->second, "recv_buffer", this->Cluster.RecvBuffer);
    }

    if(this->ini.sections.find("MANAGED") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("MANAGED");
        get_value(it->second, "port", this->Managed.Port);
        get_value(it->second, "port", this->Managed.Port);
        get_value(it->second, "user", this->Managed.User);
        get_value(it->second, "password", this->Managed.Password);
    }
    //std::cout << "bitbucket.org compression level: " << this->Role << std::endl;
    return 0;
}

bool Config::SectionExist(const char* section) {
    auto it = this->ini.sections.find(section);
    if (it == this->ini.sections.end()){
        return false;
    }
    return true;
}

int Config::SQLConfig(const char* section, sql::SQLConfig* config) {
    auto const it = this->ini.sections.find(section);
    if (it == this->ini.sections.end()){
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "user", config->User)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "character_set", config->CharacterSet)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "driver", config->Driver)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

int Config::RedisConfig(const char* section, redis::RedisConfig* config) {
    auto const it = this->ini.sections.find(section);
    if (it == this->ini.sections.end()){
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!get_value(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

}
