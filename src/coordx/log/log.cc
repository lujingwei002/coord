#include "coordx/log/log.h"
#include <cstdio>
namespace coordx {
namespace log {
void LogFatal(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(false) {
        
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
    if(false) {
       
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
    if(false) {
        
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
    if(false) {
        
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
    if(false) {
        
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}


}
}
