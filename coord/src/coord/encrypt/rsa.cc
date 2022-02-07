
#include "coord/encrypt/rsa.h"
#include "coord/encrypt/base64.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/error.h"
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <cstdio>


namespace coord {

namespace encrypt {


static RSA* createRSA(unsigned char *key, int isPublic){
    RSA *rsa= NULL;
    BIO *keybio ;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio==NULL){
        printf( "Failed to create key BIO");
        return 0;
    }
    if(isPublic){
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    } else{
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    }
    if(rsa == NULL){
        printf( "Failed to create RSA");
    }
    return rsa;
}
 
static RSA* createPrivateKey(unsigned char *key){
    RSA *rsa= NULL;
    BIO *keybio ;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio == NULL){
        printf( "Failed to create key BIO");
        return NULL;
    }
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    if(rsa == NULL){
        printf( "Failed to create RSA");
        return NULL;
    }
    return rsa;
}
 
static void printLastError(char *msg) {
    char* err = (char*)malloc(130);;
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    printf("%s ERROR: %s\n",msg, err);
    free(err);
}

int RsaPrivateDecrypt(unsigned char *src, size_t srcLen, unsigned char* key, byte_slice& dst) {//unsigned char *decrypted){
    static thread_local byte_slice encryptData(0, 0);
    //base64解密
    int err = encrypt::base64::Decode((const char*)src, srcLen, encryptData);
    if(err < 0){
        return err;
    }
    RSA* rsa = createPrivateKey(key);
    //根据RSA_size进行分段
    size_t rsaSize = RSA_size(rsa);
    for(size_t i = 0; i < encryptData.Len(); i += rsaSize){
        dst.Reserve(i + rsaSize);
        size_t blockSize = encryptData.Len() - i < rsaSize ? encryptData.Len() - i : rsaSize;
        int dstLen = RSA_private_decrypt(blockSize, (const unsigned char*)encryptData.Data() + i, (unsigned char*)dst.Data() + i, rsa, RSA_PKCS1_PADDING);
        if (dstLen < 0){
            printf("Private Decrypt failed \n");
            printLastError("Private Decrypt failed ");
            RSA_free(rsa);
            return ErrorUnknown;
        }
        dst.Resize(i + dstLen);
    }
    RSA_free(rsa);
    return 0;
}






}
}