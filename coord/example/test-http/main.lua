_package_('main')

local controller = import('test-http/controller')

function onDestory()
    package:Log('main.onDestory')
end

function onAwake()
    package:Log('main.onAwake')
    
    coorda:AddScript(controller.TestController)

end

