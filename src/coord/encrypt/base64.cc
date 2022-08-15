

#include "coord/encrypt/base64.h"
#include "coord/coordx.h"
#include <cstdio>
#include <cmath>

namespace coord {
namespace encrypt {
namespace base64 {

static unsigned char alphabet_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static unsigned char reverse_map[] = {
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
     255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63,
     52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255, 255, 255, 255, 255,
     255,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
     15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255,
     255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
     41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 255, 255, 255, 255, 255
};

int Encode(const unsigned char* src, size_t srcLen, unsigned char *dst, size_t* dstLen) {
    size_t i, j;
    for (i = 0, j = 0; i + 3 <= srcLen; i += 3) {
        dst[j++] = alphabet_map[src[i]>>2];                             // 取出第一个字符的前6位并找出对应的结果字符
        dst[j++] = alphabet_map[((src[i]<<4)&0x30)|(src[i+1]>>4)];      // 将第一个字符的后2位与第二个字符的前4位进行组合并找到对应的结果字符
        dst[j++] = alphabet_map[((src[i+1]<<2)&0x3c)|(src[i+2]>>6)];    // 将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        dst[j++] = alphabet_map[src[i+2]&0x3f];                         // 取出第三个字符的后6位并找出结果字符
    }
    if (i < srcLen) {
        size_t tail = srcLen - i;
        if (tail == 1){
            dst[j++] = alphabet_map[src[i]>>2];
            dst[j++] = alphabet_map[(src[i]<<4)&0x30];
            dst[j++] = '=';
            dst[j++] = '=';
        } else { //tail==2
            dst[j++] = alphabet_map[src[i]>>2];
            dst[j++] = alphabet_map[((src[i]<<4)&0x30)|(src[i+1]>>4)];
            dst[j++] = alphabet_map[(src[i+1]<<2)&0x3c];
            dst[j++] = '=';
        }
    }
    *dstLen = j;
    return 0;
}

int Encode(const char* src, size_t srcLen, char* dst, size_t* dstLen) {
    return Encode((const unsigned char*)src, srcLen, (unsigned char*)dst, dstLen);
}

int Encode(const char* src, size_t srcLen, byte_slice& dst) {
    int err = dst.Reserve(EncodeLen(srcLen));
    if (err) {
        return err;
    }
    size_t dstLen;
    err = Encode(src, srcLen, dst.Data(), &dstLen);
    if (err) {
        return err;
    }
    dst.Resize(dstLen);
    return 0;
}

size_t DecodeLen(size_t srcLen) {
	return (srcLen / 4 * 3);
}

size_t EncodeLen(size_t srcLen) {
	return ceil(srcLen / 3.0) * 4;
}

int Decode(const unsigned char* src, size_t srcLen, unsigned char *dst, size_t* dstLen){
    if((srcLen&0x03) != 0) {
		return -1;
	}
    size_t i, j = 0;
    unsigned char quad[4];
    for (i = 0; i < srcLen; i+=4) {
        for (int k = 0; k < 4; k++) {
            quad[k] = reverse_map[src[i+k]];//分组，每组四个分别依次转换为base64表内的十进制数
        }
        if(!(quad[0]<64 && quad[1]<64)) {
			return -1;
		}
        dst[j++] = (quad[0]<<2)|(quad[1]>>4); //取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的前2位进行组合
        if (quad[2] >= 64) {
            break;
        } else if (quad[3] >= 64){
            dst[j++] = (quad[1]<<4)|(quad[2]>>2); //取出第二个字符对应base64表的十进制数的后4位与第三个字符对应base64表的十进制数的前4位进行组合
            break;
        } else{
            dst[j++] = (quad[1]<<4)|(quad[2]>>2);
            dst[j++] = (quad[2]<<6)|quad[3];//取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
        }
    }
	*dstLen = j;
    return 0;
}

int Decode(const char* src, size_t srcLen, byte_slice& dst) {
    int err = dst.Reserve(DecodeLen(srcLen));
	if (err) {
        return err;
    }
	size_t dstLen = 0;
	err = Decode((const unsigned char*)src, srcLen, (unsigned char *)dst.Data(), &dstLen);
	if (err != 0){
		return err;
	}
	dst.Resize(dstLen);
	return 0;
}



}}}