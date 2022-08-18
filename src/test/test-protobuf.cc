

class TestProtobuf : public testing::Test {
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

TEST_F(TestProtobuf, Basic) {
    auto user = this->coord->Proto->NewMessage("test.User");
    ASSERT_NE(user, nullptr);
    user->SetString("nickname", "ljw");
    auto itemArr = user->GetRepeat("itemArr");
    ASSERT_NE(itemArr, nullptr);
    auto item1 = itemArr->AddMessage();
    item1->SetNumber("id", 100);
    auto item2 = itemArr->AddMessage();
    item2->SetNumber("count", 333);
    ASSERT_EQ(itemArr->Count(), 2);
    ASSERT_STREQ(user->ShortDebugString(), R"(nickname: "ljw" itemArr { id: 100 } itemArr { count: 333 })");
}

TEST_F(TestProtobuf, Import) {
    int err = this->coord->Proto->Import("a.proto");
    ASSERT_NE(err, 0);
}


TEST_F(TestProtobuf, Serialize) {
    auto user1 = this->coord->Proto->NewMessage("test.User");
    ASSERT_NE(user1, nullptr);
    user1->SetString("nickname", "ljw");

    coord::byte_slice buffer;
    int err = user1->Serialize(buffer);
    ASSERT_EQ(err, 0);

    auto user2 = this->coord->Proto->NewMessage("test.User");
    err = user2->ParseFrom(buffer);
    ASSERT_EQ(err, 0);

    ASSERT_EQ(user1->ByteSize(), user2->ByteSize());
}
