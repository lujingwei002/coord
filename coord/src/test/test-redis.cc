#include "coord/coord.h"
#include "coord/redis/init.h"
#include "coord/config/config.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestRedis : public testing::Test {
public:
    static void SetUpTestCase() {
       // std::cout<<"[TestHttp] SetUpTestCase()"<<std::endl;;
    }
    static void TearDownTestCase() {
        //std::cout<<"[TestHttp] TearDownTestCase()"<<std::endl;
    }

    void SetUp() {
        auto coord = coord::NewCoord();
        int err = coord->beforeTest("test/test.ini");
        ASSERT_EQ(err, 0);
        this->coord = coord;   
    }
    void TearDown() {
        int err = this->coord->afterTest();
        ASSERT_EQ(err, 0);
        delete this->coord;
    } 
public:
    coord::Coord*           coord;
};

TEST_F(TestRedis, hostError) {
    auto client = coord::redis::newClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Host = "127.0.0.11";
    ASSERT_NE(client->Connect(), 0);
}

TEST_F(TestRedis, passwordError) {
    auto client = coord::redis::newClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Password = "11";
    ASSERT_NE(client->Connect(), 0);
}

TEST_F(TestRedis, DbError) {
    auto client = coord::redis::newClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->DB = "aa";
    ASSERT_NE(client->Connect(), 0);
}

TEST_F(TestRedis, TestReplyNull) {
    auto client = coord::redis::newClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->DB = "aa";
    err = client->Connect();
    ASSERT_NE(err, 0);
    auto reply = client->AUTH("hello");
    ASSERT_TRUE(reply == nullptr);
}

TEST_F(TestRedis, TestSetGet) {
    auto client = coord::redis::newClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    err = client->Connect();
    ASSERT_EQ(err, 0);
    {
       auto reply = client->SELECT("aa");
       ASSERT_TRUE(reply.Error());
       reply = client->SELECT("3");
       ASSERT_FALSE(reply.Error());
       ASSERT_STREQ(reply.String(), "OK");
    }
    {
        auto reply = client->SET("aa", "bb");
        ASSERT_FALSE(reply.Error());
        ASSERT_STREQ(reply.String(), "OK");

        reply = client->GET("aa");
        ASSERT_FALSE(reply.Error());
        ASSERT_FALSE(reply.Empty());
        ASSERT_STREQ(reply.String(), "bb");

        reply = client->DEL("aa");
        ASSERT_FALSE(reply.Error());
        ASSERT_EQ(reply.Integer(), 1);

        reply = client->GET("aa");
        ASSERT_FALSE(reply.Error());
        ASSERT_TRUE(reply.Empty());
    }
    //printf("%s\n", this->cache->get("coord-cache").String());
}

