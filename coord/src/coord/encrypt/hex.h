#pragma once 

#include <cstdlib>
#include "coord/builtin/slice.h"

namespace coord {

namespace encrypt {

namespace hex {

int Encode(const unsigned char* src, size_t srcLen, byte_slice& dst);
int Encode(const unsigned char* src, size_t srcLen, char* dst);
int EncodeLen(int srcLen);

int Decode(const char* src, size_t srcLen, byte_slice& dst);
int Decode(const char* src, size_t srcLen, unsigned char* dst);
int DecodeLen(int srcLen);
}

}
}