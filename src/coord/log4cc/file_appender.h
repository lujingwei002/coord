#pragma once 

#include "coord/log4cc/appender.h"
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <map>

namespace coord {
namespace log4cc {

class FileAppender : public Appender {
public:
    FileAppender(const char* filePath);
    virtual ~FileAppender();
public:
    void SetMaxByte(int maxByte);
    void SetMaxLine(int maxLine);
    virtual void Log(const char* str);
private:
    void rotateFile(bool force);
private:
    std::string     filePath;
    int             lineNum;
    int             maxByte;
    int             maxLine;
    FILE*           file;
};

FileAppender* newFileAppender(const char* filePath);

}
}
