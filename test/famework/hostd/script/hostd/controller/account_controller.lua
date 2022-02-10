_package_("controller")
component("AccountController")

local Get = {}

function OnDestory(self)
    print('HttpHandler.OnDestory')
end

function onAwake(self)
    local router = coorda.httpServer.Router
    router:Get("/aa", self, Get.HandleHttpTest1)
    router:Get("/aa/", self, Get.HandleHttpTest5)
    router:Get("/aa/bb", self, Get.HandleHttpTest2)
    router:Trace()
end

function Get.HandleHttpTest6(self, request)
    local response = request:GetResponse()
    response:Text("css/*")
end

function Get.HandleHttpTest1(self, request)
    local response = request:GetResponse()
    response:Text("/aa")
end

function Get.HandleHttpTest2(self, request)
    local response = request:GetResponse()
    response:Text("/aa/bb")
end

function Get.HandleHttpTest3(self, request)
    local response = request:GetResponse()
    response:Text("aa/bb")
end

function Get.HandleHttpTest4(self, request)
    local response = request:GetResponse()
    response:Text("*")
end

function Get.HandleHttpTest5(self, request)
    local response = request:GetResponse()
    response:Text("/aa/")
end

function Update(self)
end