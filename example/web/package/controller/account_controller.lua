_package_("controller")
component("AccountController")

local GET = {}

function onDestory(self)
    print('AccountController.onDestory')
end

function onAwake(self)
    print('AccountController.onAwake')
    print(self)
    local router = coorda.HttpServer.Router
    print("register /account/login", router:Get("/account/login", self, GET.AccountLogin))
end

function GET.AccountLogin(self, request)
    print('bbbbbbbbbbbbbbbbbbb')
    local response = request:GetResponse()
    response:Text("/")
end

