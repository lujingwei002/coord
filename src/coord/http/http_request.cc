#include "coord/http/http_request.h"
#include "coord/http/http_agent.h"
#include "coord/coord.h"
#include "coord/http/http_server.h"
#include "coord/http/http_response.h"
#include "coord/coordx.h"
#include <locale>         // std::locale, std::tolowe
namespace coord {

namespace http {
RC_IMPLEMENT(HttpRequest, "coord::http::HttpRequest")

int HttpRequest::on_message_begin(http_parser* parser){
    return 0;
}

int HttpRequest::on_url(http_parser* parser, const char *at, size_t length){
    HttpRequest* request = (HttpRequest*)parser->data;
    request->Url.assign(at, length);
    http_parser_url urlParser;
    http_parser_url_init(&urlParser);
    http_parser_parse_url(at, length, 1, &urlParser);
    // http://127.0.0.1/account/login?username=lujingwei
    // 路径 /account/login
    if(urlParser.field_set & (1 << UF_PATH)) {
        request->Path.assign(at + urlParser.field_data[UF_PATH].off, urlParser.field_data[UF_PATH].len);
        request->Route = request->Path;
    }
    // 查询字符串 username=lujingwei
    if(urlParser.field_set & (1 << UF_QUERY)) {
        request->Query.assign(at + urlParser.field_data[UF_QUERY].off, urlParser.field_data[UF_QUERY].len);
    }
    // http
    if(urlParser.field_set & (1 << UF_SCHEMA)) {
        request->Schema.assign(at + urlParser.field_data[UF_SCHEMA].off, urlParser.field_data[UF_SCHEMA].len);
    }
    // 127.0.0.1
    if(urlParser.field_set & (1 << UF_HOST)) {
        request->Host.assign(at + urlParser.field_data[UF_HOST].off, urlParser.field_data[UF_HOST].len);
    }
    return 0;
}

int HttpRequest::on_status(http_parser* parser, const char *at, size_t length){
    return 0;
}

int HttpRequest::on_header_field(http_parser* parser, const char *at, size_t length){
    HttpRequest* request = (HttpRequest*)parser->data;
    std::locale loc;
    request->tempHeaderField.assign(at, length);
    return 0;
}

int HttpRequest::on_header_value(http_parser* parser, const char *at, size_t length){
    HttpRequest* request = (HttpRequest*)parser->data;
    std::string value(at, length);
    std::string field = request->tempHeaderField;
    std::transform(field.begin(), field.end(), field.begin(), ::tolower);
    request->headerDict[field] = value;
    return 0;
}

int HttpRequest::on_headers_complete(http_parser* parser){
    HttpRequest* request = (HttpRequest*)parser->data;
    request->Method.assign(http_method_str((http_method)parser->method));
    std::transform(request->Method.begin(), request->Method.end(), request->Method.begin(), ::toupper);
    request->IsUpgrade = parser->upgrade == 1 ? true : false;
    return 0;
}

int HttpRequest::on_body(http_parser* parser, const char *at, size_t length){
    HttpRequest* request = (HttpRequest*)parser->data;
    coordx::Append(request->payload, at, length);
    coordx::Append(request->payload, 0);
    return 0;
}

int HttpRequest::on_message_complete(http_parser* parser){
    HttpRequest* request = (HttpRequest*)parser->data;
    request->isComplete = true;
    return 0;
}

int HttpRequest::on_chunk_header(http_parser* parser){
    return 0;
}

int HttpRequest::on_chunk_complete(http_parser* parser){
    return 0;
}

HttpRequest::HttpRequest(Coord* coord, HttpAgent* agent) : base_request(coord, agent) {
    this->server = agent->server;
    this->agent = agent;
    this->IsUpgrade = false;
    this->isComplete = false;
    this->initHttpParser();
    this->response = new HttpResponse(this->coord, this->server, agent, this);
}

HttpRequest::~HttpRequest() {
    if(this->response){
        this->coord->Destory(this->response);
        this->response = nullptr;
    }
}

void HttpRequest::initHttpParser() {
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
}

const char* HttpRequest::GetHeader(const char* field) {
    const auto it = this->headerDict.find(field);
    if(it == this->headerDict.end()) {
        return nullptr;
    }
    return it->second.c_str();
}

bool HttpRequest::HasHeader(const char* field, const char* value) {
    auto it = this->headerDict.find(field);
    if(it == this->headerDict.end()) {
        return false;
    }
    std::string v = it->second;
    std::transform(v.begin(), v.end(), v.begin(), ::tolower);
    return strcmp(v.c_str(), value) == 0;
}

size_t HttpRequest::recvData(char* data, size_t len) {
    size_t byteRead = http_parser_execute(&this->parser, &this->setting, data, len);
    return byteRead;
}

HttpResponse* HttpRequest::GetResponse() {
    return dynamic_cast<HttpResponse*>(this->response);
}


}

}
