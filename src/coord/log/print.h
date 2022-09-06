#pragma once 

#include <cstdarg>

namespace coord {

    void Errorln(const char* fmt, ...);
    void Println(const char* fmt, ...);
    void Debugln(const char* fmt, ...);


    void CoreErrorln(const char* fmt, ...);
    void CorePrintln(const char* fmt, ...);
    void CoreDebugln(const char* fmt, ...);
}



