_package_("scene")

Name = Name or 'scene1'

print('scene.import')
function test()
    print('scene.test', Name)
end

function main()
    print('scene.main', Name)
    Name = 'scene2'
end

function reload()
    print('scene.reload', Name)
end