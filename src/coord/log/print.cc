#include "coord/log/print.h"
#include "coord/log/log.h"
#include <cstdio>

namespace coord {


    void Println(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        coord::log::LogInfo(fmt, args);
        va_end(args);
    }

    void Errorln(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        coord::log::LogError(fmt, args);
        va_end(args);
    }

    void Debugln(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        coord::log::LogDebug(fmt, args);
        va_end(args);
    }


    void CorePrintln(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        coord::log::CoreLogInfo(fmt, args);
        va_end(args);
    }

    void CoreErrorln(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        coord::log::CoreLogError(fmt, args);
        va_end(args);
    }

    void CoreDebugln(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        coord::log::CoreLogDebug(fmt, args);
        va_end(args);
    }


}


/*

#define LOG_FATAL(str, ...)     coord::log::LogFatal("%s:%d", __FILE__, __LINE__);\
                                coord::log::LogFatal(str, ## __VA_ARGS__);

#define LOG_ERROR(str, ...)     coord::log::LogError("%s:%d", __FILE__, __LINE__);\
                               coord::log::LogError(str, ## __VA_ARGS__);

#define LOG_WARN(str, ...)      coord::log::LogWarn("%s:%d", __FILE__, __LINE__);\
                                coord::log::LogWarn(str, ## __VA_ARGS__);

#define LOG_INFO(str, ...)      coord::log::LogInfo(str, ## __VA_ARGS__);

#define LOG_DEBUG(str, ...)     coord::log::LogDebug(str, ## __VA_ARGS__);
*/
