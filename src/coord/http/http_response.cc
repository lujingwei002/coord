#include "coord/http/http_response.h"
#include "coord/http/http_request.h"
#include "coord/http/http_agent.h"
#include "coord/coord.h"
#include "coord/http/http_server.h"
#include "coord/encrypt/sha1.h"
#include "coord/encrypt/base64.h"
#include "coord/io/io.h"
#include "coord/json/init.h"
#include "util/os/path.h"
#include <map>


namespace coord {
namespace http {
CC_IMPLEMENT(HttpResponse, "coord::http::HttpResponse")

HttpResponse::HttpResponse(Coord* coord, HttpAgent* agent, HttpRequest* request) : base_response(coord, agent, request) {
    this->request = request;
    this->statusCode = 200;
    this->server = request->server;
}

HttpResponse::~HttpResponse() {
}

void HttpResponse::SetStatusCode(int code) {
    this->statusCode = code;
}

int HttpResponse::Text(lua_State* L){
    if (!lua_isstring(L, 2)){
        this->coord->CoreLogError("arg error");
        return 0;
    }
    size_t len = 0;
    const char* data = (const char*)lua_tolstring(L, 2, &len);
    this->coord->CoreLogDebug("HttpResponse::Text data=%s, len=%d", data, len);
    this->body.Resize(0);
    coord::Append(this->body, data, len);
    this->contentType = "text/html";
    return 0;
}

void HttpResponse::PageNotFound() {
    this->statusCode = 404;
    this->contentType = "text/plain";
    coord::Appendf(this->body, "404 page not found");
}

void HttpResponse::Exception(const char* msg) {
    this->statusCode = 500;
    this->contentType = "text/plain";
    coord::Appendf(this->body, msg);
}

bool HttpResponse::Text(const char* content) {
    this->coord->CoreLogDebug("[HttpResponse] Text, content=%s", content);
    coord::Appendf(this->body, content);
    this->contentType = "text/plain";
    return true;
}

bool HttpResponse::Json(json::Reflect& json) {
    this->coord->CoreLogDebug("[HttpResponse] JSON, content=%s", json.ToString());
    if(json.Encode(this->body)){
        return false;
    }
   // this->body.Write(content, strlen(content));
    this->contentType = "application/json";
    return true;
}

bool HttpResponse::Allow() {
    
    return true;
}

bool HttpResponse::File(const char* path) {
    this->coord->CoreLogDebug("[HttpResponse] File, path=%s", path);
    int err = io::ReadFile(path, this->body);
    if (err) {
        this->PageNotFound();
        return false;
    }
    const char* fileType = os::path::FileType(path);
    this->contentType = http::GetContentType(fileType); 

    //ETag和If-None-Match控制缓存
    if (this->server->config.UseEtag) {
        //使用etag控制文件缓存
        static thread_local byte_slice etag;
        const char* ifNoneMatchHeader = this->request->GetHeader("if-none-match");
        int err = http::GetFileETag(this->body, etag);
        if (!err) {
            if (ifNoneMatchHeader != NULL && strcmp(etag.Data(), ifNoneMatchHeader) == 0) {
                this->body.Resize(0);
                this->statusCode = HttpStatusCode_NotModify;
                return true;
            } else {
                this->headerDict["ETag"] = etag.Data();
            }
        }
    }
    //Last-Modified和If-Modifyed-Since控制缓存
    if (this->server->config.UseEtag) {
        uv_stat_t* stat = io::FileStat(path);
        if (stat) {
        }
        const char* ifModifySince = this->request->GetHeader("if-modified-since");
        if (ifModifySince) {
            int64_t since = http::UnixTimeStamp(ifModifySince);
            if (since == stat->st_mtim.tv_sec) {
                this->body.Resize(0);
                this->statusCode = HttpStatusCode_NotModify;
                return true;
            }
        }
        const char* date = http::FromUnixTime(stat->st_mtim.tv_sec);
        this->headerDict["Last-Modified"] = date;
    }
    //使用cache-control 和 if-since-modify
    return true;
}

int HttpResponse::Upgrade() {
    static thread_local char secret[20];
    static thread_local byte_slice randomString;
    static thread_local byte_slice acceptKey;
    static thread_local char dateStr[128];
    size_t acceptKeyLen = 0;
 
    randomString.Resize(0);
    coord::Appendf(randomString, "%s", this->request->GetHeader("sec-websocket-key"));
    coord::Appendf(randomString, "%s", "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    //sha1加密
    encrypt::sha1::Encode(secret, randomString.Data(), randomString.Len());
    //编码成base64
    acceptKey.Reserve(encrypt::base64::EncodeLen(sizeof(secret)) + 1);//预留一个结束符
    int err = encrypt::base64::Encode(secret, sizeof(secret), acceptKey.Data(), &acceptKeyLen);
    if (err < 0){
        return err;
    }  
    acceptKey.Resize(acceptKeyLen + 1);
    acceptKey[acceptKeyLen] = 0;
    // 计算日期 
    time_t t = time(NULL);
    struct tm* tmp = localtime(&t);
    strftime(dateStr, sizeof(dateStr), "%a, %d %b %Y %H:%M:%S GMT", tmp);
    this->statusCode = 101;
    this->headerDict["Connection"] = "upgrade";
    this->headerDict["Upgrade"] = "WebSocket";
    this->headerDict["Access-Control-Allow-Credentials"] = "true";
    this->headerDict["Access-Control-Allow-Headers"] = "content-type";
    this->headerDict["Sec-WebSocket-Accept"] = acceptKey.Data();
    this->headerDict["Date"] = dateStr;
    return 0; 
}

int HttpResponse::flush() {
    this->headerDict["Access-Control-Allow-Credentials"] = "false";
    this->headerDict["Access-Control-Allow-Origin"] = "*";
    this->headerDict["Access-Control-Allow-Methods"] = "POST, GET, OPTIONS, PUT, DELETE,UPDATE";
    this->headerDict["Access-Control-Allow-Headers"] = "Content-Type";
    this->headerDict["Access-Control-Expose-Headers"] = "Content-Type";

    coord::Appendf(this->response, "HTTP/1.1 %d %s\r\n", this->statusCode, http_status_str((http_status)this->statusCode)); 
    size_t contentLength = this->body.Len();
    coord::Appendf(this->response, "Content-Length: %d\r\n", contentLength);
    //this->response.Writef("connection: close\r\n");
    coord::Appendf(this->response, "Server: coord\r\n");
    coord::Appendf(this->response, "Content-Type: %s\r\n", this->contentType.c_str());
    for(auto it = this->headerDict.begin(); it != this->headerDict.end(); ++it){
        coord::Appendf(this->response, "%s: %s\r\n", it->first.c_str(), it->second.c_str());
    }
    coord::Appendf(this->response, "\r\n");
    coord::Append(this->response, this->body.Data(), this->body.Len());
    //this->coord->CoreLogDebug("HttpResponse::Flush data=\n%s, len=%d", this->response.Data(), this->response.Len());
    this->request->send(this->response);
    return 0;
}
}
}
