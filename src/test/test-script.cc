


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
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));
    ASSERT_TRUE(script->IsNil("a.b.c"));
    ASSERT_EQ(script->GetString("a.b.c"), nullptr);
    ASSERT_EQ(script->SetString("a.b.c", "hello"), 0);
    ASSERT_TRUE(script->IsTable("a"));
    ASSERT_TRUE(script->IsTable("a.b"));
    ASSERT_TRUE(script->IsString("a.b.c"));
    ASSERT_STREQ(script->GetString("a.b.c"), "hello");
    ASSERT_TRUE(script->IsTable("a"));
    ASSERT_TRUE(script->IsTable("a.b"));
    ASSERT_TRUE(script->IsString("a.b.c"));
    ASSERT_EQ(script->SetNil("a.b.c"), 0);
    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));
    ASSERT_TRUE(script->IsNil("a.b.c"));
    ASSERT_EQ(lua_gettop(script->L), 0);
}

TEST_F(TestScript, Function) {
    auto& script = this->coord->Script;
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("test_script.test_function"));
    ASSERT_NE(script->DoString(R"(
        a + 11b = 1
    )"), 0);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->DoString(R"(
        test_script = {}
        test_script.test_function = function(a, b)
            return a + b
        end
    )"), 0);
    ASSERT_TRUE(script->IsFunction("test_script.test_function"));
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->GetFunction("test_script.test_function"), 0);
    lua_pushnumber(script->L, 1);
    lua_pushnumber(script->L, 2);
    ASSERT_EQ(lua_gettop(script->L), 3);
    ASSERT_EQ(lua_pcall(script->L, 2, 1, 0), 0);
    ASSERT_EQ(lua_gettop(script->L), 1);
    ASSERT_EQ(lua_tointeger(script->L, -1), 3);
    
}

TEST_F(TestScript, Error) {
    auto& script = this->coord->Script;
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));
    ASSERT_EQ(script->SetString("a.", "hello"), 0);
    ASSERT_STREQ(script->GetString("a."), "hello");
    ASSERT_TRUE(script->IsTable("a"));
    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));

    ASSERT_EQ(script->SetString("a.1b", "hello"), 0);
    ASSERT_STREQ(script->GetString("a.1b"), "hello");
    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.1b"));
}


TEST_F(TestScript, ToString) {
    auto& script = this->coord->Script;
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));
    ASSERT_TRUE(script->IsNil("a.b.c"));
    ASSERT_EQ(script->GetString("a.b.c"), nullptr);
    ASSERT_EQ(script->SetString("a.b.c", "hello"), 0);
    ASSERT_EQ(script->SetNumber("a.b.d", 1), 0);
    ASSERT_EQ(script->SetTable("a.b.t"), 0);
    auto t = script->Get("a.b.t");
    t.SetString("nickname", "ljw");
    t.SetString("avatar", "xx");
    t.SetNumber("score", 100);
    ASSERT_STREQ(script->ToShortString("a"), R"({'b'={'d'=1.000000,'c'='hello','t'={'nickname'='ljw','score'=100.000000,'avatar'='xx',},},})");
    ASSERT_EQ(lua_gettop(script->L), 0);
}


TEST_F(TestScript, Serialize) {
    auto& script = this->coord->Script;
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));
    ASSERT_TRUE(script->IsNil("a.b.c"));
    ASSERT_EQ(script->GetString("a.b.c"), nullptr);
    ASSERT_EQ(script->SetString("a.b.c", "hello"), 0);
    ASSERT_EQ(script->SetNumber("a.b.d", 1), 0);
    ASSERT_EQ(script->SetTable("a.b.t"), 0);
    auto t = script->Get("a.b.t");
    t.SetString("nickname", "ljw");
    t.SetString("avatar", "xx");
    t.SetNumber("score", 100);

    coord::byte_slice buffer;
    ASSERT_EQ(script->Encode("a", buffer), 0);
    ASSERT_EQ(lua_gettop(script->L), 0);

    ASSERT_EQ(script->Decode("b", buffer),  0);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_STREQ(script->ToShortString("b"), R"({'b'={'d'=1.000000,'c'='hello','t'={'nickname'='ljw','score'=100.000000,'avatar'='xx',},},})");
    //script->GetTable("a");
    //ASSERT_EQ(lua_gettop(script->L), 1);
}
 
TEST_F(TestScript, ToJSON) {
    auto& script = this->coord->Script;
    //lua_pop(script->L, 1);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_TRUE(script->IsNil("a.b"));
    ASSERT_TRUE(script->IsNil("a.b.c"));
    ASSERT_EQ(script->GetString("a.b.c"), nullptr);
    ASSERT_EQ(script->SetString("a.b.c", "hello"), 0);
    ASSERT_EQ(script->SetNumber("a.b.d", 1), 0);
    ASSERT_EQ(script->SetTable("a.b.t"), 0);
    auto t = script->Get("a.b.t");
    t.SetString("nickname", "lj\nw");
    t.SetString("avatar", "xx");
    t.SetNumber("score", 100);
    ASSERT_STREQ(script->ToJson("a"), R"({"b":{"d":1,"c":"hello","t":{"nickname":"lj\nw","score":100,"avatar":"xx"}}})");
    ASSERT_STREQ(script->ToJson("a.b"), R"({"d":1,"c":"hello","t":{"nickname":"lj\nw","score":100,"avatar":"xx"}})");;
    ASSERT_STREQ(script->ToJson("a.b.c"), R"("hello")");
    ASSERT_STREQ(script->ToJson("a.b.d"), R"(1)");
    ASSERT_STREQ(script->ToJson("b"), R"(null)");
    ASSERT_EQ(lua_gettop(script->L), 0);

    const char* str = script->ToJson("a");
    ASSERT_EQ(script->FromJson("b", str, strlen(str)), 0);

    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_EQ(script->SetNil("b"), 0);
    ASSERT_EQ(lua_gettop(script->L), 0);

    ASSERT_NE(script->FromJson("b", R"({(F)})"), 0);
} 

TEST_F(TestScript, SetGet) {
    auto& script = this->coord->Script;
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_EQ(script->GetNumber("a"), 0);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->SetNumber("a", 1.234), 0);
    ASSERT_TRUE(script->IsNumber("a"));
    ASSERT_EQ(script->GetNumber("a"), 1.234);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_TRUE(script->IsNil("a"));

    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_EQ(script->GetString("a"), nullptr);
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->SetString("a", "hello\n"), 0);
    ASSERT_TRUE(script->IsString("a"));
    ASSERT_STREQ(script->GetString("a"), "hello\n");
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_TRUE(script->IsNil("a"));

    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_TRUE(script->IsNil("a"));
    ASSERT_FALSE(script->GetBool("a"));
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->SetBool("a", true), 0);
    ASSERT_TRUE(script->IsBool("a"));
    ASSERT_TRUE(script->GetBool("a"));
    ASSERT_EQ(lua_gettop(script->L), 0);
    ASSERT_EQ(script->SetNil("a"), 0);
    ASSERT_TRUE(script->IsNil("a"));


}
