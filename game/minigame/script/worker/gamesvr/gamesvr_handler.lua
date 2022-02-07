_package_('gamesvr')
component("WorkerHandler")

local WORKER = {}

function onStart(self)
    self:Log('onStart')
    local router = coorda.WorkerSlave.Router
    router:Request('login.UserAuth', self, WORKER.UserAuth)
    router:Request('login.loadUserData', self, WORKER.LoadUserData)
    router:Notify('login.test', self, WORKER.Test)
    router:Request('rank.GetScoreRank', self, WORKER.GetScoreRank)
    router:Request('rank.GetScoreDayRank', self, WORKER.GetScoreDayRank)
    router:Trace()
end

function onAwake(self)
    self:Log('onAwake')
end

function onReload(self)
    self:Log('onReload')
end

function WORKER.UserAuth(self, request)
    
    local openId = request:Unpack()
    print('ccccccccccccccccc1', openId)
    local response = request:GetResponse()
    local conn = coorda:SQLConfig()
    local rows = conn:Get("SELECT userid, nickname FROM user WHERE openid=?", openId)
    if not rows:Next() then
        response:Reject(404)
        return
    end
    print('ccccccccccccccccc2')
    local user = rows:Lua()
    response:Pack(user.userid, user.nickname)
    response:Resolve()
end

function WORKER.LoadUserData(self, request)
    local userId = request:Unpack()
    local response = request:GetResponse()
    self:Log("LoadUserData", userId)
    local conn = coorda:SQLConfig()
    local rows = conn:Get("SELECT userid, nickname, coin, score, medal, diamond, level FROM user WHERE userid=?", userId)
    if not rows:Next() then
        response:Reject(404)
        return
    end
    local user = rows:Proto("model.User")
    --self:Log(user:DebugString())
    response:Proto(user)
    response:Resolve()
end

function WORKER.Test(self, notify)
    self:Log('handleTest', notify:Unpack())
end

function WORKER.GetScoreRank(self, request)
    self:Log('GetScoreRank', request:Unpack())
    local conn = coorda:SQLConfig()
    local rows = conn:Query([[
        SELECT b.openid, b.nickname, b.avatar, a.score 
		FROM scorerank AS a 
		LEFT JOIN user AS b ON a.userid=b.userid 
		WHERE a.score > 0
		ORDER BY a.score desc, a.updatetime desc LIMIT 50
    ]])
    local userArr = {}
    while rows:Next() do
        local row = rows:Proto("model.RankUser")
        print(row:DebugString())
        table.insert(userArr, row)
    end
    local response = request:GetResponse()
    --response:Pack(unpack(userArr))
    response:Pack(userArr)
    --response:Pack(1, "2", "hello", nil, true, userArr[1], {1, 2, 3})
    --response:Table({1, 2, "3", ["4"]=4, a="a", b=userArr[1]})
    --local table = response:Table()
    --table:PushString("hello", "world")
    response:Resolve()
end

function WORKER.GetScoreDayRank(self, request)
    self:Log('GetScoreDayRank', request:Unpack())
end