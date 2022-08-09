
#include "coord/encrypt/des.h"
#include "coord/encrypt/base64.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/error.h"
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/modes.h>
#include <openssl/des.h>
#include <cstdio>
#include <cstring>

namespace coord {
namespace encrypt {
namespace des {


int Decrypt(unsigned char* src, size_t srcLen, const char* secret, size_t* dstLen) {
    return Decrypt(src, srcLen, secret, src, dstLen);
}

int Decrypt(char* src, size_t srcLen, const char* secret, char* dst, size_t* dstLen) {
    return Decrypt((unsigned char* )src, srcLen, secret, (unsigned char* )dst, dstLen);
}

int Decrypt(unsigned char* src, size_t srcLen, const char* secret, unsigned char* dst, size_t* dstLen) {
    DES_cblock key;  
    DES_key_schedule schedule;  
    if (srcLen % sizeof(DES_cblock) != 0) {
        printf("crypto/cipher: input not full blocks %ld\n", sizeof(DES_cblock));
		return -1;
	} 
    DES_string_to_key(secret, &key);
   // printf("ccc %d %c %s\n", sizeof(DES_cblock), key[0], secret);
    memcpy(&key, secret, sizeof(DES_cblock));
    DES_set_key_unchecked(&key, &schedule);
    for (size_t i = 0; i < srcLen; i += sizeof(DES_cblock)){
        //不拷贝，在原来字符串上进行解码
        DES_cblock* output = (const_DES_cblock*)(src + i);
        const_DES_cblock* input = (const_DES_cblock*)(dst + i);
        DES_ecb_encrypt(input, output, &schedule, DES_DECRYPT);
    }
    int paddingLen = dst[srcLen - 1];
    *dstLen = srcLen - paddingLen;
    return 0;
}

int Encrypt(byte_slice& src, const char* secret) {
    DES_cblock key;  
    DES_key_schedule schedule;  
    //对明文数据进行补码
    char padding = sizeof(DES_cblock) - src.Len()%sizeof(DES_cblock);
    if(padding > 0){
        for(char i = 0; i < padding; i++){
            coord::Append(src, &padding, 1);
        }
    }
    if (src.Len() % sizeof(DES_cblock) != 0) {
        printf("crypto/cipher: input not full blocks %ld\n", sizeof(DES_cblock));
		return -1;
	} 
    DES_string_to_key(secret, &key);
    memcpy(&key, secret, sizeof(DES_cblock));
    DES_set_key_unchecked(&key, &schedule);
    for (size_t i = 0; i < src.Len(); i+=sizeof(DES_cblock)){
        DES_cblock* output = (const_DES_cblock*)(src.Data() + i);
        const_DES_cblock* input = (const_DES_cblock*)(src.Data() + i);
        DES_ecb_encrypt(input, output, &schedule, DES_ENCRYPT);
    }
    return 0;
}



}}}
