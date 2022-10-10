

class TestCluster : public testing::Test {
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

TEST_F(TestCluster, Basic) {
    auto cluster = coord::cluster::newCluster(this->coord);
    //coord::cluster::ClusterConfig* config = cluster->DefaultConfig();
    int err = cluster->main();
    ASSERT_EQ(err, 0);
    cluster->Router->Request("test.req", [this](coord::cluster::Request* request){
        printf("recv request %s\n", request->String());
        auto response = request->GetResponse();
        response->String("world");
    });
    auto promise = cluster->Request("gamesvr_1", "test.req", "hello");
    promise->Then([this](coord::cluster::Result* result){
        printf("recv result %p\n", result);
        printf("%s\n", result->String());
    });
    //coorda->loopTest();
}

 
