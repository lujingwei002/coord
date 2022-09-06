

class TestJson : public testing::Test {
public:
    static void SetUpTestCase() {
    }
    static void TearDownTestCase() {
    }

    void SetUp() {
    }

    void TearDown() {
    } 
public:
};

TEST_F(TestJson, Basic) {
    // {}
    auto json = coorda->Json->NewObject();  
    // 获取不存在的字段
    ASSERT_EQ(json->GetString("version"), nullptr);
    // {"version": "1.0.0"}
    json->SetString("version", "1.0.0");
    // 获取字符串字段
    ASSERT_STREQ(json->GetString("version"), "1.0.0");
    // {"version": "1.0.0", "score": 1.23}
    json->SetNumber("score", 1.23);

    // {"version": "1.0.0", "score": 1.23, "user": {}}
    auto user = json->SetObject("user");
    // {"version": "1.0.0", "score": 1.23, "user": {"name": "ljw"}}
    user->SetString("name", "ljw");

    // 获取不存在的字段
    auto dd = json->GetObject("dd");
    ASSERT_TRUE(dd == nullptr);
    // 获取object字段
    user = json->GetObject("user");
    ASSERT_TRUE(user != nullptr);
    // 获取字符串字段
    ASSERT_STREQ(user->GetString("name"), "ljw");

    // 设置数组字段
    // {"version": "1.0.0", "score": 1.23, "user": {"name": "ljw"}, "gameArr": []}
    auto gameArr = json->SetArray("gameArr");
    // {"version": "1.0.0", "score": 1.23, "user": {"name": "ljw"}, "gameArr": [{}]}
    auto game1 = gameArr->AddObject();
    // {"version": "1.0.0", "score": 1.23, "user": {"name": "ljw"}, "gameArr": [{"name": "game1"}]}
    game1->SetString("name", "game1");

    // 序列化 -》 反序列化
    std::string str1 = json->ToString();
    auto json2 = coorda->Json->Parse(str1);
    // 序列化
    std::string str2 = json2->ToString();
    ASSERT_STREQ(str2.c_str(), R"({"gameArr": [{"name": "game1"}], "score": 1.23, "user": {"name": "ljw"}, "version": "1.0.0"})");
    ASSERT_STREQ(str1.c_str(), str2.c_str());
}

TEST_F(TestJson, Array) {
    auto json = coorda->Json->NewArray();   
    auto book1 = json->AddObject();
    book1->SetString("name", "c++");
    auto book2 = json->AddObject();
    book2->SetString("name", "lua");
    ASSERT_EQ(json->Count(), 2);
    ASSERT_STREQ(json->ToString(), R"([{"name": "c++"}, {"name": "lua"}])");
}

TEST_F(TestJson, String) {
    auto json1 = coorda->Json->NewString();   
    ASSERT_STREQ(json1->ToString(), R"("")");
    auto json2 = coorda->Json->NewString("hello");   
    ASSERT_STREQ(json2->ToString(), R"("hello")");
}

TEST_F(TestJson, Null) {
    auto json1 = coorda->Json->NewNull();   
    ASSERT_STREQ(json1->ToString(), R"(null)");
}

TEST_F(TestJson, Bool) {
    auto json1 = coorda->Json->NewBool(true);   
    ASSERT_STREQ(json1->ToString(), R"(true)");
}

TEST_F(TestJson, Parse) {
    auto json = coorda->Json->Parse(R"({"nickname": "ljw"})");
    ASSERT_STREQ(json->ToString(), R"({"nickname": "ljw"})");
}
