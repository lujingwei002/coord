#include "coord/log4cc/console_appender.h"

#include <cstdio>
#include <cstring>
#include <uv.h>

namespace coord {
namespace log4cc {

ConsoleAppender* newConsoleAppender() {
    ConsoleAppender* appender = new ConsoleAppender();
    return appender;
}

ConsoleAppender::ConsoleAppender() {

}

ConsoleAppender::~ConsoleAppender() {

}

void ConsoleAppender::Log(const char* str) {
    fprintf(stdout, str);
    fflush(stdout);
}

}
}
