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


int main(int argc, char** _argv) {    
    coord::Coord* coorda = coord::NewCoord();
    coord::Argv argv;
    argv.Name = "benchmark";
    argv.ConfigPath = "test/test.ini";
    int err = coorda->beforeTest(argv);
    if (err) {
        return err;
    }
    ::benchmark::Initialize(&argc, _argv);                               
    if (::benchmark::ReportUnrecognizedArguments(argc, _argv)) return 1; 
    ::benchmark::RunSpecifiedBenchmarks();   
    err = coorda->afterTest();
    delete coorda;                               
    ::benchmark::Shutdown();                               
    return 0;                                                           
}    
