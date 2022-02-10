_package_("controller")
component("AccountController")

local Post = {}

function OnDestory(self)
    print('HttpHandler.OnDestory')
end

function onAwake(self)
    local router = coorda.HttpServer.Router
    router:Post("/account/login", self, Post.HandleLogin)
    router:Trace()
end

function Post.HandleLogin(self, request)
    local response = request:GetResponse()
    local json = request:Json()
    print("eeeeeeeeee", json:GetString("nickname"))
    response:Text("css/*")
end

function onUpdate(self)
end
