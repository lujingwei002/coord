#pragma once 

#include <cstdarg>

namespace coordx {
namespace log{
    void LogFatal(const char *fmt, ...);
    void LogError(const char *fmt, ...);
    void LogWarn(const char *fmt, ...);
    void LogInfo(const char *fmt, ...);
    void LogDebug(const char *fmt, ...);
}
}

#define LOG_FATAL(str, ...)     coordx::log::LogFatal("%s:%d", __FILE__, __LINE__);\
                                coordx::log::LogFatal(str, ## __VA_ARGS__);

#define LOG_ERROR(str, ...)     coordx::log::LogError("%s:%d", __FILE__, __LINE__);\
                                coordx::log::LogError(str, ## __VA_ARGS__);

#define LOG_WARN(str, ...)      coordx::log::LogWarn("%s:%d", __FILE__, __LINE__);\
                                coordx::log::LogWarn(str, ## __VA_ARGS__);

#define LOG_INFO(str, ...)      coordx::log::LogInfo(str, ## __VA_ARGS__);

#define LOG_DEBUG(str, ...)     coordx::log::LogDebug(str, ## __VA_ARGS__);


