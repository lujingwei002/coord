#include "coord/log4cc/logger_mgr.h"
#include "coord/log4cc/category.h"
#include "coord/log4cc/basic_layout.h"
#include "coord/log4cc/config.h"
#include "coord/log4cc/console_appender.h"
#include "coord/log4cc/file_appender.h"
#include "coord/config/config.h"
#include "coord/coord.h"

namespace coord {
namespace log4cc {

LoggerMgr* newLoggerMgr(Coord* coord) {
    LoggerMgr* self = new LoggerMgr(coord);
    return self;
}


LoggerMgr:: LoggerMgr(Coord* coord) {
    this->coord = coord;
}

LoggerMgr::~LoggerMgr() {
    for (auto it : this->categoryDict) {
        delete it.second;
    }
    this->categoryDict.clear();
}

Category* LoggerMgr::getCategory(const char* name) {
    auto it = this->categoryDict.find(name);
    if (it != this->categoryDict.end()) {
        return it->second; 
    }
    Category* category = newCategory(this, name);
    if (category == nullptr) {
        return nullptr;
    }
    this->categoryDict[name] = category;
    return category;
}

Category* LoggerMgr::GetConfigCategory(const char* name) {
    auto it = this->categoryDict.find(name);
    if (it != this->categoryDict.end()) {
        return it->second; 
    }
    LoggerConfig config;
    int err = this->coord->config->LoggerConfig(name, &config);
    if (err != 0) {
        this->coord->coreLogError("[coord::LoggerMgr] GetConfigCategory %s failed, error=%d", name, err);
        return nullptr; 
    }
    Category* category = newCategory(this, name);
    if (category == nullptr) {
        return nullptr;
    }
    // 日志级别
    category->SetPriority(config.Priority);
    // 输出目标
    if (config.Console) {
        category->AddAppender(newConsoleAppender());
    }
    if (config.File.size() > 0){
        FileAppender* appender = newFileAppender(config.File.c_str());
        appender->SetMaxLine(config.MaxLine);
        appender->SetMaxByte(config.MaxByte);
        category->AddAppender(appender);
    }

    if (config.Layout == "basic") {
        Layout* layout = new BasicLayout();
        category->SetLayout(layout);
    }
    this->categoryDict[name] = category;
    return category;
}


}
}
