#pragma once 

#include "coord/builtin/slice.h"
#include <string>
#include <libuv/uv.h>

namespace coord {
namespace http {
    
enum HttpMethod {
    HttpMethod_GET = 1,
    HttpMethod_POST = 2,
};

class HttpException {
public:
    HttpException(const char* msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

class HttpPageNotFoundException {
public:
    HttpPageNotFoundException(const char* msg):msg(msg){
    }
    const char* What() const {
        return this->msg.c_str();
    }
private:
    std::string msg;
};

enum HttpStatusCode {
    HttpStatusCode_OK =         200,
    HttpStatusCode_NotModify =  304,
};

const char* GetContentType(const char* ext);

int GetFileETag(byte_slice& data, byte_slice& etag);
const char* FromUnixTime(int64_t t);
int64_t UnixTimeStamp(const char *date);

}
}


