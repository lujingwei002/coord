#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestArray : public testing::Test {
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

TEST_F(TestArray, Basic) {
    coord::array<char> arr(4);
    ASSERT_EQ(arr.capacity, (size_t)4);
}

 