#include "coord/coord.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

int onAwake(coord::Coord* coord) {
    printf("onAwake\n");
    return 0;
}

void onDestory(coord::Coord* coord) {
    printf("onDestory\n");
}

int main(int argc, const char **argv) {
    if (argc < 2){
        std::cout << "not config file input" << std::endl;
        return EXIT_FAILURE;
    }
    coord::Init();
    for(int i = 1; i < argc; i++){
        coord::Coord* coorda = coord::NewCoord();
        int err = coorda->Fork(argv[i]);
        if(err){
            return err;
        }
    }
    int err = coord::Wait();
    coord::Destory(); 
    return err;
}

