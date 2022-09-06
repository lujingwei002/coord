#pragma once 

#include <cstdarg>

namespace coord {
namespace log {
    void LogFatal(const char *fmt, ...);
    void LogError(const char *fmt, ...);
    void LogWarn(const char *fmt, ...);
    void LogInfo(const char *fmt, ...);
    void LogDebug(const char *fmt, ...);

    void LogFatal(const char *fmt, va_list args);
    void LogError(const char *fmt, va_list args);
    void LogWarn(const char *fmt, va_list args);
    void LogInfo(const char *fmt, va_list args);
    void LogDebug(const char *fmt, va_list args);

    void CoreLogFatal(const char *fmt, ...);
    void CoreLogError(const char *fmt, ...);
    void CoreLogWarn(const char *fmt, ...);
    void CoreLogInfo(const char *fmt, ...);
    void CoreLogDebug(const char *fmt, ...);

    void CoreLogFatal(const char *fmt, va_list args);
    void CoreLogError(const char *fmt, va_list args);
    void CoreLogWarn(const char *fmt, va_list args);
    void CoreLogInfo(const char *fmt, va_list args);
    void CoreLogDebug(const char *fmt, va_list args);

}
}



