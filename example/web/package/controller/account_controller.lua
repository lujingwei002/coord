_package_("controller")
component("AccountController")

local GET = {}

-- 登录
function GET.AccountLogin(self, request)
    local response = request:GetResponse()
    print(request.Query)
    response:Text("account/login")
end

function GET.AccountIndex(self, request)
    local response = request:GetResponse()
    response:Text("/")
end

function onAwake(self)
    Log('AccountController.onAwake')
    local router = coorda.WebServer.Router
    print("register /account/login", router:Get("/account/login", self, GET.AccountLogin))
    print("register /account/index", router:Get("/account/index", self, GET.AccountIndex))
    router:Trace()
end

function onDestory(self)
    print('AccountController.onDestory')
end
