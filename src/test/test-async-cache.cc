
class TestAsyncCache : public testing::Test {
public:
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


TEST_F(TestAsyncCache, TestSetGet) {
    auto client = coord::cache::newAsyncClient(coord);
    auto config = client->DefaultConfig();
    config->Port = 6379;;
    config->Host = "127.0.0.1";
    config->DB = "2";
    config->Password = "123456";
    config->ExpireTime = 0;
    auto promise = client->main();
    ASSERT_TRUE(promise);
    promise->Then([this](auto client, auto reader) {
        ASSERT_TRUE(true);
        auto promise = client->Delete("aa");
        ASSERT_TRUE(promise);
        promise->Then([this](auto client, auto reader) {
            ASSERT_FALSE(reader->Error());
            auto promise = client->Set("aa", "bb", 60);
            ASSERT_TRUE(promise);
            promise->Then([this](auto client, auto reader) {
                ASSERT_FALSE(reader->Error());
                ASSERT_STREQ(reader->String(), "OK");
                auto promise = client->Get("aa");
                ASSERT_TRUE(promise);
                promise->Then([this](auto client, auto reader) {
                    ASSERT_FALSE(reader->Error());
                    ASSERT_STREQ(reader->String(), "bb");
                    this->coord->Destory(0);
                });
                promise->Else([this](auto client, auto reader) {
                    ASSERT_TRUE(false);
                });
            });
            promise->Else([this](auto client, auto reader) {
                ASSERT_TRUE(false);
            });
        });
        promise->Else([this](auto client, auto reader) {
            ASSERT_TRUE(false);
        });
        
    });
    promise->Else([this](auto client, auto reader) {
        ASSERT_TRUE(false);
    });
    this->coord->loopTest();
}
