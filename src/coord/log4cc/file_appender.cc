#include "coord/log4cc/file_appender.h"
#include "coord/builtin/init.h"

#include <cstdio>
#include <cstring>
#include <uv.h>
#include <ctime>

namespace coord {
namespace log4cc {

FileAppender* newFileAppender() {
    FileAppender* appender = new FileAppender();
    return appender;
}

FileAppender::FileAppender() {
    this->file = nullptr;
    this->lineNum = 0;
    this->maxByte = 0;
    this->maxLine = 0;
}

FileAppender::~FileAppender() {
    if(nullptr != this->file){
        fclose(this->file);
        this->file = nullptr;
    }
}

int FileAppender::openFile(const std::string& filePath) {
    if(nullptr != this->file){
        fclose(this->file);
        this->file = nullptr;
    }
    this->file = fopen(filePath.c_str(), "a+");
    if (this->file == nullptr) {
        return ErrorNoSuchFileOrDirectory;
    }
    this->filePath = filePath;
    return 0;
}

void FileAppender::SetMaxByte(int maxByte) {
    this->maxByte = maxByte;
}

void FileAppender::SetMaxLine(int maxLine) {
    this->maxLine = maxLine;
}

void FileAppender::Log(const char* str) {
    if(nullptr == this->file){   
        return;
    }
    this->rotateFile(false);
    size_t strLen = strlen(str);
    fwrite(str, 1, strLen, this->file);
    fflush(this->file);
}

void FileAppender::rotateFile(bool force){
    if(force){
        goto rotate;
    }
    if(this->maxByte > 0){
        if(ftell(this->file) >= this->maxByte){
            goto rotate;
        }
    }
    return;
rotate:
    time_t t = time(NULL);
    struct tm* tm = localtime(&t); 
    static thread_local char backupPath[PATH_MAX*3];
    sprintf(backupPath, "%s.%04d%02d%02d_%02d%02d%02d", this->filePath.c_str(), tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    //重命名文件
    rename(this->filePath.c_str(), backupPath);
}


}
}
