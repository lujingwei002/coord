#pragma once 

namespace coord {//tolua_export
    namespace http {//tolua_export
        class HttpServer;
        class HttpRequest;
        class HttpAgent;
        class HttpRouter;
        class HttpResponse;
        typedef coord::RcRef<coord::http::HttpRequest> HttpRequestRef;//tolua_export
    }//tolua_export
} //tolua_export
