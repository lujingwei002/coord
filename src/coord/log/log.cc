#include "coord/log/log.h"
#include "coord/coord.h"

namespace coord {
namespace log  {


void LogFatal(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->CoreLogFatal(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogError(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->CoreLogError(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogWarn(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->CoreLogFatal(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogInfo(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->CoreLogInfo(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogMsg(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->CoreLogMsg(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogDebug(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->CoreLogDebug(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void SetPriority(int priority) {
    if(coorda) {
        coorda->CoreLogSetPriority(priority);
    }
}


}

}
