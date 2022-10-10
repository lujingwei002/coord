#include "coord/coord.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>


int onStart(coord::Coord* coord) {
    printf("onStart\n");
    return 0;
}

int onAwake(coord::Coord* coord) {
    //printf("onAwake\n");
    return 0;
}

void onDestory(coord::Coord* coord) {
    //printf("onDestory\n");
}

int main(int argc, const char **argv) {
    int err = coord::Main(argc, argv);
    if (err) fprintf(stderr, "error: %d\n", err);
    return err;
}

