
class TestArgument : public testing::Test {
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

TEST_F(TestArgument, Basic) {
    coord::Argument args(coorda);
    args.AddNumber(2);
    args.AddString("hello");
    args.AddBool(true);
    args.AddNil();
    ASSERT_EQ(args.Count(), 4);
    ASSERT_EQ(args.GetNumber(0), 2);
    ASSERT_STREQ(args.GetString(1), "hello");
    ASSERT_TRUE(args.GetBool(2));
    ASSERT_TRUE(args.IsNil(3));
    for (int i = args.Count() + 1; i <= 16; i++) {
        ASSERT_EQ(args.AddNumber(i), 0);
    }
    ASSERT_EQ(args.Count(), 16);
}

TEST_F(TestArgument, Serialize) {
    coord::Argument args1(coorda);
    args1.AddNumber(2);
    args1.AddString("hello");
    args1.AddBool(true);
    args1.AddNil();
    for (int i = args1.Count() + 1; i <= 16; i++) {
        ASSERT_EQ(args1.AddNumber(i), 0);
    }
    coord::byte_slice buffer1;
    ASSERT_EQ(args1.Serialize(buffer1), 0);

    coord::Argument args2(coorda);
    ASSERT_EQ(args2.Parse(buffer1), 0);

    ASSERT_EQ(args1.Count(), args2.Count());
    for(int i = 0; i < args1.Count(); i++) {
        ASSERT_EQ(args1.Type(i), args2.Type(i));
    }

    coord::byte_slice buffer2;
    ASSERT_EQ(args2.Serialize(buffer2), 0);

    ASSERT_EQ(buffer1.Len(), buffer2.Len());
    ASSERT_EQ(strncmp(buffer1.Data(), buffer2.Data(), buffer1.Len()), 0);
}


TEST_F(TestArgument, SerializeBench) {
    coord::Argument args1(coorda);
    args1.AddNumber(2);
    args1.AddString("hello");
    args1.AddBool(true);
    args1.AddNil();
    for (int i = args1.Count() + 1; i <= 16; i++) {
        ASSERT_EQ(args1.AddNumber(i), 0);
    }

    for(int i = 0; i < 1000; i++) {
        coord::byte_slice buffer1;
        ASSERT_EQ(args1.Serialize(buffer1), 0);

        coord::Argument args2(coorda);
        ASSERT_EQ(args2.Parse(buffer1), 0);

        ASSERT_EQ(args1.Count(), args2.Count());
        for(int i = 0; i < args1.Count(); i++) {
            ASSERT_EQ(args1.Type(i), args2.Type(i));
        }

        coord::byte_slice buffer2;
        ASSERT_EQ(args2.Serialize(buffer2), 0);

        ASSERT_EQ(buffer1.Len(), buffer2.Len());
        ASSERT_EQ(strncmp(buffer1.Data(), buffer2.Data(), buffer1.Len()), 0);
    }
}

TEST_F(TestArgument, TestTable) {
    coord::Argument args1(coorda);
    args1.AddNumber(2);
    args1.AddString("hello");
    args1.AddBool(true);
    args1.AddNil();
    coord::script::Variable table1(coorda);
    table1.SetTable();
    table1.Set("HELLo", "world");
    args1.AddTable(table1);


    coord::byte_slice buffer1;
    ASSERT_EQ(args1.Serialize(buffer1), 0);

    coord::Argument args2(coorda);
    ASSERT_EQ(args2.Parse(buffer1), 0);

    ASSERT_EQ(args2.IsTable(4), true);
    coord::script::Variable& table2 = args2.GetTable(4);
    ASSERT_STREQ(table2.GetString("HELLo"), "world");

    ASSERT_EQ(args1.Count(), args2.Count());
    for(int i = 0; i < args1.Count(); i++) {
        ASSERT_EQ(args1.Type(i), args2.Type(i));
    }

    coord::byte_slice buffer2;
    ASSERT_EQ(args2.Serialize(buffer2), 0);

    ASSERT_EQ(buffer1.Len(), buffer2.Len());
    ASSERT_EQ(strncmp(buffer1.Data(), buffer2.Data(), buffer1.Len()), 0);
}
