_package_("controller")
component("AccountController")

local GET = {}

function onDestory(self)
    print('AccountController.onDestory')
end

function onAwake(self)
    print('AccountController.onAwake')
    print(self)
    local router = coorda.WebServer.Router
    print("register /account/login", router:Get("/account/login", self, GET.AccountLogin))
    print("register /", router:Get("/", self, GET.Index))
    router:Trace()
end

function GET.AccountLogin(self, request)
    local response = request:GetResponse()
    response:Text("account/login")
end

function GET.Index(self, request)
    local response = request:GetResponse()
    response:Text("/")
end
