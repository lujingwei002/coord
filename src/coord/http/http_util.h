#pragma once 

namespace coord {
namespace http {
    int UrlDecode(const char *source, const int sourceLen, char *result, const int resultLen);
    int UrlEncode(const char *source, const int sourceLen, char *result, const int resultLen);
}
}

