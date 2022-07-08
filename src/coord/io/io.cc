#include "coord/io/io.h"
#include "coord/coord.h"
#include <fstream> 
#include <iostream>

#include<sys/file.h> // flock
#include <fcntl.h> // open

namespace coord {
namespace io {
    
int ReadFile(const char* path, byte_slice& buffer) {
    std::ifstream file(path); 
    if (!file.is_open()) { 
        return -1;
    } 
    file.seekg(0, std::ios::end);    
    size_t length = file.tellg();          
    file.seekg(0, std::ios::beg);   
    int err = buffer.Reserve(length);    
    if (err) {
        file.close(); 
        return -1;
    }
    file.read(buffer.Data(), length);   
    buffer.Resize(length); 
    file.close(); 
    return 0;
}

uv_stat_t* FileStat(const char* path) {
    static thread_local uv_fs_t req;
    int err = uv_fs_stat(&coorda->loop, &req, path, NULL);
    if (err) {
        return NULL;
    }
    uv_stat_t* stat = (uv_stat_t*)req.ptr;
    return stat;
}

int FileLock(const char* path) {
    int fd = open(path, O_RDWR|O_CREAT, 0755);
    if (fd < 0) {
        return 1;
    }
    if (flock(fd, LOCK_EX | LOCK_NB) < 0) {
        return 2;
    }
    return 0;
}

}
}