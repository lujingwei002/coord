#include "coord/encrypt/md5.h"
#include <openssl/md5.h>
#include <iostream>
#include <iomanip>

namespace coord {
namespace encrypt {
namespace hex {

 
/// 将数字转为16进制（小写）
static char to_hex_lower(unsigned int value) {
	return "0123456789abcdef"[value & 0xF];
}
 
/// 将数16进（大写或小写）制转为数字
static int from_hex(char c)  {
	return ((c >= '0') && (c <= '9')) ? int(c - '0') :
		((c >= 'A') && (c <= 'F')) ? int(c - 'A' + 10) :
		((c >= 'a') && (c <= 'f')) ? int(c - 'a' + 10) :
		/* otherwise */              -1;
}

int Encode(const unsigned char* src, size_t srcLen, char* dst) {
	for(size_t i = 0; i < srcLen; i++){
		dst[i*2]     = to_hex_lower(src[i] >> 4);
		dst[i*2 + 1] = to_hex_lower(src[i] & 0xf);
	}
	return 0;
}

int EncodeLen(int srcLen) {
	return srcLen * 2;
}

int Encode(const unsigned char* src, size_t srcLen, byte_slice& dst) {
    int err = dst.Reserve(srcLen * 2);
    if (err) {
        return err;
    }
    dst.Resize(srcLen * 2);
    return Encode(src, srcLen, dst.Data());
}


int DecodeLen(int srcLen) {
	return (srcLen + 1) / 2;
}

int Decode(const char* src, size_t srcLen, unsigned char* dst) {	
	unsigned char* ptr = dst + (srcLen + 1) / 2;
	bool odd_digit = true;
	for(int i = srcLen - 1; i >= 0; i--) {
		int tmp = from_hex(src[i]);
		if (tmp == -1)
			continue;
		if (odd_digit) {
			--ptr;
			*ptr = tmp;
			odd_digit = false;
		} else {
			*ptr |= tmp << 4;
			odd_digit = true;
		}
	} 
	return 0;
}

int Decode(const char* src, size_t srcLen, byte_slice& dst) {
	int err = dst.Reserve((srcLen + 1) / 2);
    if (err) {
        return err;
    }
    dst.Resize((srcLen + 1) / 2);
	return Decode(src, srcLen, (unsigned char* )dst.Data());
}

}
}
}