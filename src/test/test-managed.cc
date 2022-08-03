#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "coord/managed/init.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestManaged: public testing::Test {
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

TEST_F(TestManaged, Basic) {
    auto managed = this->coord->Managed;
    auto client = managed->NewClient(this->coord->Environment->ManagedSockPath);
    auto promise = client->Connect();
    auto self = this;
    promise->Then([&self](auto client, auto result) {
        printf("connect succeed\n");
        coord::Argument argument(self->coord);
        argument.AddString("hello");
        auto promise1 = client->Request("stop", &argument);
        promise1->Then([&self](auto client, auto result) {
            printf("fffffffffffffff1\n");
            auto argument = result->Args();
            argument->DebugPrint();
            //self->coord->Managed->Close();
            //client->Destory();

            //client->Close();
            self->coord->Destory(client);
        })->Else([](auto client, auto result) {
            printf("fffffffffffffff2\n");
        });
    })->Else([](auto client, auto result) {
        printf("connect fail\n");
    });
    //client->Close();
    //this->coord->Destory(client);
    this->coord->loopTest();
}

 
