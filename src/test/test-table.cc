
class TestTable : public testing::Test {
public:
    static void SetUpTestCase() {
       
    }
    static void TearDownTestCase() {
      
    }

    void SetUp() {
        coord::Coord* coord = coord::NewCoord();
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
    void HandleNull(coord::http::HttpRequest* request) {

    }
public:
    coord::Coord* coord;
};

TEST_F(TestTable, TestReflect) {
}

TEST_F(TestTable, TestReflectSetGet) {
}

TEST_F(TestTable, TestReflectSerialize) {
}

TEST_F(TestTable, TestReflectString) {
}

TEST_F(TestTable, TestReflectNumber) {
}

TEST_F(TestTable, TestReflectRef) {
}
