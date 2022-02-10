#pragma once 

#include <uv.h>
#include <stdint.h>
#include <string>

namespace coord {//tolua_export
namespace net {//tolua_export

class Url {
public:
    Url();
    virtual ~Url();
public:
    int Parse(const char* data, size_t len);
public:
    std::string Schema;
    std::string Host;
    uint16_t Port;
    std::string Path;
    std::string Query;
    std::string Fragment;
    std::string User;
    std::string Password;
};

}//tolua_export
}//tolua_export
