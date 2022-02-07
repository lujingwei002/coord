#include "coord/coord.h"
#include "coord/builtin/argument.h"
#include "coord/builtin/slice.h"
#include "coord/json/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestJson : public testing::Test {
public:
    static void SetUpTestCase() {
    }
    static void TearDownTestCase() {
    }

    void SetUp() {
        coord::Coord* coorda = coord::NewCoord();
        this->coord = coorda;
        int err = coorda->beforeTest("test/test.ini");
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

TEST_F(TestJson, Basic) {
    auto json = this->coord->Json->NewObject();  
    ASSERT_EQ(json.GetString("version"), nullptr);
    json.SetString("version", "1.0.0");
    ASSERT_STREQ(json.GetString("version"), "1.0.0");
    json.SetNumber("score", 1.23);
    auto user = json.SetObject("user");
    user.SetString("name", "ljw");
    auto dd = json.GetObject("dd");
    ASSERT_TRUE(dd == nullptr);
    user = json.GetObject("user");
    ASSERT_TRUE(user != nullptr);
    ASSERT_STREQ(user.GetString("name"), "ljw");

    auto gameArr = json.SetArray("gameArr");
    auto game1 = gameArr.AddObject();
    game1.SetString("name", "game1");

    std::string str1 = json.ToString();
    auto json2 = this->coord->Json->Decode(str1);
    std::string str2 = json2.ToString();
    ASSERT_STREQ(str2.c_str(), R"({"gameArr": [{"name": "game1"}], "score": 1.23, "user": {"name": "ljw"}, "version": "1.0.0"})");
    ASSERT_STREQ(str1.c_str(), str2.c_str());
}

TEST_F(TestJson, Array) {
    auto json = this->coord->Json->NewArray();   
    auto book1 = json.AddObject();
    book1.SetString("name", "c++");
    auto book2 = json.AddObject();
    book2.SetString("name", "lua");
    ASSERT_EQ(json.Count(), 2);
    ASSERT_STREQ(json.ToString(), R"([{"name": "c++"}, {"name": "lua"}])");
}

TEST_F(TestJson, String) {
    auto json1 = this->coord->Json->NewString();   
    ASSERT_STREQ(json1.ToString(), R"("")");
    auto json2 = this->coord->Json->NewString("hello");   
    ASSERT_STREQ(json2.ToString(), R"("hello")");
}

TEST_F(TestJson, Null) {
    auto json1 = this->coord->Json->NewNull();   
    ASSERT_STREQ(json1.ToString(), R"(null)");
}

TEST_F(TestJson, Bool) {
    auto json1 = this->coord->Json->NewBool(true);   
    ASSERT_STREQ(json1.ToString(), R"(true)");
}