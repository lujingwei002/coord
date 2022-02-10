#pragma once 

#include <map>

namespace coord {

class Coord;

namespace log4cc {

class Category;

class LoggerMgr {
public:
    LoggerMgr(Coord* coord);
    ~LoggerMgr();
public:
    Category* getCategory(const char* name);
    Category* GetConfigCategory(const char* name); 
private:
    std::map<std::string, Category*>    categoryDict;
    Coord*                              coord;
};

LoggerMgr* newLoggerMgr(Coord* coord);

}
}

