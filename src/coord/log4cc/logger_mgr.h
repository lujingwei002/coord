#pragma once 

#include <map>
#include <string>

namespace coord {

class Coord;

namespace log4cc {

class Category;
class LoggerConfig;

class LoggerMgr {
public:
    LoggerMgr(Coord* coord);
    ~LoggerMgr();
public:
    Category* GetCategory(const char* name);
    Category* NewCategory(const char* name);
    Category* GetCoreLogger();
    Category* GetDefaultLogger();
    int ConfigCategory(Category* category, const char* name); 
    int ConfigCategory(Category* category, LoggerConfig* config);
    int configDefaultLogger(Category* category);
    int configCoreLogger(Category* category);
private:
private:
    std::map<std::string, Category*>    categoryDict;
    Coord*                              coord;
};

LoggerMgr* newLoggerMgr(Coord* coord);

}
}

