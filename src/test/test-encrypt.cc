#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "coord/encrypt/base64.h"
#include "coord/encrypt/md5.h"
#include "coord/encrypt/des.h"
#include "coord/encrypt/hex.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestEncrypt : public testing::Test {
public:
    static void SetUpTestCase() {
    }
    static void TearDownTestCase() {
    }

    void SetUp() {
        coord::Coord* coord = coord::NewCoord();
        this->coord = coord;
        coord::Argv argv;
        argv.Name = "test";
        argv.ConfigPath = "test/test.ini";
        int err = coord->beforeTest(argv);
        ASSERT_EQ(err, 0);
    }

    void TearDown() {
        int err = this->coord->afterTest();
        ASSERT_EQ(err, 0);
        delete this->coord;
    } 
public:
    coord::Coord* coord;
};


TEST_F(TestEncrypt, Hex) {
    {
        unsigned char src[16] = {11};
        coord::byte_slice dst;
        int err = coord::encrypt::hex::Encode(src, 16, dst);
        ASSERT_EQ(err, 0);
        ASSERT_EQ(dst.Len(), (size_t)32);
        coord::Append(dst, 0);
        ASSERT_STREQ(dst.Data(), "0b000000000000000000000000000000");        
    }
    {
        unsigned char dst[2];
        int err = coord::encrypt::hex::Decode("0b00", 4, dst);
        ASSERT_EQ(err, 0);
        ASSERT_EQ((int)dst[0], 11);
    }
}

TEST_F(TestEncrypt, Base64) {
    {
        ASSERT_EQ(coord::encrypt::base64::EncodeLen(10), (size_t)16);
        ASSERT_EQ(coord::encrypt::base64::EncodeLen(12), (size_t)16);
        coord::byte_slice dst;
        
        int err = coord::encrypt::base64::Encode("hello", 5, dst);
        ASSERT_EQ(err, 0);
        coord::Append(dst, 0);
        ASSERT_EQ(dst.Len(), (size_t)9);
        ASSERT_STREQ(dst.Data(), "aGVsbG8=");
    }

    {
        const char* src = "aGVsbG8=";
        coord::byte_slice dst;
        int err = coord::encrypt::base64::Decode(src, 8, dst);
        ASSERT_EQ(err, 0);
        coord::Append(dst, 0);
        ASSERT_EQ(dst.Len(), (size_t)6);
        ASSERT_STREQ(dst.Data(), "hello");        
    }
}

TEST_F(TestEncrypt, Des) {
    {
        coord::byte_slice src;
        coord::Appendf(src, "helloworld");
        ASSERT_EQ(src.Len(), (size_t)10);
        int err = coord::encrypt::des::Encrypt(src, "12345678");
        ASSERT_EQ(err, 0);
        //printf("ff %ld %s\n", src.Len(), src.Data());
        coord::byte_slice dst;
        err = coord::encrypt::base64::Encode(src.Data(), src.Len(), dst);
        ASSERT_EQ(err, 0);
        coord::Append(dst, 0);
        ASSERT_STREQ(dst.Data(), "ovATL3QOQmKh0WiTqhkSbg==");
    }
    {
        coord::byte_slice src;
        int err = coord::encrypt::base64::Decode("ovATL3QOQmKh0WiTqhkSbg==", 24, src);
        size_t dstLen;
        err = coord::encrypt::des::Decrypt(src.Data(), src.Len(), "12345678", src.Data(), &dstLen);
        ASSERT_EQ(err, 0);
        src.Resize(dstLen);
        coord::Append(src, 0);
        ASSERT_STREQ(src.Data(), "helloworld");

    }

}

TEST_F(TestEncrypt, Md5) {
    unsigned char src[16];
    int err = coord::encrypt::md5::Encrypt("hello", 5, src);
    ASSERT_EQ(err, 0);
    coord::byte_slice dst;
    err = coord::encrypt::hex::Encode(src, 16, dst);
    ASSERT_EQ(err, 0);
    ASSERT_EQ(dst.Len(), (size_t)32);
    coord::Append(dst, 0);
    ASSERT_STREQ(dst.Data(), "5d41402abc4b2a76b9719d911017c592"); 
}
