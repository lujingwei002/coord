#pragma once 

#include <cstdlib>
#include "coord/builtin/slice.h"
namespace coord {

namespace encrypt {


int RsaPrivateDecrypt(unsigned char* data, size_t len, unsigned char *key, byte_slice& dst);

}
}