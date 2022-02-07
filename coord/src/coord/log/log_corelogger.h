#pragma once 

#include "coord/log/log_logger.h"
#include "coord/builtin/init.h"
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>

namespace coord {
namespace log {

class core_logger_config {
public:
    char        Dir[PATH_MAX];
    uint32_t    MaxByte;
    char        Name[PATH_MAX];
};

class core_logger : public base_logger {
public:
    core_logger();
    virtual ~core_logger();
public:
    virtual void Log(const char* str);
    void reload();
    core_logger_config* getConfig() {
        return &this->config;
    }
private:
    void rotateFile(bool force);
private:
    char                    path[PATH_MAX*3]; //当前日志文件路径
    int                     lineNum;
    core_logger_config      config;
    FILE*                   file;
};

core_logger* newCoreLogger();

}
}

