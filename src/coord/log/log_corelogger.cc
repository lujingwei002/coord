#include "coord/log/log_corelogger.h"
#include <ctime>

namespace coord {
namespace log {

core_logger* newCoreLogger() {
    core_logger* logger = new core_logger();
    return logger;
}

core_logger::core_logger(){
    strcpy(this->config.Dir, "./");
    strcpy(this->config.Name, "corelog");
    this->config.MaxByte = 1024*1024;
    this->file = NULL;
    this->lineNum = 0;
}

core_logger::~core_logger() {

}

void core_logger::rotateFile(bool force){
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

void core_logger::reload() {
    if(this->file != NULL){
        fclose(this->file);
        this->file = NULL;
    }
    sprintf(this->path, "%s%s.log", this->config.Dir, this->config.Name);
    this->file = fopen(this->path, "a+");
}
 
void core_logger::Log(const char* str){
    if(!this->file){
        return;
    }
    this->rotateFile(false);
    size_t strLen = strlen(str);
    fwrite(str, 1, strLen, this->file);
    fflush(this->file);
}


}
}