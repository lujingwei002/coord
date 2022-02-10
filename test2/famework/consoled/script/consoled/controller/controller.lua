_package_("controller")

function onAwake()
    local router = coorda.httpServer.Router
    router:StaticFile("/favicon.ico", "/client/asset/favicon.ico")
    router:StaticFile("/", "/client/index.html")
    router:StaticFile("/index.html", "/client/index.html")
    router:Static("/client/*", "")
end