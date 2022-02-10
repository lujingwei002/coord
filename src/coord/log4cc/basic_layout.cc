#include "coord/log4cc/basic_layout.h"

#include <uv.h>

namespace coord {
namespace log4cc {

BasicLayout::BasicLayout() {

}

BasicLayout::~BasicLayout() {

}

const char* BasicLayout::format(const char* priorityName, const char* str) {
    static thread_local char buf[4096];

    uv_timeval64_t t;
    uv_gettimeofday(&t);
    struct tm *tm = localtime(&t.tv_sec);

    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d:%02d:%02d %06ld %ld %06s : %s\n", 
            tm->tm_year + 1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, 
            (long)t.tv_usec,
            uv_thread_self(),
            priorityName, str);
    return buf;
}

}
}
