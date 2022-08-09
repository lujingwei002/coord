


class TestEvent : public testing::Test {
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

TEST_F(TestEvent, Basic) {
   auto listener = this->coord->Event->AddListener("login", [](coord::event::BaseEvent* ev){
       printf("recv event\n");
   });
   this->coord->Emit("login", new coord::event::BaseEvent("login", "aa"));
   delete listener;
}

