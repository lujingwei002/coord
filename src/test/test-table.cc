
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
    // _G.aa.bb = 'hello' 
    // local user1 = _G.aa.bb
    auto user1 = this->coord->Script->NewVariable("aa.bb", "hello");

    ASSERT_STREQ(user1.ToShortString(), "'hello'");

    // local user2 = _G.aa.bb
    auto user2 = this->coord->Script->GetVariable("aa.bb");
    ASSERT_STREQ(user2.ToShortString(), "'hello'");

    // local user3 = _G.aa
    auto user3 = this->coord->Script->GetVariable("aa");
    ASSERT_STREQ(user3.ToShortString(), "{'bb'='hello',}");

    // user3.bb = 'hello2'
    user3.Set("bb", "hello2");
    ASSERT_STREQ(user3.ToShortString(), "{'bb'='hello2',}");

    ASSERT_STREQ(user2.ToShortString(), "'hello'");
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
