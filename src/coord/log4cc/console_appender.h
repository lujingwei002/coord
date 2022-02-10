#pragma once 

#include "coord/log4cc/appender.h"

#include <map>

namespace coord {
namespace log4cc {

class ConsoleAppender : public Appender {
public:
    ConsoleAppender();
    virtual ~ConsoleAppender();
public:
    virtual void Log(const char* str);
};

ConsoleAppender* newConsoleAppender();

}
}

