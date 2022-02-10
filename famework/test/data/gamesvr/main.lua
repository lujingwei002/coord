_package_("gamesvr")

--print("__NAME", __NAME)
--print("__PACKAGE", __PACKAGE)
--print("__PATH", __PATH)
import('gamesvr/scene')
--print(scene.Name)
--scene.Name = 'scene2'
import('gamesvr/scene', 'scene', true)
--print(scene.Name)

import('github.com/lujingwei/test')
import('gamesvr/gate')

function main()
    print('gamesvr.main')
    local scene = coorda:CreateScene("Main Scene")
    print('cccc1', scene)
    local object = scene:CreateObject("Gate")
    print('cccc2', object)
    local component = object:AddScript("gate.Gate")
    print('cccc3', component)

    print('qqqqqqqqq', gate.Gate)
    gate.Gate.Update()
end