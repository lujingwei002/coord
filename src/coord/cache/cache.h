#pragma once 

namespace coord {
class Coord;

namespace cache {

class Client;
class AsyncClient;

class Cache {
public:
    Cache(Coord* coord);
    ~Cache();
public:
    int main();
private:
    Coord*          coord;
    Client*         client;
    AsyncClient*    asynClient;
};

Cache* newCache(Coord* coord);

}
}