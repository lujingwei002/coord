#pragma once 


#include <string>
namespace coordx {
    namespace string {
        int StringEscape(const char* src, size_t srcSize, char* dest, size_t* destSize);
        int StringEscape(const char* data, size_t size);
    }
}
