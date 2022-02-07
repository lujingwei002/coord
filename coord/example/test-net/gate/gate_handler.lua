_package_("gate")
component("Gate")
implement('IHttpHandler')

function main()
    print('Gate.main')
end

function Awake(self)
    for k, v in pairs(__INTERFACE) do
        print(k, v)
    end
    print('Gate.Awake', __INTERFACE[1])
end

function Update(self, now)
    --print('Gate.Update', now)
end

--implement('IHttpHandler.RecvHttpRequest')
function RecvHttpRequest(self, request, response)
    print("ccccccc", request, request.headerLen, request.contentLength)
   -- print(request.headers[1].field.buf)
   print(request.url)
   print(request.method)
   print(request.body)
   print(request.sessionId)
   print(request:GetHeader('Connection'))
   --request:SendString("hello")

   response:SendString("hello")
   --print(request.bb.aa)
end