#include "coord/inc.h"
#include <gtest/gtest.h>
#include "test/test-http.cc"
#include "test/test-argument.cc"
#include "test/test-script.cc"
#include "test/test-table.cc"
#include "test/test-buildin.cc"
#include "test/test-redis.cc"
#include "test/test-async-redis.cc"
#include "test/test-cache.cc"
#include "test/test-async-cache.cc"
#include "test/test-array.cc"
#include "test/test-slice.cc"
#include "test/test-encrypt.cc"
#include "test/test-timer.cc"
#include "test/test-action.cc"
#include "test/test-closure.cc"
#include "test/test-promise.cc"
#include "test/test-mysql.cc"
#include "test/test-event.cc"
#include "test/test-json.cc"
#include "test/test-protobuf.cc"
#include "test/test-cluster.cc"
#include "test/test-managed.cc"
#include "test/test-r3.cc"


/*int main(int argc, const char **argv) {
    if (argc < 2){
        std::cout << "not config file input" << std::endl;
        return EXIT_FAILURE;
    }
    coord::Coord* coorda = coord::NewCoord();
    int err = coorda->Main(argv[1]);
    delete coorda;
    return err;
}*/

int onStart(coord::Coord* coord) {
    printf("onStart\n");
    return RUN_ALL_TESTS();
}

int onAwake(coord::Coord* coord) {
    printf("onAwake\n");
    return 0;
}

void onDestory(coord::Coord* coord) {
    printf("onDestory\n");
}

class Environment : public testing::Environment {
public:
    virtual void SetUp() {
        coord::Init();
        // std::cout << "Environment SetUP" << std::endl;
    }

    virtual void TearDown() {
       //int err = coorda->afterTest();
       //ASSERT_EQ(err, 0);
       //delete coorda;
       // std::cout << "Environment TearDown" << std::endl;
       coord::Destory();
    }
};

int main(int argc,char **argv){
    testing::AddGlobalTestEnvironment(new Environment);
    testing::InitGoogleTest(&argc,argv);

    coord::Argv args;
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-v") == 0) {
            if (i + 1 >= argc) {
                printf("verbose argument error\n");
                return -1;
            }
            i = i + 1;
            args.LoggerPriority = argv[i];
            break;
        }
        if (strcmp(argv[i], "-vv") == 0) {
            if (i + 1 >= argc) {
                printf("vverbose argument error\n");
                return -1;
            }
            i = i + 1;
            args.CoreLoggerPriority = argv[i];
            break;
        }
    }
    coord::Coord* coord = coord::NewCoord();
    args.Name = "test";
    args.ConfigPath = "test/test.ini";
    printf("aaaaaaaa1\n");
    int err = coord->Main(args);
    printf("aaaaaaaa2\n");
    if (err) {
        printf("set up fail, error=%d\n", err);
        return err;
    }
    delete coord;
    return err;
}
