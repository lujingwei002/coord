#include "coord/coord.h"
#include "coord/http/http_server.h"
#include "coord/http/http_router.h"
#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>

class TestHttp : public testing::Test {
public:
    static void SetUpTestCase() {
    }
    
    static void TearDownTestCase() {
    }

    void SetUp() {
        coord::Coord* coord = coord::NewCoord();
        coord::Argv argv;
        argv.Name = "test";
        argv.ConfigPath = "test/test.ini";
        int err = coord->beforeTest(argv);
        ASSERT_EQ(err, 0);
        this->coord = coord;
    }
    void TearDown() {
        int err = this->coord->afterTest();
        ASSERT_EQ(err, 0);
        delete this->coord;
    } 
    void HandleNull(coord::http::HttpRequest* request) {

    }
public:
    coord::Coord* coord;
};

TEST_F(TestHttp, TestRouter) {
    auto httpServer = this->coord->NewHttpServer();
    auto router = httpServer->Router;
    router->Get("/", std::bind(&TestHttp::HandleNull, this, std::placeholders::_1));
    router->Get("/account/login", std::bind(&TestHttp::HandleNull, this, std::placeholders::_1));
    router->Get("/account/index", std::bind(&TestHttp::HandleNull, this, std::placeholders::_1));
    router->Trace();
    ASSERT_TRUE(router->Match("GET", "/"));
    ASSERT_TRUE(router->Match("GET", "/account/index"));
/*    auto node = router->searchNode("GET", "/");*/
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/");

    //node = router->searchNode("GET", "/bb/");
    //ASSERT_FALSE(node) << "Match Url:" << node->fullPath;

    //node = router->searchNode("GET", "/aa/cc");
    //ASSERT_FALSE(node) << "Match Url:" << node->fullPath;

    //node = router->searchNode("GET", "/aa/bb");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/aa/bb");

    //node = router->searchNode("GET", "/aa/bb/");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/aa/bb/");

    //node = router->searchNode("GET", "/aa/bb/cc");
    //ASSERT_FALSE(node) << "Match Url:" << node->fullPath;

    //node = router->searchNode("GET", "/asset/1.js");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/asset/*path");

    //node = router->searchNode("GET", "/asset/js/1.js");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/asset/*path");

    //node = router->searchNode("GET", "/static/1.js");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/static/:path");

    //node = router->searchNode("GET", "/static/js/1.js");
    //ASSERT_FALSE(node) << "Match Url:" << node->fullPath;
    ////test /hello/:name
    //node = router->searchNode("GET", "/hello/aa");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/hello/:name");
    //node = router->searchNode("GET", "/hello/");
    //ASSERT_FALSE(node) << "Match Url:" << node->fullPath;
    //node = router->searchNode("GET", "/hello/v1/aa");
    //ASSERT_FALSE(node) << "Match Url:" << node->fullPath;
    ////test /hi[>name
    //node = router->searchNode("GET", "/hi/aa");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/hi/*name");
    //node = router->searchNode("GET", "/hi/");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/hi/*name");
    //node = router->searchNode("GET", "/hi/v1/aa");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/hi/*name");
    //node = router->searchNode("GET", "/hi/song");
    //ASSERT_TRUE(node);
    //ASSERT_STREQ(node->fullPath.c_str(), "/hi/song");
    /*this->coord->Destory(httpServer);*/
}

TEST_F(TestHttp, TestServer) {
}
