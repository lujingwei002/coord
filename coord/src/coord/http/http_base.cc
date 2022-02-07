#include "coord/http/http_base.h"
#include "coord/coord.h"
#include "coord/encrypt/sha1.h"
#include "coord/encrypt/base64.h"
#include <string>
#include <map>

namespace coord {
namespace http {

std::map<std::string, std::string> httpContentType = {
    {"png",     "image/png"},
    {"jpg",     "image/jpg"},
    {"jpeg",    "image/jpeg"},
    {"ico",     "application/x-ico"},
    {"js",      "application/javascript"},
    {"css",     "text/css"},
    {"html",    "text/html"},
    {"htm",     "text/html"},
    {"gif",     "image/gif"},

};

std::string defaultHttpContentType = "application/octet-stream";

const char* GetContentType(const char* ext) {
    auto it = httpContentType.find(ext);
    if (it != httpContentType.end()) {
        return it->second.c_str();
    }
    return defaultHttpContentType.c_str();
}

int GetFileETag(byte_slice& data, byte_slice& etag) {
    static thread_local char etagSha1[20];
    size_t len = 0;
    //sha1加密
    encrypt::sha1::Encode(etagSha1, data.Data(), data.Len());
    //编码成base64
    etag.Reserve(encrypt::base64::EncodeLen(sizeof(etagSha1)) + 1);//预留一个结束符
    int err = encrypt::base64::Encode(etagSha1, sizeof(etagSha1), etag.Data(), &len);
    if (err) {
        return err;
    }  
    etag.Resize(len + 1);
    etag[len] = 0;
    return 0;
}

const char* FromUnixTime(int64_t t) {
    static thread_local char date[128];
    struct tm* tmp = localtime(&t);
    strftime(date, sizeof(date), "%a, %d %b %Y %H:%M:%S GMT", tmp);
    return date;
}

int64_t UnixTimeStamp(const char *date) {
  static thread_local struct tm stm;  
  strptime(date, "%a, %d %b %Y %H:%M:%S GMT", &stm);
  long t = mktime(&stm);
  return t;
}

}
} 