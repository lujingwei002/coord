_package_('main')

local gate = import('gamesvr/gate')
local daxigua = import('gamesvr/daxigua')
local rank = import('gamesvr/rank')

local controller = import('loginsvr/controller')


function onAwake()
    package:Log("loginsvr.onAwake")
    local loginSvr = loginsvr.NewLoginSvr()
    coorda:AddComponent(loginSvr)
    coorda:AddScript(controller.AccountController)
    --coorda:AddScript(gate.GateHandler)
    --coorda:AddScript(daxigua.DaxiguaHandler)
    --coorda:AddScript(rank.RankHandler)
end
 
function onDestory()
    package:Log('loginsvr.onDestory')
end

function onReload()
    package:Log('loginsvr.onReload')
end
