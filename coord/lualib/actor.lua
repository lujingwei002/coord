--[[
这是一个实体的构造脚本，相当于UNITY的预设

1.本来想用继承Entity类来构造个性化的实体的，不过用脚本更好点，而且因为加入了组件功能，实体的多样性应该由组件来实现
2.实体的组织方法是树型结构，即可以在这里构建实体的时候加入子实体，如场景，玩家等分类

function create(self)
    --C++组件
    Entity.add_component(self, TestComponent:new())
    --lua组件
    Entity.add_script(self, 'ActorController')
end

上面是最基本的构造接口，当然可以写成配置的形式,比如

local prefab = {
   root = {
        --组件
        component = {
            {_script = 'ActorController', a = 1, b = 2},
            {_cls = 'TestController', a = 1, b = 2},
        },
        --玩家
        actors = {

        },
        --场景
        scenes = {

        },
   }
}

instantiate(prefab)

一个游戏的初始化可以来源于这样一个根节点

--]]

--function create(entity)
    --print('create entity')
    --print('entity.id', entity.id)
    --print('entity test', Entity.test(entity))
    --print('add test component', Entity.add_component(entity, TestComponent:new()))
    --print('get component', Entity.get_component(entity, 'TestComponent'))
    --local component = Entity.get_component(entity, 'TestComponent')
    --TestComponent.test(component)
    --print('add script component', Entity.add_script(entity, 'ActorController'))
    --local component = Entity.get_script(entity, 'ActorController')
    --ScriptComponent.test(component)
--end

ActorPrefab = {
    --组件
    [1] = {
        TestComponent = {a = 1, b = 2},
    },
    [2] = {
        ActorController = {a = 1, b = 2},
    },
    [3] = {
    },
    --玩家
    actors = {

    },
    --场景
    scenes = {

    },
}

