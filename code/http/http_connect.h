//
// Created by xuxinyu on 23-3-14.
//

#ifndef MYWEBSERVER_HTTP_CONNECT_H
#define MYWEBSERVER_HTTP_CONNECT_H

#include <sys/types.h>
#include <sys/uio.h>     // readv/writev
#include <arpa/inet.h>   // sockaddr_in
#include <cstdlib>      // atoi()
#include <cerrno>


#include "../buffer/buffer.h"
#include "http_request.h"
#include "http_response.h"
#include "../log/log.h"

class HttpConn {
public:
    HttpConn();

    ~HttpConn();

    void init(int sockFd, const sockaddr_in& addr);

    ssize_t read(int* saveErrno);

    ssize_t write(int* saveErrno);

    void Close();

    int GetFd() const;

    int GetPort() const;

    const char* GetIP() const;

    sockaddr_in GetAddr() const;

    bool process();

    int ToWriteBytes() {
        return iov_[0].iov_len + iov_[1].iov_len;
    }

    bool IsKeepAlive() const {
        return request_.IsKeepAlive();
    }

    static bool isET;
    static const char* srcDir;
    static std::atomic<int> userCount;

private:

    int fd_;
    struct sockaddr_in addr_;

    bool isClose_;

    int iovCnt_{};
    struct iovec iov_[2]{};

    Buffer readBuff_; // 读缓冲区
    Buffer writeBuff_; // 写缓冲区

    HttpRequest request_;
    HttpResponse response_;
};


#endif //MYWEBSERVER_HTTP_CONNECT_H
