_package_("http")
component("HttpHandler")
--http.route('/Account/')
--implement('IHttpHandler')

function OnDestory(self)
    print('HttpHandler.OnDestory')
end

function Awake(self)
    --注册事件
    --self.On("http", "RecvHttpRequest")
    --self.On("http.RecvHttpRequest")
    --coord.event.http_RecvHttpRequest
    --for k, v in pairs(__INTERFACE) do
    --    print(k, v)
    --end
    --print('Gate.Awake', __INTERFACE[1])
    --self.Interface("IHttpHandler")
    print('Gate.Awake')
    self:AddEventListener("testevent")

    --self:AddHttpGet("*", 'HandleHttpRequest')
    --self:AddHttpGet("/test", 'HandleHttpTest')

    local router = coorda.httpServer.Router
    router:GET("/", self, 'HandleHttpTest1')
    router:GET("/test", self, 'HandleHttpTest2')
    router:GET("/test/1", self, 'HandleHttpTest3')
    router:POST("/test/1/", self, 'HandleHttpTest4')
    --router:GET("*", self, 'HandleHttpTest5')
    router:GET("/test/1/*", self, 'HandleHttpTest6')
    --router:MESSAGE("/hello", self, 'HandleHttpFrame')
end

function test()
    print('http.test')
end

function HandleHttpFrame(self, frame)
    print("oooooooooooooooooo", frame.payload)
    --coorda:SendHttpFrame()
end

function HandleHttpRequest(self, request)
    local response = request:GetResponse()
    response:Text("hello world11")
    coord.Destory(request)
end

function HandleHttpTest1(self, request)
    local response = request:GetResponse()
    response:Text("/")
    coord.Destory(request)
end

function HandleHttpTest2(self, request)
    local response = request:GetResponse()
    response:Text("/test")
    coord.Destory(request)
end

function HandleHttpTest3(self, request)
    local response = request:GetResponse()
    response:Text("/test/1")
    coord.Destory(request)
end

function HandleHttpTest4(self, request)
    local response = request:GetResponse()
    print('bbbbbbbbbbbbbbbbbbb', request.Url)
    print('bbbbbbbbbbbbbbbbbbb', request.Body)
    response:Text("/test/1/")
    --coord.Destory(request)
end

function HandleHttpTest5(self, request)
    local response = request:GetResponse()
    response:Text("*")
    coord.Destory(request)
end

function HandleHttpTest6(self, request)
    local response = request:GetResponse()
    response:Text("/test/1/*")
    coord.Destory(request)
end

function Update(self, now)
    --print('Gate.Update', now)
    --local event = coord.EventArgs:new("name", "arg")
    --print(event)
    --coorda:Emit("testevent", event)
    --event:delete()
end

--implement('IHttpHandler.RecvHttpRequest')
function RecvHttpRequest(self, request)
    local response = request:GetResponse()
    response:Text("hello world")
    coord.Destory(request)
   --print(request.bb.aa)
end

--收到事件
function OnEvent(self, name, args)
    print("HttpHandler.OnEvent", name, args, args.name, args.arg)
end