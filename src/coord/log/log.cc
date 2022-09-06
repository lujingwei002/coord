#include "coord/log/log.h"
#include "coord/coord.h"
#include <cstdio>

namespace coord {
namespace log {

void LogFatal(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogFatal(fmt, args);
    va_end(args);
}

void LogError(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogError(fmt, args);
    va_end(args);
}

void LogWarn(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogWarn(fmt, args);
    va_end(args);
}

void LogInfo(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogInfo(fmt, args);
    va_end(args);
}

void LogDebug(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    LogDebug(fmt, args);
    va_end(args);
}

void LogFatal(const char *fmt, va_list args){
    if(coorda) {
        coorda->LogFatal(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void LogError(const char *fmt, va_list args){
    if(coorda) {
        coorda->LogError(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void LogWarn(const char *fmt, va_list args){
    if(coorda) {
        coorda->LogWarn(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void LogInfo(const char *fmt, va_list args){
    if(coorda) {
        coorda->LogInfo(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void LogDebug(const char *fmt, va_list args){
    if(coorda) {
        coorda->LogDebug(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}


void CoreLogFatal(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    CoreLogFatal(fmt, args);
    va_end(args);
}

void CoreLogError(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    CoreLogError(fmt, args);
    va_end(args);
}

void CoreLogWarn(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    CoreLogWarn(fmt, args);
    va_end(args);
}

void CoreLogInfo(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    CoreLogInfo(fmt, args);
    va_end(args);
}

void CoreLogDebug(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    CoreLogDebug(fmt, args);
    va_end(args);
}

void CoreLogFatal(const char *fmt, va_list args){
    if(coorda) {
        coorda->CoreLogFatal(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void CoreLogError(const char *fmt, va_list args){
    if(coorda) {
        coorda->CoreLogError(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void CoreLogWarn(const char *fmt, va_list args){
    if(coorda) {
        coorda->CoreLogWarn(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void CoreLogInfo(const char *fmt, va_list args){
    if(coorda) {
        coorda->CoreLogInfo(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}

void CoreLogDebug(const char *fmt, va_list args){
    if(coorda) {
        coorda->CoreLogDebug(fmt, args);
    } else {
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
}




}
}
