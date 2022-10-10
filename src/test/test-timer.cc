

class TestTimer : public testing::Test {
public:
    static void SetUpTestCase() {
    }
    static void TearDownTestCase() {
    }

    void SetUp() {
    }

    void TearDown() {
    } 
public:
};

TEST_F(TestTimer, Timeout) {
    coord::timer::SetTimeout(10, [this]() {
        printf("ggggggggggggggggggg2\n");
        coorda->Break();
        return 0;
    });
    printf("ggggggggggggggggggg1\n");
    coorda->Join();
    printf("ggggggggggggggggggg11\n");
}

TEST_F(TestTimer, Interval) {
    int count = 0;
    coord::timer::SetInterval(10, [this, &count]() -> uint64_t {
        count = count + 1;
        if (count > 10) {
            return coord::timer::StopTimer();
        }
        return 0;        
    });
}

TEST_F(TestTimer, IntervalReduce) {
    uint64_t interval = 10;
    coord::timer::SetInterval(interval, [this, &interval]() {
        interval = interval - 1;
        if (interval <= 0) {
            return coord::timer::StopTimer();
        }
        return interval;        
    });
}


TEST_F(TestTimer, Cron) {
    coord::timer::SetCron("* * * * * *", [this]() {
    });
} 
