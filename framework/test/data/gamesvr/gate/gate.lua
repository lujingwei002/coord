_package_("gate")

component("Gate")

function main()
end

function Awake(self)
    print('Gate.Awake')
end

function Update(self, now)
    print('Gate.Update', now)
end