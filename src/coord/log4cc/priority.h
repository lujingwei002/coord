#pragma once 

#include <map>

namespace coord {
namespace log4cc {

typedef enum {
    EMERG = 0,
    FATAL = 0,
    ALERT = 100,
    CRIT = 200,
    ERROR = 300,
    WARN = 400,
    NOTICE = 500,
    INFO = 600,
    DEBUG = 700,
    NOTSET = 800,
    ALL = 1000,
} PriorityLevel;

PriorityLevel IntPriority(const char* name);

}
}

