#include "coord/coord.h"
#include "coord/builtin/argument.h"
#include "coord/builtin/slice.h"
#include "coord/event/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestEvent : public testing::Test {
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

TEST_F(TestEvent, Basic) {
   auto listener = this->coord->Event->AddListener("login", [](coord::event::BaseEvent* ev){
       printf("recv event\n");
   });
   this->coord->Emit("login", new coord::event::BaseEvent("login", "aa"));
   delete listener;
}

