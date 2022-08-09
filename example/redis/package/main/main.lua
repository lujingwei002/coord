_package_('main')

function onAwake()
    Log("OnAwake")
    local client = coorda:RedisConfig("REDIS")
    assert(client)
    local err = client:Connect()
    assert(err == 0)
    local reply = client:DEL("aa")
    local reply = client:GET("aa")
    assert(reply)
    assert(reply:Empty())
    local reply = client:SET("aa", "bb")
    assert(reply:Error() == false)
    local reply = client:GET("aa")
    assert(reply:String() == "bb")
end

function onDestory()
    Log("OnDestory")
end
