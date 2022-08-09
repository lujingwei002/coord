

class TestMySQL : public testing::Test {
public:
    static void SetUpTestCase() { 
    }

    static void TearDownTestCase() {  
    }

    void SetUp() {
        auto coord = coord::NewCoord();
        coord::Argv argv;
        argv.Name = "test";
        argv.ConfigPath = "test/test.ini";
        int err = coord->beforeTest(argv);
        ASSERT_EQ(err, 0);
        this->sqlMgr = coord::sql::newSQLMgr(coord);
        this->coord = coord;    
    }
    void TearDown() {
        int err = this->coord->afterTest();
        ASSERT_EQ(err, 0);
        delete this->coord;
    } 
public:
    coord::Coord*           coord;
    coord::sql::sql_mgr*    sqlMgr;
};

class Test1 {
public:
    Test1(const char* name) {
        this->name = name;
    }
    void hello1(const char* w) {
        printf("aaa %s %s\n", this->name.c_str(), w);
    }
    void hello2(const char* w) {
        printf("aaa %s %s\n", this->name.c_str(), w);
    }
public:
    std::string name;
};

 
typedef std::function<void (const char* w)> TestFunction; 

TEST_F(TestMySQL, TestSetGet) {
    
    Test1* t1 = new Test1("t1");
    Test1* t2 = new Test1("t2");
    TestFunction f1 = std::bind(&Test1::hello1, t1, std::placeholders::_1);
    TestFunction f2 = std::bind(&Test1::hello2, t2, std::placeholders::_1);
    if (f1.target<void(*)(const char*)>() == f2.target<void(*)(const char*)>()) {
        printf("ffffffffffffffffffffffffffffffffff1\n");
    } else {
        printf("ffffffffffffffffffffffffffffffffff2\n");
    }

    int err = this->coord->Proto->ImportDir(this->coord->Config->Basic.Proto.c_str());
    ASSERT_EQ(err, 0);

    auto client = this->sqlMgr->getClient("DB");
    ASSERT_NE(client, nullptr);
    err = client->Ping();
    ASSERT_EQ(err, 0);
   
    ASSERT_STREQ(client->Format("aa ?, ?", 1, "你好"), "aa 1, '你好'");
    ASSERT_STREQ(client->Format("aa ?, ?", 1, (char*)"你好"), "aa 1, '你好'");
    ASSERT_STREQ(client->Format("aa ?, ?,?", 1, "你好"), "aa 1, '你好',?");
    ASSERT_STREQ(client->Format("aa ?, ?", 1, "你好", "2"), "aa 1, '你好'");

    auto result = client->Execute("DROP TABLE `testcoord`");
    //ASSERT_NE(result, nullptr);
    result = client->Execute("CREATE TABLE `testcoord` (\
        `userid` bigint(11) NOT NULL AUTO_INCREMENT COMMENT '用户id',\
        `openid` varchar(64) NOT NULL DEFAULT '' COMMENT 'openid',\
        `nickname` varchar(128) NOT NULL DEFAULT '' COMMENT '昵称',\
        `avatar` varchar(128) NOT NULL DEFAULT '' COMMENT '头像',\
        `diamond` bigint(11) NOT NULL DEFAULT '0' COMMENT '钻石',\
        `score` decimal(11, 2) NOT NULL DEFAULT '0' COMMENT '分类',\
        `rank` enum('one', 'two', 'three') NOT NULL DEFAULT 'two' COMMENT '排名',\
        `catalog` set('c1', 'c2', 'c3') NOT NULL DEFAULT 'c1,c3' COMMENT '分类',\
        `coin` bigint(11) NOT NULL DEFAULT '0' COMMENT '金币',\
        `createtime` int(11) NOT NULL DEFAULT '0' COMMENT '创建时间',\
        `updatetime` int(11) NOT NULL DEFAULT '0' COMMENT '更新时间',\
        PRIMARY KEY (`userid`)\
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户表';\
    ");
    ASSERT_NE(result, nullptr); 
    result = client->Execute("INSERT INTO testcoord(userid, nickname, score, rank, catalog) VALUES (1, '你好a', 3.123, 'three', 'c2,c3')");
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result.RowsAffected(), (uint64_t)1);
    result = client->Execute("INSERT INTO testcoord(userid, nickname) VALUES (?, ?)", 2, "你好b", 4);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result.RowsAffected(), (uint64_t)1);
    auto rows = client->Query("SELECT userid, nickname, avatar, score, rank, catalog, createtime FROM testcoord ORDER BY userid asc LIMIT 10");
    while (rows.Next()) {
        if (rows.Index() == 0){
            ASSERT_STREQ(rows.String("nickname"), "你好a");
            ASSERT_EQ(rows.Number("score"), 3.12);
            ASSERT_STREQ(rows.String("rank"), "three");
            ASSERT_STREQ(rows.String("catalog"), "c2,c3");
        } else if(rows.Index() == 1){
            ASSERT_STREQ(rows.String("nickname"), "你好b");
        }
    }

    auto user = this->coord->Proto->NewReflect("test.User");
    ASSERT_NE(user, nullptr);
    err = client->Get(user, "SELECT * FROM testcoord WHERE userid=?", 1);
    ASSERT_EQ(err, 0);
    //printf("ppppppp %s\n", user.DebugString());
    //coord::slice<coord::protobuf::Reflect> userArr;
    //err = client->Query(userArr, "SELECT * FROM testcoord");
    //ASSERT_EQ(err, 0);

    rows = client->Query("SELECT userid1, nickname, avatar, createtime FROM testcoord LIMIT 10");
    ASSERT_EQ(rows, nullptr);
    result = client->Execute("UPDATE testcoord SET nickname=? WHERE userid=2", "你好c");
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result.RowsAffected(), (uint64_t)1);
    result = client->Execute("UPDATE testcoord SET nickname=?", "你好");
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result.RowsAffected(), (uint64_t)2);
    result = client->Execute("DROP TABLE `testcoord`");
    ASSERT_NE(result, nullptr);
}

