#pragma once 

#include <cstdlib>
#include "coord/coordx.h"

namespace coord {

namespace encrypt {

namespace md5 {

/// #example
/// unsigned char md5[16] = {0};
/// char hex[33] = {0};
/// int err = coord::encrypt::md5::Encrypt("hello", 5, md5);
/// err = coord::encrypt::hex::Encode(md5, 16, hex);
///
///

/// 计算src的md5值，保存到dst中
int Encrypt(byte_slice& src, unsigned char dst[16]);
/// 计算src的md5值，保存到dst中
int Encrypt(const unsigned char* src, size_t srcLen, unsigned char dst[16]);
/// 计算src的md5值，保存到dst中
int Encrypt(const char* src, size_t srcLen, unsigned char dst[16]);

}

}
} 