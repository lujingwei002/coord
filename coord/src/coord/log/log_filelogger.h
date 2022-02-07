#pragma once 

#include "coord/log/log_logger.h"
#include "coord/builtin/init.h"
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>


namespace coord {
namespace log {

class file_logger_config {
public:
    char        Dir[PATH_MAX];
    uint32_t    MaxByte;
    char        Name[PATH_MAX];
};

class file_logger : public base_logger {
public:
    file_logger();
    virtual ~file_logger();
public:
    virtual void Log(const char* str);
    void reload();
    file_logger_config* getConfig() {
        return &this->config;
    }
private:
    void rotateFile(bool force);
private:
    char                    path[PATH_MAX*3]; //当前日志文件路径
    int                     lineNum;
    file_logger_config      config;
    FILE*                   file;
};

file_logger* newFileLogger();

}
}

