#include "coord/log4cc/category.h"
#include "coord/log4cc/logger_mgr.h"
#include "coord/log4cc/layout.h"
#include "coord/log4cc/appender.h"

#include <cstdio>
#include <cstring>

namespace coord {
namespace log4cc {

Category* newCategory(LoggerMgr* logger, const char* name) {
    Category* self = new Category(logger, name);
    return self;
}

Category::Category(LoggerMgr* logger, const char* name) {
    this->logger = logger;
    this->name = name;
    this->priority = ALL;
    this->layout = nullptr;
}

Category::~Category() {
    if (this->layout != nullptr) {
        delete this->layout;
        this->layout = nullptr;
    }
    for (auto it : this->appenderArr) {
        delete it;
    }
    this->appenderArr.clear();
}

void Category::SetPriority(PriorityLevel priority) {
    this->priority = priority;
}

void Category::SetLayout(Layout* layout) {
    this->layout = layout;
}

void Category::AddAppender(Appender* appender) {
    this->appenderArr.push_back(appender);
}

void Category::Emerg(const char* fmt, va_list args){
    this->vPrintf(EMERG, "EMERG", fmt, args);
}

void Category::Fatal(const char* fmt, va_list args){
    this->vPrintf(FATAL, "FATAL", fmt, args);
}

void Category::Alert(const char* fmt, va_list args){
    this->vPrintf(ALERT, "ALERT", fmt, args);
}

void Category::Crit(const char* fmt, va_list args){
    this->vPrintf(CRIT, "CRIT", fmt, args);
}

void Category::Error(const char* fmt, va_list args){
    this->vPrintf(ERROR, "ERROR", fmt, args);
}

void Category::Warn(const char* fmt, va_list args){
    this->vPrintf(WARN, "WARN", fmt, args);
}

void Category::Notice(const char* fmt, va_list args){
    this->vPrintf(NOTICE, "NOTICE", fmt, args);
}

void Category::Info(const char* fmt, va_list args){
    this->vPrintf(INFO, "INFO", fmt, args);
}

void Category::Debug(const char* fmt, va_list args){
    this->vPrintf(DEBUG, "DEBUG", fmt, args);
}

void Category::Emerg(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(EMERG, "EMERG", fmt, args);
    va_end(args);
}

void Category::Fatal(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(FATAL, "FATAL", fmt, args);
    va_end(args);
}

void Category::Alert(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(ALERT, "ALERT", fmt, args);
    va_end(args);
}

void Category::Crit(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(CRIT, "CRIT", fmt, args);
    va_end(args);
}

void Category::Error(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(ERROR, "ERROR", fmt, args);
    va_end(args);
}

void Category::Warn(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(WARN, "WARN", fmt, args);
    va_end(args);
}

void Category::Notice(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(NOTICE, "NOTICE", fmt, args);
    va_end(args);
}

void Category::Info(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(INFO, "INFO", fmt, args);
    va_end(args);
}

void Category::Debug(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    this->vPrintf(DEBUG, "DEBUG", fmt, args);
    va_end(args);
}

void Category::vPrintf(int priority, const char* priorityName, const char *fmt, va_list ap){
    if (this->priority < priority) {
        return;
    }
    static thread_local char msg[4096];
    vsnprintf(msg, sizeof(msg), fmt, ap);
    if (this->layout == nullptr) {
        this->Log(msg);
    } else {
        const char* str = this->layout->format(priorityName, msg);
        this->Log(str);
    }
}

void Category::Log(const char* str){
    for (auto it : this->appenderArr) {
        it->Log(str);
    }
    // if (this->appenderArr.size() <= 0) {
    //     printf(str);
    //     fflush(stdout);
    // }
}


}
}
