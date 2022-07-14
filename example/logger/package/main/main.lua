_package_('main')


function onAwake()
    Log("OnAwake")
    Log(coorda.Environment:Get("config-dir"))
    coorda:Log({a = 3}, 'afasf')
end

function onDestory()
    Log("OnDestory")
end
