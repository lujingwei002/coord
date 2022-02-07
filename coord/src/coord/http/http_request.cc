#include "coord/http/http_request.h"
#include "coord/http/http_agent.h"
#include "coord/coord.h"
#include "coord/http/http_server.h"
#include "coord/http/http_response.h"
#include "util/date/date.h"
#include <locale>         // std::locale, std::tolowe
namespace coord {

namespace http {
CC_IMPLEMENT(HttpRequest, "coord::http::HttpRequest")

static int on_message_begin(http_parser* parser){
    //printf("on_message_begin\n");
    return 0;
}

static int on_url(http_parser* parser, const char *at, size_t length){
    //printf("on_url ength:%d\n", length);
    HttpRequest* request = (HttpRequest*)parser->data;
    request->Url.assign(at, length);
    http_parser_url urlParser;
    http_parser_url_init(&urlParser);
    http_parser_parse_url(at, length, 1, &urlParser);
    if(urlParser.field_set & (1 << UF_PATH)) {
        request->Path.assign(at + urlParser.field_data[UF_PATH].off, urlParser.field_data[UF_PATH].len);
    }
    if(urlParser.field_set & (1 << UF_QUERY)) {
        request->Query.assign(at + urlParser.field_data[UF_QUERY].off, urlParser.field_data[UF_QUERY].len);
    }
    if(urlParser.field_set & (1 << UF_SCHEMA)) {
        request->Schema.assign(at + urlParser.field_data[UF_SCHEMA].off, urlParser.field_data[UF_SCHEMA].len);
    }
    if(urlParser.field_set & (1 << UF_HOST)) {
        request->Host.assign(at + urlParser.field_data[UF_HOST].off, urlParser.field_data[UF_HOST].len);
    }
    return 0;
}

static int on_status(http_parser* parser, const char *at, size_t length){
    //printf("on_status length:%d\n", length);
    return 0;
}

static int on_header_field(http_parser* parser, const char *at, size_t length){
    //printf("on_header_field length:%d\n", length);
    HttpRequest* request = (HttpRequest*)parser->data;
    std::locale loc;
    request->headerField.assign(at, length);
    return 0;
}

static int on_header_value(http_parser* parser, const char *at, size_t length){
    HttpRequest* request = (HttpRequest*)parser->data;
    std::string value(at, length);
    std::string field = request->headerField;
    std::transform(field.begin(), field.end(), field.begin(), ::tolower);
    //std::transform(value.begin(), value.end(), value.begin(), ::tolower);
    request->headerDict[field] = value;
    //printf("on_header_value %s:%s\n", field.c_str(), value.c_str());
    return 0;
}

static int on_headers_complete(http_parser* parser){
    //printf("on_headers_complete\n");
    HttpRequest* request = (HttpRequest*)parser->data;
    request->Method.assign(http_method_str((http_method)parser->method));
    std::transform(request->Method.begin(), request->Method.end(), request->Method.begin(), ::toupper);
    request->isUpgrade = parser->upgrade == 1 ? true : false;
    return 0;
}

static int on_body(http_parser* parser, const char *at, size_t length){
    HttpRequest* request = (HttpRequest*)parser->data;
    //request->Body.append(at, length);
    coord::Append(request->payload, at, length);
    coord::Append(request->payload, 0);
    //printf("on_body length:%d\n", length);
    return 0;
}

static int on_message_complete(http_parser* parser){
    //printf("on_message_complete\n");
    HttpRequest* request = (HttpRequest*)parser->data;
    request->isComplete = true;
    return 0;
}

static int on_chunk_header(http_parser* parser){
    printf("on_chunk_header\n");
    return 0;
}

static int on_chunk_complete(http_parser* parser){
    printf("on_chunk_complete\n");    
    return 0;
}

HttpRequest* newHttpRequest(Coord* coord, HttpAgent* agent) {
    HttpRequest* request = new HttpRequest(coord, agent);
    return request;
}

HttpRequest::HttpRequest(Coord* coord, HttpAgent* agent) : BaseRequest(coord) {
    this->agent = agent;
    this->server = agent->server;
    //this->coord = coord;
    this->response = NULL;
    this->sessionId = agent->sessionId;
    this->isUpgrade = false;
    this->isComplete = false;
    this->reqTime = uv_hrtime();
    http_parser_init(&this->parser, HTTP_REQUEST);
    this->parser.data = this;
    http_parser_settings_init(&this->setting);
    this->setting.on_message_begin = on_message_begin;
    this->setting.on_url = on_url;
    this->setting.on_status = on_status;
    this->setting.on_header_field = on_header_field;
    this->setting.on_header_value = on_header_value;
    this->setting.on_headers_complete = on_headers_complete;
    this->setting.on_body = on_body;
    this->setting.on_message_complete = on_message_complete;
    this->setting.on_chunk_header = on_chunk_header;
    this->setting.on_chunk_complete = on_chunk_complete;
    this->response = newHttpResponse(this);
    this->coord->DontDestory(this->agent);
}

HttpRequest::~HttpRequest() {
    this->coord->coreLogDebug("[HttpRequest] ~HttpRequest");
    if(this->response){
        delete this->response;
        this->response = NULL;
    }
    this->coord->Destory(this->agent);
}

const char* HttpRequest::GetHeader(const char* field) {
    const auto it = this->headerDict.find(field);
   // for (auto it = this->headerDict.begin(); it != this->headerDict.end(); ++it) {
     //   printf("%s\n", it->first.c_str());
    //    printf("%s\n", it->second.c_str());
   // }
    if(it == this->headerDict.end()) {
        return NULL;
    }
    return it->second.c_str();
}

bool HttpRequest::HasHeader(const char* field, const char* value) {
    auto it = this->headerDict.find(field);
    if(it == this->headerDict.end()) {
        return NULL;
    }
    std::string v = it->second;
    std::transform(v.begin(), v.end(), v.begin(), ::tolower);
    return strcmp(v.c_str(), value) == 0;
}

size_t HttpRequest::parse(char* data, size_t len) {
    size_t byteRead = http_parser_execute(&this->parser, &this->setting, data, len);
    return byteRead;
}

HttpResponse* HttpRequest::GetResponse() {
    return this->response;
}

void HttpRequest::onDestory() {
    this->response->flush();
    uint64_t duration = uv_hrtime() - this->reqTime;
    this->coord->LogDebug("[HttpRequest] %d | %10s | %16s | %8s \"%s\"", this->response->statusCode, date::FormatNano(duration), this->RemoteAddr.c_str(), this->Method.c_str(), this->Url.c_str());
    this->agent->reset();
}

int HttpRequest::send(byte_slice& data) {
    return this->agent->send(data);
}


}

}