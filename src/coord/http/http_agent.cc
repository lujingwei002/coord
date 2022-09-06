#include "coord/http/http_agent.h"
#include "coord/http/http_request.h"
#include "coord/http/http_response.h"
#include "coord/http/http_server.h"
#include "coord/http/http_base.h"
#include "coord/coord.h"
namespace coord {
namespace http {
RC_IMPLEMENT(HttpAgent, "coord::http::HttpAgent")

HttpAgent::HttpAgent(Coord* coord, HttpServer* server, net::TcpAgent* tcpAgent) : base_agent(coord) {
    this->coord = coord;
    this->server = server;
    this->tcpAgent = tcpAgent;
    this->request = nullptr;
    this->IsUpgrade = false;
    this->handler = nullptr;
    this->requestId = 0;
    this->minimumAlreadyResponseRequestId = 0;
    this->tcpAgent->SetHandler(this);
    this->coord->DontDestory(this->tcpAgent);
    //开启https 
    if (this->server->config.SSLEncrypt) {
        this->ssl = SSL_new(this->server->sslContext);
        this->read_bio = BIO_new(BIO_s_mem());
        this->write_bio = BIO_new(BIO_s_mem());
        SSL_set_bio(this->ssl, this->read_bio, this->write_bio);
        SSL_set_accept_state(this->ssl);
    } else {
        this->ssl = nullptr;
        this->read_bio = nullptr;
        this->write_bio = nullptr;
    }
}

HttpAgent::~HttpAgent() {
    this->coord->CoreLogDebug("[HttpAgent] ~HttpAgent");
    if(nullptr != this->tcpAgent) {
        this->tcpAgent->SetHandler(nullptr);
        this->coord->Destory(this->tcpAgent);
        this->tcpAgent = nullptr;
    }
    if (nullptr != this->request) {
        this->coord->Destory(this->request);
        this->request = nullptr;
    }
    if (nullptr != this->ssl) {
        BIO_free(this->read_bio);
        BIO_free(this->write_bio);
       // SSL_shutdown(this->ssl);
        SSL_free(this->ssl);
        this->ssl = nullptr;
    }
}    

void HttpAgent::SetHandler(IHttpAgentHandler* handler) {
    this->handler = handler;
}

void HttpAgent::recvTcpNew(net::TcpAgent* tcpAgent) {
}

void HttpAgent::recvTcpClose(net::TcpAgent* agent){
    this->coord->CoreLogDebug("[HttpAgent] recvTcpClose sessionId=%d", this->SessionId);
    if(this->handler) {this->handler->recvHttpClose(this);}
    this->server->recvAgentClose(this);
}

void HttpAgent::recvTcpError(net::TcpAgent* agent){
    int sessionId = this->SessionId;
    this->coord->CoreLogDebug("[HttpAgent] recvTcpError sessionId=%d", sessionId);
}

int HttpAgent::recvTcpData(net::TcpAgent* agent, char* data, size_t len) {
    int sessionId = this->SessionId;
    this->coord->CoreLogDebug("[HttpAgent] recvTcpData sessionId=%d", sessionId);
    if (this->server->config.SSLEncrypt) {
        return this->recvEncryptData(data, len);
    } else {
        return this->recvData(data, len);
    }
}

int HttpAgent::recvEncryptData(char* data, size_t len) {
    //写进bio, 由openssl解密
    BIO_write(this->read_bio, data, len);
    if (!SSL_is_init_finished(ssl)) {
        // 末完成握手，数据交给accept处理
        int ret = SSL_accept (this->ssl);
        if (ret != 1) {
            int err = SSL_get_error(this->ssl, ret);
            if (err == SSL_ERROR_WANT_READ) {
            } else if (err == SSL_ERROR_WANT_WRITE) { 
            }
        } else {
            this->coord->CoreLogDebug("完成握手1");
            this->readDecryptData();
        }
        //握手过程中会产生要发送的数据
        this->writeBioToSocket();
    } else {
        this->coord->CoreLogDebug("完成握手2 %ld", len);
        this->readDecryptData();
    }
    return len;
}

int HttpAgent::recvData(char* data, size_t len) {
    if(this->IsUpgrade){
        if(nullptr == this->handler) {
            return len;
        }
        return this->handler->recvHttpData(this, data, len);
    } 
    // search delimit
    char* header = strstr(data, "\r\n\r\n");
    if(header == nullptr){
        return 0;
    }
    HttpRequest* request = this->request;
    if(request == nullptr){
        request = new HttpRequest(this->coord, this);
        request->Id = ++this->requestId;
        this->request = request;
    }
    size_t byteRead = request->recvData(data, len);
    if(!request->isComplete){
        return byteRead;
    }
    this->recvHttpRequest(request);    
    this->request = nullptr;
    return byteRead;
}

void HttpAgent::readDecryptData() {
    static thread_local byte_slice data;
    data.Reserve(this->server->config.RecvBufferSize);
    for(;;){
        //从bio中读取解密后的数据，读出来的是是一个完整的请求
        int byteRead = SSL_read(this->ssl, data.Data(), data.Capacity());
        if (byteRead < 0) {
            int err = SSL_get_error(this->ssl, byteRead);
            if (err == SSL_ERROR_WANT_READ) {
            } else if (err == SSL_ERROR_WANT_WRITE) {
                this->writeBioToSocket();
            }
            break;
        } else if(byteRead == 0) {
            break;
        } else {
            this->recvData(data.Data(), byteRead);
            break;
        }
    }
}

int HttpAgent::writeBioToSocket() {
    for(;;) {
        byte_slice data;
        data.Reserve(1024);
        int byteRead = BIO_read(this->write_bio, data.Data(), data.Capacity());
        //printf("write_bio_to_socket %d\n", byteRead);
        if (byteRead <= 0) {
            // 无数据可写。
            break;;
        }
        data.Resize(byteRead);
        int err = this->tcpAgent->Send(data);
        if (err) {
            return err;
        }
    }
    return 0;
}

void HttpAgent::recvHttpRequest(HttpRequest* request) {
    this->coord->CoreLogDebug("[HttpAgent] recvHttpRequest, url=%s", request->Url.c_str());
    if(this->request->HasHeader("connection", "upgrade")){
        //协议升级
        if(this->request->HasHeader("upgrade", "websocket")) {
            this->recvHttpUpgrade(request);
        } else {
            request->GetResponse()->PageNotFound();
        }
    } else {
        bool isKeepAlive = this->request->HasHeader("connection", "keep-alive");
        this->isKeepAlive = isKeepAlive;
        try{
            this->server->recvHttpRequest(this, request);
        } catch(HttpException& e){
            this->catchHttpException(request, e);
        } catch(HttpPageNotFoundException& e){
            this->catchPageNotFoundException(request, e);
        }
    }
    this->coord->Destory(request);
    if(!this->isKeepAlive && !this->IsUpgrade){
        this->Close();
    }
} 

void HttpAgent::catchHttpException(HttpRequest* request, HttpException& e) {
    HttpResponse* response = request->GetResponse();
    response->Exception(e.What());  
}

void HttpAgent::catchPageNotFoundException(HttpRequest* request, HttpPageNotFoundException& e) {
    request->GetResponse()->PageNotFound();
}

void HttpAgent::recvHttpUpgrade(HttpRequest* request) {
    HttpResponse* response = request->GetResponse();
    int err = response->Upgrade();
    if (err < 0){
        request->GetResponse()->PageNotFound();
        return;
    }
    this->IsUpgrade = true;
    this->server->recvHttpUpgrade(this, request);
}

void HttpAgent::Close() {
    this->tcpAgent->Close();
} 

int HttpAgent::send(const char* data, size_t len) {
    return -1;
}

int HttpAgent::send(byte_slice& data) {
    if (this->server->config.SSLEncrypt) {
        int byteWrite = SSL_write(this->ssl, data.Data(), data.Len());  
        return this->writeBioToSocket();
        //this->coord->CoreLogDebug("[HttpAgent] send, ret=%d", byteWrite);
        if (byteWrite > 0) {
            // 写入socket
            return this->writeBioToSocket();
        } else if (byteWrite == 0) {
            this->Close();
            return -1;
        } else {
            // 需要读取或写入数据。
            int err = SSL_get_error(this->ssl, byteWrite);
            if (err == SSL_ERROR_WANT_READ) {
            } else if (err == SSL_ERROR_WANT_WRITE) {
                return this->writeBioToSocket();
            }
        }
        return 0;
    } else {
        return this->tcpAgent->Send(data);
    }
}

void HttpAgent::responseWaitQueueIfNeed() {
    while (this->payloadWaitingResponse.size() > 0) {
        uint64_t requestId = this->requestIdWaitingResponse.top();
        if (requestId == this->minimumAlreadyResponseRequestId + 1) {
            this->requestIdWaitingResponse.pop();
            auto it = this->payloadWaitingResponse.find(requestId);
            if (it != this->payloadWaitingResponse.end()) {
                this->send(it->second);
                this->payloadWaitingResponse.erase(it);
            }
            this->minimumAlreadyResponseRequestId = requestId;
        } else {
            break;
        }
    }
}

int HttpAgent::response(uint64_t id, byte_slice& data) {
    if (id == this->minimumAlreadyResponseRequestId + 1) {
        this->minimumAlreadyResponseRequestId = id;
        return this->send(data);
    } else {
        this->requestIdWaitingResponse.push(id);
        this->payloadWaitingResponse[id] = data;
        this->responseWaitQueueIfNeed();
        return 0;
    }  
}

}
}
