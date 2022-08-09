

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
    coord::Coord*           coord;
};

// host错误
TEST_F(TestRedis, hostError) {
    auto client = this->coord->NewRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Host = "127.0.0.11";
    ASSERT_NE(client->Connect(), 0);
}

// 密码错误
TEST_F(TestRedis, passwordError) {
    auto client = this->coord->NewRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->Password = "11";
    ASSERT_NE(client->Connect(), 0);
}

// db错误
TEST_F(TestRedis, DbError) {
    auto client = this->coord->NewRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->DB = "aa";
    ASSERT_NE(client->Connect(), 0);
}

// 空值判断
TEST_F(TestRedis, TestReplyNull) {
    auto client = this->coord->NewRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
    ASSERT_EQ(err, 0);
    *(client->DefaultConfig()) = config;
    client->DefaultConfig()->DB = "aa";
    err = client->Connect();
    ASSERT_NE(err, 0);
    auto reply = client->AUTH("hello");
    ASSERT_TRUE(reply == nullptr);
}

TEST_F(TestRedis, TestSetGet) {
    auto client = this->coord->NewRedisClient();
    coord::redis::RedisConfig config;
    int err = this->coord->Config->RedisConfig("REDIS", &config);
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

