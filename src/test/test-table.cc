
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
    this->coord->Script->SetGlobal("aa.bb", "hello");

    // // local user1 = _G.aa.bb
    auto user1 = this->coord->Script->GetVariable("aa.bb");

    ASSERT_STREQ(user1.ShortDebugString(), "'hello'");

    // local user2 = _G.aa.bb
    auto user2 = this->coord->Script->GetVariable("aa.bb");
    ASSERT_STREQ(user2.ShortDebugString(), "'hello'");

    // local user3 = _G.aa
    auto user3 = this->coord->Script->GetVariable("aa");
    ASSERT_STREQ(user3.ShortDebugString(), "{'bb'='hello',}");

    // user3.bb = 'hello2'
    user3.Set("bb", "hello2");
    ASSERT_STREQ(user3.ShortDebugString(), "{'bb'='hello2',}");

    ASSERT_STREQ(user2.ShortDebugString(), "'hello'");
}

TEST_F(TestTable, TestReflectSetGet) {
    // _G.aa.bb = {1, 2} 
    this->coord->Script->SetGlobal("aa.user1", {1, "2"});

    // local user1 = _G.aa.bb
    auto user1 = this->coord->Script->GetVariable("aa.user1");
    ASSERT_STREQ(user1.ShortDebugString(), "{[1]=1.000000,[2]='2',}");
    // _G.aa.bb = {} 
    this->coord->Script->SetGlobal("aa.user2", {});

    // local user2 = _G.aa.bb
    auto user2 = this->coord->Script->GetVariable("aa.user2");
    ASSERT_STREQ(user2.ShortDebugString(), "{}");
    ASSERT_TRUE(user2.IsTable());
    // user2 = 123
    user2 = 123;
    printf("fff %s\n", user2.ShortDebugString());
    // user2 = 'abc'
    user2 = "abc";
    printf("fff %s\n", user2.ShortDebugString());
    // user2 = true
    user2 = true;
    printf("fff %s\n", user2.ShortDebugString());
    // user2 = nil
    user2 = nullptr;
    printf("fff %s\n", user2.ShortDebugString());
    // user2 = {}
    user2 = {};
    printf("fff %s\n", user2.ShortDebugString());
    user2 = {{1, "2"}};
    printf("fff %s\n", user2.ShortDebugString());
    user2 = {{1, "2"}, {"2", "3"}};
   // user2 = {1, "2"};
    printf("fff %s\n", user2.ShortDebugString());
}

TEST_F(TestTable, TestReflectSerialize) {
}

TEST_F(TestTable, TestReflectString) {
}

TEST_F(TestTable, TestReflectNumber) {
}

TEST_F(TestTable, TestReflectRef) {
}
