#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class Tiger {

};

class TestSlice : public testing::Test {
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

TEST_F(TestSlice, Basic) {
    coord::slice<unsigned char> arr(4, 4);
   // Tiger t1;
   // arr.Appendf("%s", "aa");
    ASSERT_EQ(arr.Capacity(), (size_t)4);
}

 