

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
        coord::Argv argv;
        argv.Name = "test";
        argv.ConfigPath = "test/test.ini";
        int err = coord->beforeTest(argv);
        ASSERT_EQ(err, 0);
        this->coord = coord;
    }
    void TearDown() {
        int err = this->coord->afterTest();
        ASSERT_EQ(err, 0);
        delete this->coord;
    } 
public:
    coord::Coord*   coord;
};

// db错误
TEST_F(TestAsyncRedis, DbError) {
    auto client = this->coord->NewAsyncRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->DB = "aa";
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(false);
        this->coord->Destory(0);
    })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(true);
        this->coord->Destory(0);
    });
    this->coord->loopTest();
}

// host错误
/*
TEST_F(TestAsyncRedis, hostError) {
    auto client = this->coord->NewAsyncRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Port = 3000;
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(false);
        this->coord->Destory(0);
    })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(true);
        this->coord->Destory(0);
    });
    this->coord->loopTest();
}*/

// password错误
TEST_F(TestAsyncRedis, passwordError) {
    auto client = this->coord->NewAsyncRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Password = "11";
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(false);
        this->coord->Destory(0);
    })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(true);
        this->coord->Destory(0);
    });
    this->coord->loopTest();
}

TEST_F(TestAsyncRedis, Action) {
    auto client = this->coord->NewAsyncRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;

    auto anim = this->coord->Action->Begin();
    anim->Run(anim->Sequence(
        anim->Call([this, client](coord::action::Action* action){
            //连接
            auto promise = client->Connect();
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(true);
                action->Next();
            })->Else([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(false);
                this->coord->Destory(0);
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            // del aa
            auto promise = client->DEL("aa");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(true);
                ASSERT_FALSE(reply->Error());
                ASSERT_FALSE(reply->Empty());
                action->Next();
            })->Else([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            // get aa
            auto promise = client->GET("aa");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_FALSE(reply->Error());
                ASSERT_TRUE(reply->Empty());
                action->Next();
            })->Else([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            // set aa bb
            auto promise = client->SET("aa", "bb");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_FALSE(reply->Error());
                ASSERT_FALSE(reply->Empty());
                ASSERT_STREQ(reply->String(), "OK");
                action->Next();
            })->Else([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        anim->Call([this, client](coord::action::Action* action){
            // del aa
            auto promise = client->DEL("aa");
            ASSERT_TRUE(promise);
            promise->Then([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_FALSE(reply->Error());
                ASSERT_FALSE(reply->Empty());
                ASSERT_EQ(reply->Integer(), 1);
                action->Next();
                this->coord->Destory(0);
            })->Else([this, action](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(false);
                action->Next();
            });
        }),
        nullptr
    ));
    this->coord->loopTest();
}

TEST_F(TestAsyncRedis, setGet) {
    auto client = this->coord->NewAsyncRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    auto promise = client->Connect();
    ASSERT_NE(promise, nullptr);
    promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        auto promise = client->DEL("aa");
        ASSERT_NE(promise, nullptr);
        promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
            auto promise = client->GET("aa");
            ASSERT_TRUE(promise);
            promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_FALSE(reply->Error());
                ASSERT_TRUE(reply->Empty());
                auto promise = client->SET("aa", "bb");
                ASSERT_TRUE(promise);
                promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                    ASSERT_FALSE(reply->Error());
                    ASSERT_FALSE(reply->Empty());
                    ASSERT_STREQ(reply->String(), "OK");
                    auto promise = client->GET("aa");
                    ASSERT_TRUE(promise);
                    promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                        ASSERT_FALSE(reply->Error());
                        ASSERT_FALSE(reply->Empty());
                        ASSERT_STREQ(reply->String(), "bb");
                        auto promise = client->DEL("aa");
                        ASSERT_TRUE(promise);
                        promise->Then([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                            ASSERT_FALSE(reply->Error());
                            ASSERT_FALSE(reply->Empty());
                            ASSERT_EQ(reply->Integer(), 1);
                            this->coord->Destory(0);
                        })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                            ASSERT_TRUE(false);
                        });
                    })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                        ASSERT_TRUE(false);
                    });
                })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                    ASSERT_TRUE(false);
                });
            })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
                ASSERT_TRUE(false);
            });
        })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
            ASSERT_TRUE(false);
        });
    })->Else([this](coord::redis::AsyncClient* client, const coord::redis::RedisResult* reply) {
        ASSERT_TRUE(false);
    });

    this->coord->loopTest();
    //printf("%s\n", this->cache->get("coord-cache").String());
}

