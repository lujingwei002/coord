#include "coord/encrypt/md5.h"
#include <openssl/md5.h>
#include <iostream>
#include <iomanip>

namespace coord {
namespace encrypt {
namespace md5 {

int Encrypt(const unsigned char* src, size_t srcLen, unsigned char dst[16]) {
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, src, srcLen);
    MD5_Final(dst, &c);
    return 0;
}

int Encrypt(const char* src, size_t srcLen, unsigned char dst[16]) {
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, src, srcLen);
    MD5_Final(dst, &c);
    return 0;
}

int Encrypt(byte_slice& src, unsigned char dst[16]) {
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, src.Data(), src.Len());
    MD5_Final(dst, &c);
    return 0;
}

}
}
}