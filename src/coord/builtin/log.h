#pragma once 

#include <cstdarg>

namespace coord {
namespace log{
    void LogFatal(const char *fmt, ...);
    void LogError(const char *fmt, ...);
    void LogWarn(const char *fmt, ...);
    void LogInfo(const char *fmt, ...);
    void LogDebug(const char *fmt, ...);
}
}

#define LOG_FATAL(str, ...)     coord::log::LogFatal("%s:%d", __FILE__, __LINE__);\
                                coord::log::LogFatal(str, ## __VA_ARGS__);

#define LOG_ERROR(str, ...)     coord::log::LogError("%s:%d", __FILE__, __LINE__);\
                                coord::log::LogError(str, ## __VA_ARGS__);

#define LOG_WARN(str, ...)      coord::log::LogWarn("%s:%d", __FILE__, __LINE__);\
                                coord::log::LogWarn(str, ## __VA_ARGS__);

#define LOG_INFO(str, ...)      coord::log::LogInfo(str, ## __VA_ARGS__);

#define LOG_DEBUG(str, ...)     coord::log::LogDebug(str, ## __VA_ARGS__);


