_package_('main')

function onAwake()
    Log("OnAwake")
    local client = coorda:RedisConfig("REDIS")
    assert(client)
    local err = client:Connect()
    assert(err == 0)
    local reply = owner_move(client:DEL("aa"))
    local reply = owner_move(client:GET("aa"))
    assert(reply)
    assert(reply:Empty())
    local reply = owner_move(client:SET("aa", "bb"))
    assert(reply:Error() == false)
    local reply = owner_move(client:GET("aa"))
    assert(reply:String() == "bb")
    collectgarbage("collect")
    print('bbbbbbbbbbbbbb')
end

function onDestory()
    Log("OnDestory")
end
