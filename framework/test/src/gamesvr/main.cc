
#include "coord/coord.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

int main(int argc, const char **argv) {
    if (argc < 2){
        std::cout << "not config file" << std::endl;
        return EXIT_FAILURE;
    }
    coord::Coord* coorda = coord::NewCoord();
    int err = coorda->Run(argv[1]);
    if(err){
        return err;
    }

    /*coord::Coord* coordb = coord::NewCoord();
    err = coordb->Main(argc, argv);
    if(err){
        return err;
    }*/

    coord::Wait();

    return EXIT_SUCCESS;
}

