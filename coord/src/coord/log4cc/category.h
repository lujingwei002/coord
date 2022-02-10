#pragma once 

#include "coord/log4cc/priority.h"

#include <string>
#include <vector>
#include <cstdarg>

namespace coord {
namespace log4cc {

class LoggerMgr;
class Layout;
class Appender;

class Category {
public:
    Category(LoggerMgr* logger, const char* name);
    ~Category();
public:
    void SetPriority(PriorityLevel priority);
    void SetLayout(Layout* layout);
    void AddAppender(Appender* appender);

    void Emerg(const char* fmt, ...);
    void Fatal(const char* fmt, ...);
    void Alert(const char* fmt, ...);
    void Crit(const char* fmt, ...);
    void Error(const char* fmt, ...);
    void Warn(const char* fmt, ...);
    void Notice(const char* fmt, ...);
    void Info(const char* fmt, ...);
    void Debug(const char* fmt, ...);

    void Emerg(const char* fmt, va_list args); 
    void Fatal(const char* fmt, va_list args); 
    void Alert(const char* fmt, va_list args); 
    void Crit(const char* fmt, va_list args); 
    void Error(const char* fmt, va_list args);
    void Warn(const char* fmt, va_list args);
    void Notice(const char* fmt, va_list args);
    void Info(const char* fmt, va_list args);
    void Debug(const char* fmt, va_list args);

    void Log(const char* str);
    void vPrintf(int priority, const char* priorityName, const char *fmt, va_list ap);
private:
    LoggerMgr*              logger;
    std::string             name;
    PriorityLevel           priority;
    Layout*                 layout;
    std::vector<Appender*>  appenderArr;
};

Category* newCategory(LoggerMgr* logger, const char* name);


}

}
