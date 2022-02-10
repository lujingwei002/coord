#include "coord/coord.h"
#include "coord/builtin/init.h"
#include "coord/closure/init.h"
#include "coord/builtin/slice.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestClosure : public testing::Test {
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

TEST_F(TestClosure, Basic) {
    auto func = this->coord->Closure->Function("arg1", "arg2", "arg3")
        ->Defer([](auto self) {
            printf("defer\n");
        })
        ->Catch([](auto self) {
            printf("catch\n");
        })
        ->_([](auto self){
            printf("ffff1 \n");
            self->Value("enter 1", true);
            auto arg1 = std::any_cast<int>(self->Arg("arg1"));
            ASSERT_EQ(arg1, 1);
        })
        ->_([](auto self){
            printf("ffff2 \n");
            auto arg2 = std::any_cast<const char*>(self->Arg("arg2"));
            ASSERT_STREQ(arg2, "2");
        })
        ->Await([](auto self, auto promise){
            printf("await1\n");
            promise->Reslove();
        }, 
        [](auto self) {
            ASSERT_TRUE(true);
        },
        [](auto self){
            ASSERT_TRUE(false);
        })
        ->Await([](auto self, auto promise){
            printf("await2\n");
            promise->Reslove();
        })
        ->Wait(100)
        ->_([](auto self){
            printf("ffff3 \n");
            auto arg3 = std::any_cast<double>(self->Arg("arg3"));
            ASSERT_EQ(arg3, 3.3);
        })
        ->If([](auto self){
            printf("if\n");
            return false;
        })
            ->_([](auto self){
                ASSERT_TRUE(false);
            })
        ->Else()
            ->_([](auto self){
                ASSERT_TRUE(true);
            })
        ->End()
        ->_([](auto self){
            printf("ffff4 \n");
        })
    ->End();
    func->Call(1, "2", 3.3);
    this->coord->loopTest();
}

