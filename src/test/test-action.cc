#include "coord/coord.h"
#include "coord/builtin/argument.h"
#include "coord/builtin/slice.h"
#include "coord/action/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestAction : public testing::Test {
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

TEST_F(TestAction, Basic) {
    auto anim = this->coord->Action->Begin();
    anim->Run(
        anim->Sequence(
            anim->Sequence(
                anim->Call([this](coord::action::Action* action) {
                   // printf("ggggggggg11\n");
                    action->Next();
                }),
                nullptr
            ),
            anim->Wait(100),
            anim->Parallel(
                anim->Wait(200),
                anim->Call([this](coord::action::Action* action) {
                 //   printf("ggggggggg22\n");
                    action->Next();
                }),
                anim->Call([this](coord::action::Action* action) {
                   // printf("ggggggggg33\n");
                    action->Next();
                }),
                nullptr
            ),
            anim->Call([this](coord::action::Action* action) {
              //  printf("ggggggggg1\n");
                action->Next();
            }),
            anim->Call([this](coord::action::Action* action) {
               // printf("ggggggggg2\n");
                action->Next();
            }),
            nullptr
        )
    );
    this->coord->loopTest();
}

