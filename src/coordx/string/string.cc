#include "coordx/string/string.h"
#include "coordx/error/error.h"

namespace coordx {
    namespace string {

    int StringEscape(const char* data, size_t size) {
        char* dest = (char*)data;
        size_t destSize = size;
        int err = StringEscape(data, size, dest, &destSize);
        if (err) {
            return err;
        }
        return destSize;
    }

    int StringEscape(const char* src, size_t srcSize, char* dest, size_t* destSize) {
        size_t j = 0;
        for (size_t i = 0; i < srcSize; i++) {
            if (src[i] == '\\' && i < srcSize - 1) {
                char c = src[i + 1];
                if (c == '"') {
                    dest[j++] = '"';
                } else if (c == 'n') {
                    dest[j++] = '\n';
                } else if (c == '\\') {
                    dest[j++] = '\\';
                } else if (c == 'a') {
                    dest[j++] = '\a';
                } else if (c == 'r') {
                    dest[j++] = '\r';
                } else if (c == 'b') {
                    dest[j++] = '\b';
                } else if (c == 'f') {
                    dest[j++] = '\f';
                } else if (c == 'v') {
                    dest[j++] = '\v';
                } else if (c == 't') {
                    dest[j++] = '\t';
                } else {
                    return ErrorInvalidArg;
                }
                if (j >= *destSize) {
                    return ErrorInvalidArg;
                }
                i = i + 1;
            } else {
                dest[j++] = src[i];
            }
        }
        *destSize = j;
        return 0;
    }

    }
}
