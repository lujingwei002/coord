#pragma once 

#include "coord/log4cc/layout.h"

#include <map>

namespace coord {
namespace log4cc {

class BasicLayout : public Layout {
public:
    BasicLayout();
    virtual ~BasicLayout();
public:
    virtual const char* format(const char* priorityName, const char* str);
};


}
}

