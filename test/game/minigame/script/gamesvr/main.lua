_package_('main')

local gate = import('gamesvr/gate')
local daxigua = import('gamesvr/daxigua')
local rank = import('gamesvr/rank')

function onAwake()
    package:Log("gamesvr.onAwake")
    --在默认的实体上创建组件
    coorda:AddScript(gate.GateHandler)
    coorda:AddScript(daxigua.DaxiguaHandler)
    coorda:AddScript(rank.RankHandler)
end
 
function onDestory()
    package:Log('gamesvr.onDestory')
end

function onReload()
    package:Log('gamesvr.onReload')
end
