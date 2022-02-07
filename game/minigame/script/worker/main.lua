_package_('main')

local gamesvr = import ('worker/gamesvr')


function onAwake()
    package:Log('worker.onAwake')
    coorda:AddScript(gamesvr.WorkerHandler)
end
 
function onDestory()
    package:Log('worker.onDestory')
end

function onReload()
    package:Log('worker.onReload')
end