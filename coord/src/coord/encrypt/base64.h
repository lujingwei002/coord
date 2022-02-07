#pragma once 

#include <cstdlib>
#include "coord/builtin/slice.h"

namespace coord {
namespace encrypt {

namespace base64 {

size_t EncodeLen(size_t len);
size_t DecodeLen(size_t len);

int Encode(const unsigned char* src, size_t srcLen, unsigned char* dst, size_t* dstLen);
int Encode(const char* src, size_t srcLen, char* dst, size_t* dstLen);
int Encode(const char* src, size_t srcLen, byte_slice& dst);

int Decode(const unsigned char* src, size_t srcLen, unsigned char* dst, size_t* dstLen);
int Decode(const char* src, size_t srcLen, byte_slice& dst);

}

}
}