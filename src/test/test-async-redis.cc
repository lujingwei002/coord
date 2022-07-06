#include "coord/coord.h"
#include "coord/redis/init.h"
#include "gtest/gtest.h"
#include "coord/action/init.h"
#include "coord/config/config.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestAsyncRedis : public testing::Test {
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
    coord::Coord*               coord;
};

TEST_F(TestAsyncRedis, DbError) {
    auto client = coord::redis::newAsyncClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->DB = "aa";
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(false);
    });
    promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(true);
    });
    this->coord->loopTest();
}

TEST_F(TestAsyncRedis, hostError) {
    auto client = coord::redis::newAsyncClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Host = "127.0.0.11";
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(false);
    });
    promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(true);
    });
    this->coord->loopTest();
}

TEST_F(TestAsyncRedis, passwordError) {
    auto client = coord::redis::newAsyncClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Password = "11";
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(false);
    });
    promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(true);
    });

    this->coord->loopTest();
}

TEST_F(TestAsyncRedis, Action) {
    auto client = coord::redis::newAsyncClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;

    auto anim = this->coord->Action->Begin();
    anim->Run(anim->Sequence(
        anim->Call([this, client](coord::action::Action* action){
            auto promise = client->Connect();
            promise->Then([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                action->Next();
            });
            promise->Else([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            auto promise = client->DEL("aa");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_FALSE(reply.Error());
                ASSERT_FALSE(reply.Empty());
                action->Next();
            });
            promise->Else([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            auto promise = client->GET("aa");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_FALSE(reply.Error());
                ASSERT_TRUE(reply.Empty());
                action->Next();
            });
            promise->Else([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            auto promise = client->SET("aa", "bb");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_FALSE(reply.Error());
                ASSERT_FALSE(reply.Empty());
                ASSERT_STREQ(reply.String(), "OK");
                action->Next();
            });
            promise->Else([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            auto promise = client->DEL("aa");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_FALSE(reply.Error());
                ASSERT_FALSE(reply.Empty());
                ASSERT_EQ(reply.Integer(), 1);
                action->Next();
                this->coord->Destory(0);
            });
            promise->Else([this, action](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        nullptr
    ));
    this->coord->loopTest();
}

TEST_F(TestAsyncRedis, setGet) {
    auto client = coord::redis::newAsyncClient(coord);
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        auto promise = client->DEL("aa");
        ASSERT_NE(promise, nullptr);
        promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
            auto promise = client->GET("aa");
            ASSERT_TRUE(promise);
            promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_FALSE(reply.Error());
                ASSERT_TRUE(reply.Empty());
                auto promise = client->SET("aa", "bb");
                ASSERT_TRUE(promise);
                promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                    ASSERT_FALSE(reply.Error());
                    ASSERT_FALSE(reply.Empty());
                    ASSERT_STREQ(reply.String(), "OK");
                    auto promise = client->GET("aa");
                    ASSERT_TRUE(promise);
                    promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                        ASSERT_FALSE(reply.Error());
                        ASSERT_FALSE(reply.Empty());
                        ASSERT_STREQ(reply.String(), "bb");
                        auto promise = client->DEL("aa");
                        ASSERT_TRUE(promise);
                        promise->Then([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                            ASSERT_FALSE(reply.Error());
                            ASSERT_FALSE(reply.Empty());
                            ASSERT_EQ(reply.Integer(), 1);
                            this->coord->Destory(0);
                        });
                        promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                            ASSERT_TRUE(false);
                        });
                    });
                    promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                        ASSERT_TRUE(false);
                    });
                });
                promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                    ASSERT_TRUE(false);
                });
            });
            promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
                ASSERT_TRUE(false);
            });
        });
        promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
            ASSERT_TRUE(false);
        });
    }); 
    promise->Else([this](coord::redis::AsyncClient* client, coord::redis::Reply& reply) {
        ASSERT_TRUE(false);
    });

    this->coord->loopTest();
    //printf("%s\n", this->cache->get("coord-cache").String());
}

