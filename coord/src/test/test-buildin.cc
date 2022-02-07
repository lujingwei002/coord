#include "coord/coord.h"
#include "coord/script/reflect.h"
#include "coord/builtin/slice.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestBuildin : public testing::Test {
public:
    static void SetUpTestCase() {
       // std::cout<<"[TestHttp] SetUpTestCase()"<<std::endl;;
    }
    static void TearDownTestCase() {
        //std::cout<<"[TestHttp] TearDownTestCase()"<<std::endl;
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


TEST_F(TestBuildin, TestArgument) {
    
   
}