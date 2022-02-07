_package_("daxigua")
component("DaxiguaHandler")

local GATE = {}

function onStart(self)
    self:LogInfo('onStart')
    local router = coorda.Gate.Router
    --登录请求
    --router:Request("daxigua.getdata", self, GATE.GetData)
    --router:Request("daxigua.roundstart", self, GATE.RoundStart)
    --router:Request("daxigua.roundresult", self, GATE.RoundResult)
    router:Request("daxigua", self, GATE)
    router:Trace()
end

function onAwake(self)
    self:LogInfo('onAwake')
end

function onReload(self)
    self:LogInfo('onReload')
end

function GATE.GetData(self, session, request)
    self:LogInfo('GetData')
    local response = request:GetResponse()
    local proto = response:Proto("gamepb.DaxiguaGetDataResponse")
    proto:Set("Code", 0)
end

function GATE.RoundStart(self, session, request)
    self:Log('RoundStart')
    local response = request:GetResponse()
    local proto = response:Proto("gamepb.DaxiguaStartResponse")
    proto:Set("Code", 0)
    coorda.Worker:Notify('login.test', 11, 222)
end

function GATE.RoundResult(self, session, request)
    self:Log('RoundResult')
    local response = request:GetResponse()
    local proto = response:Proto("gamepb.DaxiguaResultResponse")
    proto:Set("Code", 0)
end
