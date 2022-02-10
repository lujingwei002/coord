_package_('main')

local controller = import('consoled/controller')


function onAwake()
    local consoled = consoled.NewConsoled()
    coorda:LogDebug('consoled start')
    coorda:AddComponent(consoled)
    coorda:AddScript(controller.AccountController)
end
 
function onDestory()
    print("fffffffffffffffffff2")
end
