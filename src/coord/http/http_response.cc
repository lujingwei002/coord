#include "coord/http/http_response.h"
#include "coord/http/http_request.h"
#include "coord/http/http_agent.h"
#include "coord/coord.h"
#include "coord/http/http_server.h"
#include "coord/encrypt/sha1.h"
#include "coord/encrypt/base64.h"
#include "coord/json/inc.h"
#include "coord/coordx.h"
#include <map>



namespace coord {
namespace http {
RC_IMPLEMENT(HttpResponse, "coord::http::HttpResponse")

static std::map<int, std::string> contentTypeDict = {
    {base_message_data_type_string, "text/plain"}
};

static std::map<std::string, std::string> defaultHeaderArr = {
    {"Access-Control-Allow-Credentials", "false"},
    {"Access-Control-Allow-Origin", "*"},
    {"Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE,UPDATE"},
    {"Access-Control-Allow-Headers", "Content-Type"},
    {"Access-Control-Expose-Headers", "Content-Type"},
    {"Server", "Coord"}
};

static std::string defaultContentType = "text/plain";

HttpResponse::HttpResponse(Coord* coord, HttpServer* server, HttpAgent* agent, HttpRequest* request) : base_response(coord, agent, request) {
    this->request = request;
    this->Code = 200;
    this->server = server;
}

HttpResponse::~HttpResponse() {
}

void HttpResponse::SetStatusCode(int code) {
    this->Code = code;
}

int HttpResponse::Text(lua_State* L){
    if (!lua_isstring(L, 2)){
        this->coord->CoreLogError("arg error");
        return 0;
    }
    size_t len = 0;
    const char* data = (const char*)lua_tolstring(L, 2, &len);
    this->coord->CoreLogDebug("HttpResponse::Text data=%s, len=%d", data, len);
    this->Payload.Resize(0);
    coordx::Append(this->Payload, data, len);
    this->contentType = "text/html";
    this->DataType = base_message_data_type_string;
    return 0;
}

void HttpResponse::PageNotFound() {
    this->Code = 404;
    this->contentType = "text/plain";
    this->DataType = base_message_data_type_string;
    coordx::Appendf(this->Payload, "404 page not found");
}

void HttpResponse::Exception(const char* msg) {
    this->Code = 500;
    this->DataType = base_message_data_type_string;
    this->contentType = "text/plain";
    coordx::Appendf(this->Payload, msg);
}

bool HttpResponse::Text(const char* content) {
    this->coord->CoreLogDebug("[HttpResponse] Text, content=%s", content);
    coordx::Appendf(this->Payload, content);
    this->DataType = base_message_data_type_string;
    this->contentType = "text/plain";
    return true;
}

bool HttpResponse::Json(json::JsonRef& json) {
    this->coord->CoreLogDebug("[HttpResponse] JSON, content=%s", json->ToString());
    if(json->Dump(this->Payload)){
        return false;
    }
   // this->body.Write(content, strlen(content));
    this->contentType = "application/json";
    this->DataType = base_message_data_type_json;
    return true;
}

bool HttpResponse::Allow() {
    return true;
}

bool HttpResponse::File(const char* path) {
    this->coord->CoreLogDebug("[HttpResponse] File, path=%s", path);
    int err = coordx::path::ReadFile(path, this->Payload);
    if (err) {
        this->PageNotFound();
        return false;
    }
    const char* fileType = coordx::path::FileType(path);
    this->contentType = http::GetContentType(fileType); 
    this->DataType = base_message_data_type_string;

    //ETag和If-None-Match控制缓存
    if (this->server->config.UseEtag) {
        //使用etag控制文件缓存
        static thread_local byte_slice etag;
        const char* ifNoneMatchHeader = this->request->GetHeader("if-none-match");
        int err = http::GetFileETag(this->Payload, etag);
        if (!err) {
            if (ifNoneMatchHeader != NULL && strcmp(etag.Data(), ifNoneMatchHeader) == 0) {
                this->Payload.Resize(0);
                this->Code = HttpStatusCode_NotModify;
                return true;
            } else {
                this->headerDict["ETag"] = etag.Data();
            }
        }
    }
    //Last-Modified和If-Modifyed-Since控制缓存
    if (this->server->config.UseEtag) {
        uv_stat_t* stat = coordx::path::FileStat(path);
        if (stat) {
        }
        const char* ifModifySince = this->request->GetHeader("if-modified-since");
        if (ifModifySince) {
            int64_t since = http::UnixTimeStamp(ifModifySince);
            if (since == stat->st_mtim.tv_sec) {
                this->Payload.Resize(0);
                this->Code = HttpStatusCode_NotModify;
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
    coordx::Appendf(randomString, "%s", this->request->GetHeader("sec-websocket-key"));
    coordx::Appendf(randomString, "%s", "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
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
    this->Code = 101;
    this->headerDict["Connection"] = "upgrade";
    this->headerDict["Upgrade"] = "WebSocket";
    this->headerDict["Access-Control-Allow-Credentials"] = "true";
    this->headerDict["Access-Control-Allow-Headers"] = "content-type";
    this->headerDict["Sec-WebSocket-Accept"] = acceptKey.Data();
    this->headerDict["Date"] = dateStr;
    return 0; 
}

int HttpResponse::Flush() {

    byte_slice response;

    // Response Line
    coordx::Appendf(response, "HTTP/1.1 %d %s\r\n", this->Code, http_status_str((http_status)this->Code)); 
    
    // Content-Length
    size_t contentLength = this->Payload.Len();
    coordx::Appendf(response, "Content-Length: %d\r\n", contentLength);

    // Connection
    //this->response.Writef("connection: close\r\n");

    // Content-Type
    coordx::Appendf(response, "Content-Type: %s\r\n", this->contentType.c_str());

    // Default Header
    for(auto it = defaultHeaderArr.begin(); it != defaultHeaderArr.end(); ++it){
        coordx::Appendf(response, "%s: %s\r\n", it->first.c_str(), it->second.c_str());
    }
    // Other header
    for(auto it = this->headerDict.begin(); it != this->headerDict.end(); ++it){
        coordx::Appendf(response, "%s: %s\r\n", it->first.c_str(), it->second.c_str());
    }
    coordx::Appendf(response, "\r\n");

    // 序列化
    coordx::Append(response, this->Payload.Data(), this->Payload.Len());
    this->request->agent->response(this->request->Id, response);
    return 0;
}
}
}
