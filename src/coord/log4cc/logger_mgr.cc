#include "coord/log4cc/logger_mgr.h"
#include "coord/log4cc/category.h"
#include "coord/log4cc/basic_layout.h"
#include "coord/log4cc/config.h"
#include "coord/log4cc/console_appender.h"
#include "coord/log4cc/file_appender.h"
#include "coord/environment/environment.h"
#include "coord/config/config.h"
#include "coord/coordx.h"
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

int LoggerMgr::ConfigCategory(Category* category, LoggerConfig* config) {
    // 日志级别
    category->SetPriority(config->Priority);
    // 输出目标
    if (config->Console) {
        category->AddAppender(newConsoleAppender());
    }
    if (config->File.size() > 0){
        FileAppender* appender = newFileAppender();
        int err = appender->openFile(config->File);
        if(err) {
            this->coord->CoreLogError("no such file or directory: %s", config->File.c_str());
            delete appender;
            return err;
        }
        appender->SetMaxLine(config->MaxLine);
        appender->SetMaxByte(config->MaxByte);
        category->AddAppender(appender);
    }
    if (config->Layout == "basic") {
        Layout* layout = new BasicLayout();
        category->SetLayout(layout);
    }
    return 0;
}

Category* LoggerMgr::GetCategory(const char* name) {
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

Category* LoggerMgr::GetCoreLogger() {
    static const char* name = "core-logger";
    return this->GetCategory(name);
}

Category* LoggerMgr::GetDefaultLogger() {
    static const char* name = "logger";
    return this->GetCategory(name);
}

int LoggerMgr::configDefaultLogger(Category* category) {
    static const char* name = "logger";
    LoggerConfig config;
    int err = this->coord->Config->LoggerConfig(name, &config);
    if (err != 0) {
        //std::string path = coordx::path::PathJoin("log", this->coord->Config->Basic.Name + ".log");
        //config.File = coordx::path::PathJoin(this->coord->Environment->WorkingDir, path);
        config.Console = true;
    }
    config.Name = name;
    err = this->ConfigCategory(category, &config);
    if (err) {
        fprintf(stderr, "config default logger failed\n");
    }
    return err;
}

int LoggerMgr::configCoreLogger(Category* category) {
    static const char* name = "core-logger";
    LoggerConfig config;
    int err = this->coord->Config->LoggerConfig(name, &config);
    if (err != 0) {
        std::string path = coordx::path::PathJoin("log", this->coord->Config->Basic.Name + "-core.log");
        config.File = coordx::path::PathJoin(this->coord->Environment->CoordDir, path);
    }
    config.Name = name;
    err = this->ConfigCategory(category, &config);
    if (err) {
        fprintf(stderr, "config core logger failed\n");
    }
    return err;
}


int LoggerMgr::ConfigCategory(Category* category, const char* name) {
    LoggerConfig config;
    int err = this->coord->Config->LoggerConfig(name, &config);
    if (err != 0) {
        this->coord->CoreLogError("[coord::LoggerMgr] GetConfigCategory %s failed, error=%d", name, err);
        return err;
    }
    config.Name = name;
    return this->ConfigCategory(category, &config);
}


}
}
