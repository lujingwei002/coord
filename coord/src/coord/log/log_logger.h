#pragma once 

//日志类

#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdarg>

namespace coord {
namespace log {

enum LogLevel {
    FATAL = 1,
    ERROR = 2,
    WARN = 4,
    INFO = 8,
    DEBUG = 16,
    MSG = 32,
};

class base_logger {
public:
    base_logger();
    virtual ~base_logger();
public:
    void LogFatal(const char* fmt, ...);
    void LogError(const char* fmt, ...);
    void LogWarn(const char* fmt, ...);
    void LogInfo(const char* fmt, ...);
    void LogDebug(const char* fmt, ...);
    void LogMsg(const char* fmt, ...);

    void LogFatal(const char* fmt, va_list args); 
    void LogError(const char* fmt, va_list args);
    void LogWarn(const char* fmt, va_list args);
    void LogInfo(const char* fmt, va_list args);
    void LogDebug(const char* fmt, va_list args);
    void LogMsg(const char* fmt, va_list args);

    void SetLevel(int level);
    void OpenLevel(int level);
    void CloseLevel(int level);
 
    void SetTag(const char* val);
    void SetFormat(const char* val);

    virtual void Log(const char* str);

protected:
    int _vsprintf(char *buf, const char* fmt, const char* level, const char *msg);
private:
    void log_vprint(int level, const char *fmt, va_list ap);
private:
    int32_t flag;
    char tag[64];
    char format[64];
};

}
}
