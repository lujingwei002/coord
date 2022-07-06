#include "coord/log/log.h"
#include "coord/coord.h"

namespace coord {
namespace log  {

base_logger logger;

static int s_warn_counter = 0;
static int s_error_counter = 0;

void LogFatal(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->coreLogFatal(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogError(const char *fmt, ...){
    s_error_counter++;
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->coreLogError(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void LogWarn(const char *fmt, ...){
    s_warn_counter++;
    va_list args;
    va_start(args, fmt);
    if(coorda) {
        coorda->coreLogFatal(fmt, args);
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
        coorda->coreLogInfo(fmt, args);
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
        coorda->coreLogMsg(fmt, args);
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
        coorda->coreLogDebug(fmt, args);
    } else {
        //logger.LogFatal(fmt, args);
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
    }
    va_end(args);
}

void OpenLevel(int level) {
    if(coorda) {
        coorda->coreLogOpenLevel(level);
    } else {
        logger.OpenLevel(level);
    }
}

void SetLevel(int level) {
    if(coorda) {
        coorda->coreLogSetLevel(level);
    } else {
        logger.SetLevel(level);
    }
}

void CloseLevel(int level) {
    if(coorda) {
        coorda->coreLogCloseLevel(level);
    } else {
        logger.CloseLevel(level);
    }
}

}

}
