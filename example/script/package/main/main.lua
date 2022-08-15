_package_('main')

function onAwake()
    Log("OnAwake")
    print('aaa', coorda.Script:ToJson({a = 1, b = "b"}))
end

function onDestory()
    Log("OnDestory")
end
