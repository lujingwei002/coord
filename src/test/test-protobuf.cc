#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "coord/protobuf/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

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
    auto user = this->coord->Proto->NewReflect("test.User");
    user.SetString("nickname", "ljw");
    ASSERT_NE(user, nullptr);
    auto itemArr = user.GetRepeat("itemArr");
    ASSERT_NE(itemArr, nullptr);
    auto item1 = itemArr.AddMessage();
    item1.SetNumber("id", 100);
    auto item2 = itemArr.AddMessage();
    item2.SetNumber("count", 333);
    ASSERT_EQ(itemArr.Count(), 2);
    ASSERT_STREQ(user.ShortDebugString(), R"(nickname: "ljw" itemArr { id: 100 } itemArr { count: 333 })");
}

TEST_F(TestProtobuf, Import) {
    int err = this->coord->Proto->Import("a.proto");
    ASSERT_NE(err, 0);
}

