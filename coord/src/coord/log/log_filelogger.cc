#include "coord/log/log_filelogger.h"
#include <ctime>

namespace coord {
namespace log {

file_logger* newFileLogger() {
    file_logger* logger = new file_logger();
    return logger;
}

file_logger::file_logger(){
    strcpy(this->config.Dir, "./");
    strcpy(this->config.Name, "log");
    this->config.MaxByte = 1024*1024;
    this->file = NULL;
    this->lineNum = 0;
}

file_logger::~file_logger() {

}

void file_logger::rotateFile(bool force){
    if(force){
        goto rotate;
    }
    if(this->config.MaxByte > 0){
        if(ftell(this->file) >= this->config.MaxByte){
            goto rotate;
        }
    }
    return;
rotate:
    time_t t = time(NULL);
    struct tm* tm = localtime(&t); 
    static thread_local char backupPath[PATH_MAX*3];
    sprintf(backupPath, "%s%s_%04d%02d%02d_%02d%02d%02d.log", this->config.Dir, this->config.Name, tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    //重命名文件
    rename(this->path, backupPath);
}

void file_logger::reload() {
    if(this->file != NULL){
        fclose(this->file);
        this->file = NULL;
    }
    sprintf(this->path, "%s%s.log", this->config.Dir, this->config.Name);
    this->file = fopen(this->path, "a+");
}
 
void file_logger::Log(const char* str){
    printf(str);
    fflush(stdout);
    if(this->file){   
        this->rotateFile(false);
        size_t strLen = strlen(str);
        fwrite(str, 1, strLen, this->file);
        fflush(this->file);
    }
}


}
}