#include "coord/cache/cache.h"

namespace coord {
namespace cache {

Cache* newCache(Coord* coord) {
    Cache* self = new Cache(coord);
    return self;
}

Cache::Cache(Coord* coord) {
    this->coord = coord;
}

Cache::~Cache() {

}

int Cache::main() {
    return 0;
}

}
}