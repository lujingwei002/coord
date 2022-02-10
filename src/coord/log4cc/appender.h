#pragma once 

#include <map>

namespace coord {
namespace log4cc {

class Appender {
public:
    Appender();
    virtual ~Appender();
public:
    virtual void Log(const char* str) = 0;
};


}
}

