#pragma once 

#include "coord/log4cc/declare.h"

namespace coord {
namespace log{

    void LogFatal(const char *fmt, ...);
    void LogError(const char *fmt, ...);
    void LogWarn(const char *fmt, ...);
    void LogInfo(const char *fmt, ...);
    void LogDebug(const char *fmt, ...);
    void LogMsg(const char *fmt, ...);
    void SetPriority(log4cc::PriorityLevel priority);
    
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

#define LOG_MSG(str, ...)     coord::log::LogMsg(str, ## __VA_ARGS__);

