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

int onAwake(coord::Coord* coord) {
    //printf("onAwake\n");
    return 0;
}

void onDestory(coord::Coord* coord) {
    //printf("onDestory\n");
}

class Environment : public testing::Environment {
public:
    virtual void SetUp() {
        coord::Init();
       // std::cout << "Environment SetUP" << std::endl;
    }

    virtual void TearDown() {
       // std::cout << "Environment TearDown" << std::endl;
       coord::Destory();
    }
};

int main(int argc,char **argv){
    testing::AddGlobalTestEnvironment(new Environment);
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
