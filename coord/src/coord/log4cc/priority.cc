#include "coord/log4cc/priority.h"
#include <map>
#include <string>
namespace coord {
namespace log4cc {

std::map<std::string, PriorityLevel> int_priority_dict = {
    {"emerg",   EMERG},
    {"fatal",   FATAL},
    {"alert",   ALERT},
    {"crit",    CRIT},
    {"error",   ERROR},
    {"warn",    WARN},
    {"notice",  NOTICE},
    {"info",    INFO},
    {"debug",   DEBUG},
    {"all",     ALL},
};

PriorityLevel IntPriority(const char* name) {
    auto it = int_priority_dict.find(name);
    if (it == int_priority_dict.end()) {
        return ALL;
    }
    return it->second;
}

}
}
