_package_('test-gate')

import('test/test-gate/gate')

function main()
    print('gamesvr.main')
    local scene = coorda:CreateScene("Main Scene")
    local object = scene:CreateObject("Gate")
    local listener = object:AddComponent(coord.TcpListener:New())
    local http_server = object:AddComponent(coord.HttpServer:New())
    local gate_handler = object:AddScript("gate.Gate")
    listener:Listen("0.0.0.0", 3333)
end

function exit()
    static:LogMsg("exit")
end