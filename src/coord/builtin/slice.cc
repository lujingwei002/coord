#include "coord/builtin/slice.h"
#include <stdio.h>

namespace coord {


int Appendf(byte_slice& self, const char* fmt, va_list args) {
    static thread_local char* tempbuf = NULL;
    static thread_local int tempbufLen = 0;
    if(tempbuf == NULL) {
        tempbufLen = 4096;
        tempbuf = (char*)malloc(tempbufLen);
    }
    int len = 0;
    while(true){
        len = vsnprintf(tempbuf, tempbufLen, fmt, args);
        if (len < tempbufLen){
            break;
        }
        free(tempbuf);
        tempbufLen = tempbufLen * 2;
        tempbuf = (char*)malloc(tempbufLen);
    }
    return coord::Append(self, tempbuf, len);
}

int Appendf(byte_slice& self, const char* fmt, ...) {
    static thread_local char* tempbuf = NULL;
    static thread_local int tempbufLen = 0;
    if(tempbuf == NULL) {
        tempbufLen = 4096;
        tempbuf = (char*)malloc(tempbufLen);
    }
    va_list args;
    va_start(args, fmt);
    int len = 0;
    while(true){
        len = vsnprintf(tempbuf, tempbufLen, fmt, args);
        if (len < tempbufLen){
            break;
        }
        free(tempbuf);
        tempbufLen = tempbufLen * 2;
        tempbuf = (char*)malloc(tempbufLen);
    }
    va_end(args);
    return coord::Append(self, tempbuf, len);
}

}