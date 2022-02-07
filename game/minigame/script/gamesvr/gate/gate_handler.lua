_package_("gate")
component("GateHandler")

local GATE = {}
local WORKER = {}

function onStart(self)
    self:LogInfo('onStart')
    local router = coorda.Gate.Router
    router:SessionClose(self, GATE.SessionClose)
    router:SessionNew(self, GATE.SessionNew)
    router:Auth("game.login", self, GATE.UserAuth)
    router:Instead(self, GATE.UserInstead)
    router:Login(self, GATE.UserLogin)
    router:Logout(self, GATE.UserLogout)
    router:Trace()
end

function onUpdate(self)
    --self:LogInfo('onUpdate')
end

function onAwake(self)
    self:LogInfo('onAwake')
end

function onReload(self)
    self:LogInfo('onReload')
end

function GATE.UserLogin(self, session)
    self:Log("UserLogin", session.RemoteAddr, session.Id, session.UserId)
end

function GATE.UserLogout(self, session)
    self:Log("UserLogout", session.RemoteAddr, session.Id, session.UserId)
end

function GATE.UserInstead(self, session)
    self:Log("UserInstead", session.RemoteAddr, session.Id, session.UserId)
end

function GATE.SessionClose(self, session)
    self:Log("SessionClose", session.RemoteAddr, session.Id)
end

function GATE.SessionNew(self, session)
    self:Log("SessionNew", session.RemoteAddr, session.Id)
end

function GATE.UserAuth(self, session, request)
    --1.验证登录，有可能会调用http等外部接口
    --2.到网关请求登录，有可能会把号顶下，有可能会要排队
    --3.数据库读取数据
    
    local proto = request:Proto("gamepb.LoginRequest")
    self:Log(proto:DebugString())
    local openId = proto:Get("Openid")
    self:Log("UserAuth1111111111111111", session.Id, openId)
    --验证登录
    coorda.Worker:Request('login.UserAuth', openId)
    :Using(request)
    :Else(self, WORKER.recvUserAuthErr)
    :Then(self, WORKER.recvUserAuthSucc)
end

function WORKER.recvUserAuthSucc(self, result, request)
    local userId, nickname = result:Unpack()
    self:Log("recvUserAuthSucc", userId)
    local session = request:GetSession()
    --到网关请求登录
    session:Login(userId)
    :Using(request)
    :Else(self, WORKER.recvUserLoginErr)
    :Then(self, WORKER.recvUserLoginSucc)
end

function WORKER.recvUserAuthErr(self, result, request)
    self:Log("recvUserAuthErr", result.Code)
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.LoginResponse")
    reply:Set("Code", result.Code)
end

--用户登录成功
function WORKER.recvUserLoginSucc(self, session, request)
    local userId = session.UserId
    self:Log("recvUserLoginSucc", session.UserId)
    --加载用户数据
    coorda.Worker:Request('login.loadUserData', userId)
    :Using(request)
    :Else(self, WORKER.recvLoadUserDataErr)
    :Then(self, WORKER.recvLoadUserDataSucc)
end

--用户登录出错
function WORKER.recvUserLoginErr(self, session, request)
    self:Log("recvUserLoginErr")
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.LoginResponse")
    reply:Set("Code", 500)
end

--加载数据出错
function WORKER.recvLoadUserDataErr(self, result, request)
    self:Log("recvLoadUserDataErr", result.Code, result:String(), result:Len())
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.LoginResponse")
    reply:Set("Code", result.Code)
end

--加载数据成功
function WORKER.recvLoadUserDataSucc(self, result, request)
    local session = request:GetSession()
    self:Log("recvLoadUserDataSucc", session.Id, session.UserId)
    local response = request:GetResponse()
    local proto = result:Proto("model.User")
    local user = proto
    self:Log("recvLoadUserDataSucc", proto:DebugString())
    local reply = response:Proto("gamepb.LoginResponse")
    reply:Set("Code", 0)
    reply:Set("Coin", user:Get("coin"))
    reply:Set("Score", user:Get("score"))
    reply:Set("Medal", user:Get("medal"))
    reply:Set("Diamond", user:Get("diamond"))
    reply:Set("Level", user:Get("level"))
    reply:Set("ServerTime", os.time())
end










