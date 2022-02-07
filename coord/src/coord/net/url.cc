#include "coord/net/url.h"
#include "http-parser/http_parser.h"

namespace coord {
namespace net {
 
Url::Url() {
}

Url::~Url() { 
}

int Url::Parse(const char* data, size_t len) {
    http_parser_url url;
    http_parser_url_init(&url);
    int err = http_parser_parse_url(data, len, 0, &url);
    if (err != 0){
        return -1;
    }
    if(url.field_set & (1<<UF_HOST)) {
        this->Host.assign(data + url.field_data[UF_HOST].off, url.field_data[UF_HOST].len);
    }
    if(url.field_set & (1<<UF_PORT)) {
        this->Port = url.port;
    }
    if(url.field_set & (1<<UF_USERINFO)) {
        std::string userinfo;
        userinfo.assign(data + url.field_data[UF_USERINFO].off, url.field_data[UF_USERINFO].len);
        size_t index = userinfo.find(":");
        if(index != std::string::npos) {
            this->User = userinfo.substr(0, index);
            this->Password = userinfo.substr(index + 1);
        } else {
            this->User = userinfo;
        }  
    }
    if(url.field_set & (1<<UF_PATH)) {
        this->Path.assign(data + url.field_data[UF_PATH].off, url.field_data[UF_PATH].len);
    }
    if(url.field_set & (1<<UF_QUERY)) {
        this->Query.assign(data + url.field_data[UF_QUERY].off, url.field_data[UF_QUERY].len);
    }
    if(url.field_set & (1<<UF_FRAGMENT)) {
        this->Fragment.assign(data + url.field_data[UF_FRAGMENT].off, url.field_data[UF_FRAGMENT].len);
    }
    return 0;
}

}
}