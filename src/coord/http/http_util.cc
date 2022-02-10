#include "coord/http/http_util.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
namespace coord {
namespace http {
    #define NON_NUM '0'

    static int hex2num(char c){
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'a' && c <= 'z') return c - 'a' + 10;
        if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
        return NON_NUM;
    }

    int UrlDecode(const char *source, const int sourceLen, char *result, const int resultLen){
        char ch, ch1, ch2;
        int i;
        int j = 0;
        if ((source == NULL) || (result == NULL) || (sourceLen <= 0) || (resultLen <= 0)) {
            return 0;
        }
        for (i = 0; i < sourceLen && j < resultLen; ++i) {
            ch = source[i];
            switch (ch) {
                case '+':
                    result[j++] = ' ';
                    break;
                case '%':
                    if (i + 2 < sourceLen) {
                        ch1 = hex2num(source[i + 1]);
                        ch2 = hex2num(source[i + 2]);
                        if ((ch1 != NON_NUM) && (ch2 != NON_NUM)) {
                            result[j++] = (char)((ch1 << 4) | ch2);
                        }
                        i += 2;
                        break;
                    } else {
                        break;
                    }
                default:
                    result[j++] = ch;
                    break;
            }
        }
        result[j] = 0;
        return j;
    }

    int UrlEncode(const char *source, const int sourceLen, char *result, const int resultLen){
        int i;
        int j = 0;
        char ch;

        if ((source == NULL) || (result == NULL) || (sourceLen <= 0) || (resultLen <= 0)) {
            return 0;
        }
        for (i = 0; i < sourceLen && j < resultLen; ++i) {
            ch = source[i];
            if (((ch >= 'A') && (ch < 'Z')) ||
                    ((ch >= 'a') && (ch < 'z')) ||
                    ((ch >= '0') && (ch < '9'))) {
                result[j++] = ch;
            } else if (ch == ' '){
                result[j++] = '+';
            } else if (ch == '.' || ch == '-' || ch == '_' || ch == '*') {
                result[j++] = ch;
            } else {

                if (j + 3 < resultLen) 
                {
                    sprintf(result + j, "%%%02X", (unsigned char)ch);
                    j += 3;
                } else 
                {
                    return 0;
                }
            }
        }
        result[j] = '\0';
        return j;
    }
}
}