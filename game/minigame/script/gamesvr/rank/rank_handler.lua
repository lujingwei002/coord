_package_("rank")
component("RankHandler")

local GATE = {}
local WORKER = {}

function onStart(self)
    self:LogInfo('onStart')
    local router = coorda.Gate.Router
    
    --登录请求
    router:Request("game.getscorerank", self, GATE.GetScoreRank)
    router:Request("game.getmedalrank", self, GATE.GetMedalRank)
    router:Trace()
end

function onAwake(self)
    self:LogInfo('onAwake')
end

function onReload(self)
    self:LogInfo('onReload')
end

function GATE.GetScoreRank(self, session, request)
    self:LogInfo('GetScoreRank')
    local proto = request:Proto("gamepb.GetMedalRankResponse")
    print(proto:DebugString())
    --coorda:DontDestory(request)
    coorda.Worker:Request('rank.GetScoreRank')
    :Using(request)
    :Else(self, WORKER.getScoreRankErr)
    :Then(self, WORKER.getScoreRankSucc)

    --local response = request:GetResponse()
    --local proto = response:Proto("gamepb.GetScoreRankResponse")
    --proto:Set("Code", 0)
end

function GATE.GetMedalRank(self, session, request)
    self:LogInfo('GetMedalRank')
    local proto = request:Proto("gamepb.GetMedalRankRequest")
    print(proto:DebugString())
    local response = request:GetResponse()
    local proto = response:Proto("gamepb.GetMedalRankResponse")
    proto.Code = 0
end

function WORKER.getScoreRankSucc(self, result, request)
    self:Log("getScoreRankSucc", result.Code)
    local userArr = result:Unpack()
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.GetScoreRankResponse")
    local users = reply.Users
    for _, rankUser in pairs(userArr) do
        local user = users:Add()
        user.Openid = rankUser.openid
        user.Nickname = rankUser.nickname
        user.Avatar = rankUser.avatar
        user.Score = rankUser.score
        if user.Avatar == "" then
            user.Avatar = "https://pic1.zhimg.com/v2-0e12707217a7c6d403259d9667f5d864_r.jpg"
        end
    end 
    reply.Score = 0
    reply.Rank = 1
    reply.Code = result.Code
end

function WORKER.getScoreRankErr(self, result, request)
    self:Log("getScoreRankErr", result.Code)
    local response = request:GetResponse()
    local reply = response:Proto("gamepb.GetScoreRankResponse")
    reply:Set("Code", result.Code)
end