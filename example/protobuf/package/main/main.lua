_package_('main')

function onAwake()
    Log("OnAwake11")
    local user = coorda.Proto:NewMessage("test.User")
    user.nickname = "ljw"
    user:Set("score", 100) 
    print(user.nickname)
    print(user.score)
    print(user:ShortDebugString())
end

function onDestory()
    Log("OnDestory")
end
