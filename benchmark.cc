#include "coord/coord.h"
#include <benchmark/benchmark.h>
#include "benchmark/benchmark-map.cc"
#include "benchmark/benchmark-json.cc"
#include "benchmark/benchmark-table.cc"
#include "benchmark/benchmark-protobuf.cc"
#include <array>


int onAwake(coord::Coord* coord) {
    printf("onAwake\n");
    return 0;
}

void onDestory(coord::Coord* coord) {
    printf("onDestory\n");
}


int main(int argc, char** argv) {    
    coord::Coord* coorda = coord::NewCoord();
    int err = coorda->beforeTest("test/test.ini");
    if (err) {
        return err;
    }
    ::benchmark::Initialize(&argc, argv);                               
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1; 
    ::benchmark::RunSpecifiedBenchmarks();   
    err = coorda->afterTest();
    delete coorda;                               
    ::benchmark::Shutdown();                               
    return 0;                                                           
}    