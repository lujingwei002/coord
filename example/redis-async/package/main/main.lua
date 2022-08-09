_package_('main')

function onAwake()
    Log("OnAwake")
    local client = coorda:AsyncRedisConfig("REDIS")
    assert(client)
    local promise = client:Connect()
    promise:Then(function(client, reply)
        print('bbbbbbbbbbbbbbaaaaaaaaaaaa1')
    end):Else(function(client, reply)
        print('bbbbbbbbbbbbbbaaaaaaaaaaaa2')
    end)
end

function onDestory()
    Log("OnDestory")
end
