#include "coord/config/config.h"
#include "coord/log/log.h"
#include "coord/sql/sql_client.h"
#include "coord/redis/redis_client.h"
#include "coord/builtin/init.h"
#include "inipp/inipp.h"
#include <fstream>
#include <iostream>

namespace coord {

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
    inipp::get_value(this->ini.sections["DEFAULT"], "registery", this->Basic.Registery);
    inipp::get_value(this->ini.sections["DEFAULT"], "main", this->Basic.Main);
    inipp::get_value(this->ini.sections["DEFAULT"], "scene", this->Basic.Scene);
    inipp::get_value(this->ini.sections["DEFAULT"], "package", this->Basic.Package);
    inipp::get_value(this->ini.sections["DEFAULT"], "gc", this->Basic.GC);
    inipp::get_value(this->ini.sections["DEFAULT"], "update", this->Basic.Update);
    inipp::get_value(this->ini.sections["DEFAULT"], "worker", this->Basic.Worker);
    inipp::get_value(this->ini.sections["DEFAULT"], "worker_num", this->Basic.WorkerNum);
    inipp::get_value(this->ini.sections["DEFAULT"], "proto", this->Basic.Proto);
    inipp::get_value(this->ini.sections["DEFAULT"], "name", this->Basic.Name);
    inipp::get_value(this->ini.sections["DEFAULT"], "core_logger", this->Basic.CoreLogger);
    inipp::get_value(this->ini.sections["DEFAULT"], "core_logger_maxbyte", this->Basic.CoreLoggerMaxByte);
    inipp::get_value(this->ini.sections["DEFAULT"], "logger", this->Basic.Logger);
    inipp::get_value(this->ini.sections["DEFAULT"], "logger_maxbyte", this->Basic.LoggerMaxByte);
    inipp::get_value(this->ini.sections["DEFAULT"], "pid", this->Basic.Pid);
    inipp::get_value(this->ini.sections["DEFAULT"], "version", this->Basic.Version);
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
        inipp::get_value(it->second, "port", this->Web.Port);
        inipp::get_value(it->second, "host", this->Web.Host);
        inipp::get_value(it->second, "backlog", this->Web.Backlog);
        inipp::get_value(it->second, "recv_buffer", this->Web.RecvBuffer);
        inipp::get_value(it->second, "ssl_encrypt", this->Web.SSLEncrypt);
        inipp::get_value(it->second, "ssl_pem", this->Web.SSLPemFile);
        inipp::get_value(it->second, "ssl_key", this->Web.SSLKeyFile);
        inipp::get_value(it->second, "asset_dir", this->Web.AssetDir);
        inipp::get_value(it->second, "use_etag", this->Web.UseEtag);
    }

    if(this->ini.sections.find("Login") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("Login");
        inipp::get_value(it->second, "port", this->Login.Port);
        inipp::get_value(it->second, "host", this->Login.Host);
        inipp::get_value(it->second, "backlog", this->Login.Backlog);
        inipp::get_value(it->second, "recv_buffer", this->Login.RecvBufferSize);
        inipp::get_value(it->second, "ssl_encrypt", this->Login.SSLEncrypt);
        inipp::get_value(it->second, "ssl_pem", this->Login.SSLPemFile);
        inipp::get_value(it->second, "ssl_key", this->Login.SSLKeyFile);
        inipp::get_value(it->second, "cluster", this->Login.Cluster);
    } 

    if(this->ini.sections.find("GATE") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("GATE");
        inipp::get_value(it->second, "server_name", this->Gate.ServerName);
        inipp::get_value(it->second, "port", this->Gate.Port);
        inipp::get_value(it->second, "host", this->Gate.Host);
        inipp::get_value(it->second, "network", this->Gate.Network);
        inipp::get_value(it->second, "rsa_encrypt", this->Gate.RsaEncrypt);
        inipp::get_value(it->second, "rsa_keyfile", this->Gate.RsaKeyFile);
        inipp::get_value(it->second, "heartbeat", this->Gate.Heartbeat);
        inipp::get_value(it->second, "backlog", this->Gate.Backlog);
        inipp::get_value(it->second, "recv_buffer", this->Gate.RecvBuffer);
        inipp::get_value(it->second, "ssl_encrypt", this->Gate.SSLEncrypt);
        inipp::get_value(it->second, "ssl_pem", this->Gate.SSLPemFile);
        inipp::get_value(it->second, "ssl_key", this->Gate.SSLKeyFile);
        inipp::get_value(it->second, "max_user", this->Gate.MaxUser);
        inipp::get_value(it->second, "max_connection", this->Gate.MaxConnection);
        inipp::get_value(it->second, "cluster", this->Gate.Cluster);
        inipp::get_value(it->second, "register_expire", this->Gate.RegisterExpire);
        inipp::get_value(it->second, "register_interval", this->Gate.RegisterInterval);
    }
    if(this->ini.sections.find("CACHE") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("CACHE");
        inipp::get_value(it->second, "password", this->Cache.Password);
        inipp::get_value(it->second, "db", this->Cache.DB);
        inipp::get_value(it->second, "port", this->Cache.Port);
        inipp::get_value(it->second, "host", this->Cache.Host);
        inipp::get_value(it->second, "expire", this->Cache.ExpireTime);
    }

    if(this->ini.sections.find("CLUSTER") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("CLUSTER");
        inipp::get_value(it->second, "port", this->Cluster.Port);
        inipp::get_value(it->second, "host", this->Cluster.Host);
        inipp::get_value(it->second, "driver", this->Cluster.Driver);
        inipp::get_value(it->second, "heartbeat", this->Cluster.Heartbeat);
        inipp::get_value(it->second, "expire", this->Cluster.Expire);
        inipp::get_value(it->second, "reload_interval", this->Cluster.ReloadInterval);
        inipp::get_value(it->second, "reconnect_interval", this->Cluster.ReconnectInterval);
        inipp::get_value(it->second, "register_interval", this->Cluster.RegisterInterval);
        inipp::get_value(it->second, "name", this->Cluster.Name);
        inipp::get_value(it->second, "recv_buffer", this->Cluster.RecvBuffer);
    }

    if(this->ini.sections.find("MANAGED") != this->ini.sections.end()) {
        auto const it = this->ini.sections.find("MANAGED");
        inipp::get_value(it->second, "port", this->Managed.Port);
        inipp::get_value(it->second, "port", this->Managed.Port);
        inipp::get_value(it->second, "user", this->Managed.User);
        inipp::get_value(it->second, "password", this->Managed.Password);
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
    if(!inipp::get_value(it->second, "user", config->User)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "character_set", config->CharacterSet)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "driver", config->Driver)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

int Config::RedisConfig(const char* section, redis::RedisConfig* config) {
    auto const it = this->ini.sections.find(section);
    if (it == this->ini.sections.end()){
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "password", config->Password)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "host", config->Host)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "port", config->Port)) {
        return ErrorConfigNotExist;
    }
    if(!inipp::get_value(it->second, "db", config->DB)) {
        return ErrorConfigNotExist;
    }
    return 0;
}

}
