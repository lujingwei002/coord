#include "coord/coord.h"
#include "coord/builtin/slice.h"
#include "coord/timer/timer.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestTimer : public testing::Test {
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

TEST_F(TestTimer, Timeout) {
    this->coord->SetTimeout(10, [this]() {
        this->coord->Destory(0);
        return 0;
    });
    this->coord->loopTest();
}

TEST_F(TestTimer, Interval) {
    int count = 0;
    this->coord->SetInterval(10, [this, &count]() -> uint64_t {
        count = count + 1;
        if (count > 10) {
            return this->coord->StopTimer();
        }
        return 0;        
    });
    this->coord->loopTest();
}

TEST_F(TestTimer, IntervalReduce) {
    uint64_t interval = 10;
    this->coord->SetInterval(interval, [this, &interval]() {
        interval = interval - 1;
        //printf("fff %ld %ld\n", interval, this->coord->Time());
        if (interval <= 0) {
            return this->coord->StopTimer();
        }
        return interval;        
    });
    this->coord->loopTest();
}


TEST_F(TestTimer, Cron) {
    this->coord->SetCron("* * * * * *", [this]() {
        this->coord->Destory(0);      
    });
    this->coord->loopTest();
} 
