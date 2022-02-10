_package_("controller")
component("TestController")

local GET = {}
local POST = {}

function onDestory(self)
    print('TestController.onDestory')
end

function onAwake(self)
    print('TestController.onAwake')
    package:LogError('aaa')
    package:LogDebug('aaa')
    --self:AddEventListener("testevent")

    local router = coorda.HttpServer.Router
    router:Get("/", self, GET.HandleHttpTest1)
    router:Get("/test", self, GET.HandleHttpTest2)
    router:Get("/test/1", self, GET.HandleHttpTest3)
    router:Post("/test/1/", self, POST.HandleHttpTest4)
    --router:GET("*", self, 'HandleHttpTest5')
    router:Get("/test/1/*", self, GET.HandleHttpTest6)
    --router:MESSAGE("/hello", self, 'HandleHttpFrame')
end

function test()
    print('http.test')
end

function HandleHttpFrame(self, frame)
    print("oooooooooooooooooo", frame.payload)
    --coorda:SendHttpFrame()
end

function GET.HandleHttpTest1(self, request)
    local response = request:GetResponse()
    response:Text("/")
end

function GET.HandleHttpTest2(self, request)
    local response = request:GetResponse()
    response:Text("/test")
end

function GET.HandleHttpTest3(self, request)
    local response = request:GetResponse()
    response:Text("/test/1")
end

function POST.HandleHttpTest4(self, request)
    local response = request:GetResponse()
    print('bbbbbbbbbbbbbbbbbbb', request.Url)
    print('bbbbbbbbbbbbbbbbbbb', request.Body)
    response:Text("/test/1/")
end

function GET.HandleHttpTest5(self, request)
    local response = request:GetResponse()
    response:Text("*")
end

function GET.HandleHttpTest6(self, request)
    local response = request:GetResponse()
    response:Text("/test/1/*")
end

function onUpdate(self, now)
    print('onUpdate')
    --print('Gate.Update', now)
    --local event = coord.EventArgs:new("name", "arg")
    --print(event)
    --coorda:Emit("testevent", event)
    --event:delete()
end

--收到事件
function OnEvent(self, name, args)
    print("HttpHandler.OnEvent", name, args, args.name, args.arg)
end
