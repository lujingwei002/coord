#include "coord/coord.h"
#include "coord/cache/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestCache : public testing::Test {
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
        auto cache = coord::cache::newClient(coord);
        auto config = cache->DefaultConfig();
        config->Port = 6379;;
        config->Host = "127.0.0.1";
        config->DB = "2";
        config->Password = "123456";
        config->ExpireTime = 0;
        err = cache->main();
        ASSERT_EQ(err, 0);
        this->coord = coord;
        this->cache = cache;    
    }
    void TearDown() {
        int err = this->coord->afterTest();
        ASSERT_EQ(err, 0);
        delete this->coord;
    } 
public:
    coord::Coord*           coord;
    coord::cache::Client*   cache;
};


TEST_F(TestCache, TestSetGet) {
    {
        int err = this->cache->Set("coord-cache", "hello", 60);
        ASSERT_EQ(err, 0);
        auto reader =  this->cache->Get("coord-cache");
        ASSERT_FALSE(reader.Error());
        ASSERT_FALSE(reader.Empty());
        ASSERT_STREQ(reader.String(), "hello");
        err = this->cache->Delete("coord-cache");
        ASSERT_EQ(err, 0);
        reader =  this->cache->Get("coord-cache");
        ASSERT_FALSE(reader.Error());
        ASSERT_TRUE(reader.Empty());
    }
    {
        auto reader =  this->cache->Get("coord-cache2");
        ASSERT_FALSE(reader.Error());
        ASSERT_TRUE(reader.Empty());
    }
    //printf("%s\n", this->cache->get("coord-cache").String());
}