


class TestScript : public testing::Test {
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

TEST_F(TestScript, Basic) {
    auto& script = this->coord->Script;
}

TEST_F(TestScript, Function) {
    auto& script = this->coord->Script;
}

TEST_F(TestScript, Error) {
    auto& script = this->coord->Script;
}


TEST_F(TestScript, ToString) {
    auto& script = this->coord->Script;
}


TEST_F(TestScript, Serialize) {
    auto& script = this->coord->Script;
}
 
TEST_F(TestScript, ToJSON) {
    auto& script = this->coord->Script;
} 

TEST_F(TestScript, SetGet) {
    auto& script = this->coord->Script;
}
