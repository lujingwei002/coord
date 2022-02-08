#include "coord/coord.h"
#include "coord/script/reflect.h"
#include "coord/builtin/slice.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestTable : public testing::Test {
public:
    static void SetUpTestCase() {
       
    }
    static void TearDownTestCase() {
      
    }

    void SetUp() {
        coord::Coord* coord = coord::NewCoord();
        int err = coord->beforeTest("test/test.ini");
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
    auto table = this->coord->Script->NewReflect();
    
    table.SetTable();
    table.SetString("hello", "world");
    table.SetString(1, "world");
    auto t1 = table.SetTable("user");
    t1.SetString("nickname", "ljw");
    auto t2 = table.SetTable("servers");
    t2.SetString(1, "ljw1");
    t2.SetString(1, "ljw2");

    auto table2 = this->coord->Script->NewReflect();
    table2.SetTable();
    table2.SetString("Name", "3333");
    table.SetTable(3, table2);
    ASSERT_STREQ(table.ToShortString(), "{[1]='world','hello'='world','servers'={[1]='ljw2',},[3]={'Name'='3333',},'user'={'nickname'='ljw',},}");
}

TEST_F(TestTable, TestReflectSetGet) {
    auto table = this->coord->Script->NewTable();
    int err = table.SetString("name", "ljw");
    ASSERT_EQ(err, 0);
    ASSERT_EQ(table.GetString("avatar"), nullptr);
    ASSERT_STREQ(table.GetString("name"), "ljw");
}

TEST_F(TestTable, TestReflectSerialize) {
    auto table = this->coord->Script->NewReflect();
    
    table.SetTable();
    table.SetString("hello", "world");
    table.SetString(1, "world");
    auto t1 = table.SetTable("user");
    t1.SetString("nickname", "ljw");
    auto t2 = table.SetTable("servers");
    t2.SetString(1, "ljw1");
    t2.SetString(1, "ljw2");

    auto table2 = this->coord->Script->NewReflect();
    table2.SetTable();
    table2.SetString("Name", "3333");
    table.SetTable(3, table2);

    coord::byte_slice buffer;
    int err = table.Encode(buffer);
    ASSERT_EQ(err, 0);
    auto table3 = this->coord->Script->NewReflect();
    ASSERT_TRUE(table3.IsNil());
    err = table3.Decode(buffer);
    ASSERT_TRUE(table3.IsTable());
    ASSERT_STREQ(table3.ToShortString(), "{[1]='world','servers'={[1]='ljw2',},'hello'='world',[3]={'Name'='3333',},'user'={'nickname'='ljw',},}");
}

TEST_F(TestTable, TestReflectString) {
    auto table = this->coord->Script->NewString("hello world");
    int err = table.SetString("name", "ljw");
    ASSERT_NE(err, 0);
    ASSERT_STREQ(table.GetString(), "hello world");
    ASSERT_STREQ(table.ToShortString(), R"('hello world')");
}

TEST_F(TestTable, TestReflectNumber) {
    auto table = this->coord->Script->NewNumber(1.234);
    int err = table.SetString("name", "ljw");
    ASSERT_NE(err, 0);
    ASSERT_FLOAT_EQ(table.GetNumber(), 1.234);
    ASSERT_STREQ(table.ToShortString(), R"(1.234000)");
}

TEST_F(TestTable, TestReflectRef) {
    auto table1 = this->coord->Script->NewTable();
    auto table2 = table1;
    ASSERT_NE(table1.ref, table2.ref);
}
