_package_('main')

local controller = import('controller')

function onAwake()
    Log("OnAwake")
    coorda:AddScript(controller.AccountController)
end

function onDestory()
    Log("OnDestory")
end
