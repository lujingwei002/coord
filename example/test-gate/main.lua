_package_('test-gate')

import('example/test-gate/gate')

function onAwake()
    print('main.onAwake')
    --local config = coorda.gate:DefaultConfig()
    --config.host = "0.0.0.0"
    --config.port = 3333
    --coorda.gate:Start()
    --local scene = coorda:CreateScene("Main Scene")
    --local object = scene:CreateObject("Gate")
    --local listener = object:AddComponent(coord.TcpListener:New())
    --local http_server = object:AddComponent(coord.HttpServer:New())
    --local gate_handler = object:AddScript("gate.Gate")
    --listener:Listen("0.0.0.0", 3333)
    local err = coorda.proto:Import("gamepb.proto")
    --[[if true then
        print("aa1")
        local proto = coorda.proto:NewReflect("gamepb.TestLogin")
        print("aa2")
        local subProto = proto:Get("Login")
        subProto:Set("Nickname", "ljw")
        
        local protoArr = proto:Get("LoginArr")
        local protoArr0 = protoArr:Add()
        protoArr0:Set("Nickname", "bbb1")
        local protoArr1 = protoArr:Add()
        protoArr1:Set("Nickname", "bbb2")

        print(proto:Set("Nickname", "hello"))
        print(assert(proto:Get("Nickname") == "hello"))
        print('kkk', proto:DebugString())
    end--]]

    
    for i = 1, 2 do
        --local proto = coorda.proto:NewReflect("gamepb.TestLogin")
    end
    --print(collectgarbage ("count"))
    --collectgarbage ("collect")
    --print(collectgarbage ("count"))
    --print("ccccccccccccc", coorda.cluster.Name)
    --print("ccccccccccccc", coorda.cluster.FullName)
    --print("ccccccccccccc", coorda.cluster.Version)
    coorda:AddScript("gate.GateHandler")

    
end
 
function onDestory()
    print('main.onDestory')
end
