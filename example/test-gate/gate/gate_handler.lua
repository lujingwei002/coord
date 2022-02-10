_package_("gate")
component("GateHandler")
--implement('IHttpHandler')

function onAwake(self)
    for k, v in pairs(__INTERFACE) do
        print(k, v)
    end
    print('GateHandler.onAwake', __INTERFACE[1])

    local router = coorda.gate.Router
    router:Request("game.login", self, 'HandleGameLogin')
    router:Request("daxigua.getdata", self, 'HandleGetData')
    router:Request("daxigua.roundstart", self, 'HandleRoundStart')
    router:Request("daxigua.*", self, 'HandleRoundStart')
    router:SessionClose(self, 'HandleSessionClose')
    router:SessionNew(self, 'HandleSessionNew')
    router:Trace()

    --测试cluster
    print('aaa', coorda.cluster)
    coorda.cluster.router:Notify("user.login_notify", self, "HandleUserLoginNotify")
    coorda.cluster.router:Notify("user.login_push", self, "HandleUserLoginPush")
    coorda.cluster.router:Request("user.login_req", self, "HandleUserLoginRequest")
    --coorda.cluster.router:Request("user.login2", nil, nil)
    coorda.cluster.router:Trace()
  --  coorda.cluster:Notify("gamesvr_1", "user.login_notify", "1234")
    print('ccccccccc')
    coorda.worker:Request('aa.bb', 'hello'):Then(self, "HandleWorkerThen"):Catch(self, "HandleWorkerCatch")
    if true then
        return
    end
    --self:SetInterval(1000, "HandleInterval")
    --self:SetTimeout(1000, "HandleTimeout")
    local conn = coorda:SQLConfig()
    local rows = conn:Query("select * from user")
    while rows:Next() do
        local row = rows:Lua()
        print(row, row.userid, row.nickname)
    end
    print("aaa", rows:ColumnCount())
    for i = 1, rows:ColumnCount() do
        print(rows:Column(i - 1))
    end
    coorda:Destory(rows)

    local result = conn:Execute("Update user set createtime=1 where userid = 1")
    if not result then
        print('fffffff', conn:Error())
    end
    print('affect', result:RowsAffected())
    --print(result:LastInsertId())
    coorda:Destory(result)
    --print(conn:Ping())

    local conn = coorda:RedisConfig()
    print(conn)
    print(conn:Connect())
    local reply = conn:SET("a", "b")
    print('reply', reply)
    print('reply', reply:Error())
    print('reply', reply:Empty())
    print('reply set a b', reply:String())
    coorda:Destory(reply)

    local reply = conn:GET("a")
    print('reply', reply)
    print('reply', reply:Error())
    print('reply', reply:Empty())
    print('reply get a', reply:String())
    coorda:Destory(reply)

    print('Cache', coorda:Cache("a", "b", 10))
    local reader = coorda:Cache("a")
    print('CacheGet', reader:String())
    coorda:Destory(reader)
    print("redis:TIME", conn:TIME())

    local conn = coorda:RedisAsyncConfig()
    print("redis async client", conn)
    local promise = conn:Connect()
    print("redis async client connect", promise)
    promise:Then(self, "HandleAsyncRedisConnect")
end

function HandleWorkerThen(self, result)
    print("HandleWorkerThen", result.Code, result:String())
    --coorda:Sleep(2000)
    --coorda.worker:Request('aa.bb', 'hello'):Then(self, "HandleWorkerThen"):Catch(self, "HandleWorkerCatch")
end

function HandleWorkerCatch(self, result)
    print("HandleWorkerThen")
end

function HandleAsyncRedisConnect(self, client, reply)
    print("HandleAsyncRedisConnect", client, reply:String())
    local promise = client:GET("a")
    print("redis async get promise", promise)
    promise:Then(self, "HandleAsyncRedisGet")
end

function HandleAsyncRedisGet(self, client, reply)
    print("HandleAsyncRedisGet", client, reply:String())
end

function HandleUserLoginRequest(self, request)
    print("HandleUserLoginRequest~~~~~~~~~", request:String())
    local response = request:GetResponse()
    local proto = request:Proto("gamepb.LoginRequest")
    print('ffff', proto:DebugString())

    local proto = response:Proto("gamepb.LoginResponse")
    proto:Set("Code", 2)
    print(proto:DebugString())
    response:Resolve()
end

function HandleUserLoginNotify(self, notify)
    print("HandleUserLoginNotify~~~~~~~~~", notify:String())
    coorda.cluster:Notify("gamesvr_1", "user.login_push", "5678")
end

function HandleUserLoginPush(self, notify)
    print("HandleUserLoginPush~~~~~~~~~", notify:String())
    local proto = coorda.proto:NewReflect("gamepb.LoginRequest")
    proto:Set("Nickname", "fff1")
    print(proto:DebugString())
    local promise = coorda.cluster:Request("gamesvr_1", "user.login_req", proto)
    --local promise = coorda.cluster:Request("gamesvr_1", "user.login2", "8888")
    promise:Then(self, "HandleUserLoginReqResolve"):Catch(self, "HandleUserLoginReqReject")
end

function HandleUserLoginReqResolve(self, result)
    print("HandleUserLoginReqResolve")
    local proto = result:Proto("gamepb.LoginResponse")
    print(proto:DebugString())
end

function HandleUserLoginReqReject(self, result)
    print("HandleUserLoginReqReject", result:String(), result.Code)
end

function Update(self, now)
    --print('Gate.Update', now)
end

function HandleInterval(self)
    print('HandleIntervalHandleIntervalHandleInterval')
    print(collectgarbage ("collect"))
end

function HandleTimeout(self)
    print('HandleTimeoutHandleTimeoutHandleTimeout')
end

function HandleSessionClose(self, session)
    print("HandleSessionClose HandleSessionClose HandleSessionClose", session.RemoteAddr, session.Id)
end

function HandleSessionNew(self, session)
    print("HandleSessionNew HandleSessionNew HandleSessionNew HandleSessionNew", session.RemoteAddr, session.Id)
end

function HandleGameLogin(self, session, request)
    print("HandleGameLogin HandleGameLogin HandleGameLogin", session.Id)
    local proto = request:Proto("gamepb.LoginRequest")
    print(proto:DebugString())
    print(proto:Get("Nickname"))
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.LoginResponse")
    reply:Set("Code", 0)
    reply:Set("Userid", 1)
end

function HandleGetData(self, session, request)
    print("HandleGetData HandleGetData HandleGetData", session.Id)
    local proto = request:Proto("gamepb.DaxiguaGetDataRequest")
    print(proto:DebugString())
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.DaxiguaGetDataResponse")
    reply:Set("Code", 0)
    reply:Set("Userid", 1)
end

function HandleRoundStart(self, session, request)
    print("bbbbbbbbbbbbbbbbbbbb3", request.sessionId)
    local proto = request:Proto("gamepb.DaxiguaStartRequest")
    print(proto:DebugString())
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.DaxiguaStartResponse")
    reply:Set("Code", 0)
    --reply:Set("Userid", 1)
    session:Kick("fffffffffffffffff")
    coorda.gate.Router:Trace()
end

--implement('IHttpHandler.RecvHttpRequest')
function RecvHttpRequest(self, request, response)
    print("ccccccc", request, request.headerLen, request.contentLength)
   -- print(request.headers[1].field.buf)
   print(request.url)
   print(request.method)
   print(request.body)
   print(request.sessionId)
   print(request:GetHeader('Connection'))
   --request:SendString("hello")
   response:SendString("hello")
   --print(request.bb.aa)
end
