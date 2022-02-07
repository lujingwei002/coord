#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "coord/builtin/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestPromise : public testing::Test {
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

TEST_F(TestPromise, Basic) {
    auto promise = coord::newPromise(this->coord);
    promise->Then([this](){
        printf("gg\n");
      //  std::cout << arg1 << std::endl;
    });
    promise->resolve();
}

 