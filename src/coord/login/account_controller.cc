#include "coord/login/account_controller.h"
#include "coord/login/login.h"
#include "coord/login/login_cluster.h"
#include "coord/http/init.h"
#include "coord/redis/redis_promise.h"
#include "coord/redis/redis_result.h"
#include "coord/json/json_mgr.h"
#include "coord/http/http_router.h"
#include "coord/coord.h"

namespace coord {
namespace login {

account_controller* newAccountController(Coord* coord, LoginSvr* loginSvr) {
    account_controller* self = new account_controller(coord, loginSvr);
    return self;
}

account_controller::account_controller(Coord* coord, LoginSvr* loginSvr) {
    this->coord = coord;
    this->loginSvr = loginSvr;
}

account_controller::~account_controller() {

}

int account_controller::main() {
    auto router = this->loginSvr->httpServer->Router;
    router->Post("/account/login", std::bind(&account_controller::reqLogin, this, std::placeholders::_1));
    router->Get("/gate/list", std::bind(&account_controller::reqList, this, std::placeholders::_1));
    return 0;
}

void account_controller::reqLogin(http::HttpRequest* request) {
    auto args = request->Json();
    printf("gggg %s\n", request->payload.Data());
    printf("gggg %s\n", args.GetString("nickname"));
    auto response = request->GetResponse();
    auto promise = this->loginSvr->loginCluster->getBalanceGate();
    if (promise == nullptr) {
        auto result = this->coord->Json->NewObject();
        result.SetInteger("code", 1);
        response->Json(result);
        return;
    }
    this->coord->DontDestory(request);
    promise->Then([this, request, response](auto client, auto reply){
        if (reply->Empty()) {
            auto result = this->coord->Json->NewObject();
            result.SetInteger("code", 1);
            response->Json(result);
            this->coord->Destory(request);
            return;
        }
        if (!reply->Array() || reply->ArrayCount() < 3 || reply->Empty(0)) {
            auto result = this->coord->Json->NewObject();
            result.SetInteger("code", 2);
            response->Json(result);
            this->coord->Destory(request);
            return;
        }
        auto result = this->coord->Json->NewObject();
        result.SetInteger("code", 0);
        auto data = result.SetObject("data");
        data.SetString("host", reply->String(0));
        data.SetString("port", reply->String(2));
        data.SetString("online", reply->String(3));
        data.SetString("version", reply->String(4));
        response->Json(result);
        this->coord->Destory(request);
        this->coord->CoreLogError("[login_cluster] test succ %s", reply->String());
    });
    promise->Else([this, request, response](auto client, auto reply){
        this->coord->CoreLogError("[login_cluster] test error");
        auto result = this->coord->Json->NewObject();
        result.SetInteger("code", 4);
        response->Json(result);
        this->coord->Destory(request);
    });
}

void account_controller::reqList(http::HttpRequest* request) {
    auto response = request->GetResponse();
    auto promise = this->loginSvr->loginCluster->getBalanceGate();
    if (promise == nullptr) {
        auto result = this->coord->Json->NewObject();
        result.SetInteger("code", 1);
        response->Json(result);
        return;
    }
    this->coord->DontDestory(request);
    promise->Then([this, request, response](auto client, auto reply){
        if (reply->Empty()) {
            auto result = this->coord->Json->NewObject();
            result.SetInteger("code", 1);
            response->Json(result);
            this->coord->Destory(request);
            return;
        }
        if (!reply->Array() || reply->ArrayCount() % 5 != 0) {
            auto result = this->coord->Json->NewObject();
            result.SetInteger("code", 2);
            response->Json(result);
            this->coord->Destory(request);
            return;
        }
        auto result = this->coord->Json->NewObject();
        result.SetInteger("code", 0);
        auto data = result.SetArray("data");

        for (int i = 0; i < reply->ArrayCount() / 5; i++) {
            auto gate = data.AddObject();
            gate.SetString("host", reply->String(0 + 5 * i));
            gate.SetString("port", reply->String(2 + 5 * i));
            gate.SetString("online", reply->String(3 + 5 * i));
            gate.SetString("version", reply->String(4 + 5 * i));
        }
        response->Json(result);
        this->coord->Destory(request);
        this->coord->CoreLogError("[login_cluster] test succ %s", reply->String());
    });
    promise->Else([this, request, response](auto client, auto reply){
        this->coord->CoreLogError("[login_cluster] test error");
        auto result = this->coord->Json->NewObject();
        result.SetInteger("code", 4);
        response->Json(result);
        this->coord->Destory(request);
    });
}
}
}
