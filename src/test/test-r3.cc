#include "coord/coord.h"
#include "coord/redis/init.h"
#include "coord/config/config.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "r3/r3.hpp"

class TestR3: public testing::Test {
public:
    static void SetUpTestCase() {
       // std::cout<<"[TestHttp] SetUpTestCase()"<<std::endl;;
    }
    static void TearDownTestCase() {
        //std::cout<<"[TestHttp] TearDownTestCase()"<<std::endl;
    }
    void SetUp() {
    }
    void TearDown() {
    } 
public:
};

TEST_F(TestR3, Insert) {

    auto tree = new r3::Tree(10);
    char* errstr = nullptr;
    auto node = tree->insert_path("/account/login", nullptr, &errstr);
    if (node.is_null()) {
        delete tree;
    }
    node = tree->insert_path("/account/index", nullptr, &errstr);
    if (node.is_null()) {
        delete tree;
    }
    node = tree->insert_path("status", nullptr, &errstr);
    if (node.is_null()) {
        delete tree;
    }
    int err = tree->compile(&errstr);
    if (err) {
        delete tree;
    }

    node = tree->match("hello");
    if (node) {
        printf("match status\n");
    } else {
        printf("not match status\n");
    }
    node = tree->match("/account/login/");
    if (node) {
        printf("match /account/login/\n");
    } else {
        printf("not match /account/login/\n");
    }

    tree->dump(10);
}


