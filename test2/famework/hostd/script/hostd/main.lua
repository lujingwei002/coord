_package_('main')

local controller = import('hostd/controller')


function onAwake()
    local hostd = hostd.NewHostd()
    coorda:LogDebug('hostd start')
    coorda:AddComponent(hostd)
    coorda:AddScript(controller.AccountController)
end
 
function onDestory()
    print("fffffffffffffffffff2")
end
