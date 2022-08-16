_package_('main')
_G.haha = 'hello haha'
function onAwake()
    Log("OnAwake")
    print('aaa', coorda.Script:ToJson({a = 1, b = "b"}))
    
    print(haha)
    local table = coorda.Script:NewString("hello")
    print(table:ToString())
    _G.ddd = 'ddd1'
end

function onDestory()
    Log("OnDestory")
    print(ddd)
end
