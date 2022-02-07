#pragma once 

#include "coord/builtin/slice.h"
#include <cstdlib>
namespace coord {
namespace encrypt {
namespace des {

int Decrypt(unsigned char* src, size_t srcLen, const char* secret, size_t* dstLen);
int Decrypt(unsigned char* src, size_t srcLen, const char* secret, unsigned char* dst, size_t* dstLen);
int Decrypt(char* src, size_t srcLen, const char* secret, char* dst, size_t* dstLen);

/// DES-ECB模式加密 64Bit为一个分组, 填充方式为PKCS5Padding
int Encrypt(byte_slice& src, const char* secret);
}

}
}