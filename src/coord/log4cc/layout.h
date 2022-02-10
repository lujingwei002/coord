#pragma once 

#include <map>

namespace coord {
namespace log4cc {

class Layout {
public:
    Layout();
    virtual ~Layout();
public:
    virtual const char* format(const char* priorityName, const char* str) = 0;
};


}
}

