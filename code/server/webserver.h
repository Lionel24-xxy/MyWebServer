//
// Created by xuxinyu on 23-3-16.
//

#ifndef MYWEBSERVER_WEBSERVER_H
#define MYWEBSERVER_WEBSERVER_H

#include <unordered_map>
#include <fcntl.h>       // fcntl()
#include <unistd.h>      // close()
#include <cassert>
#include <cerrno>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../http/http_connect.h"
#include "epoller.h"
#include "../pool/threadpool.h"
#include "../timer/heap_timer.h"
#include "../pool/sql_connect_pool.h"
#include "../log/log.h"

class WebServer {
public:
    WebServer(int port, int trigMode, int timeoutMS, bool OptLinger, int threadNum,
              int sqlPort, const char* sqlUser, const  char* sqlPwd, const char* dbName, int connPoolNum,
              bool openLog, int logLevel, int logQueSize);

    ~WebServer();
    void Start();

private:
    bool InitSocket_();
    void InitEventMode_(int trigMode);
    void AddClient_(int fd, sockaddr_in addr);

    void DealListen_();
    void DealWrite_(HttpConn* client);
    void DealRead_(HttpConn* client);

    static void SendError_(int fd, const char*info);
    void ExtentTime_(HttpConn* client);
    void CloseConn_(HttpConn* client);

    void OnRead_(HttpConn* client);
    void OnWrite_(HttpConn* client);
    void OnProcess(HttpConn* client);

    static const int MAX_FD = 65536;

    static int SetFdNonblock(int fd);

    int port_;
    bool openLinger_;
    int timeoutMS_;  /* 毫秒MS */
    bool isClose_;
    int listenFd_;
    char* srcDir_;

    uint32_t listenEvent_;
    uint32_t connEvent_;

    std::unordered_map<int, HttpConn> users_;
    std::unique_ptr<Epoller> epoller_;
    std::unique_ptr<ThreadPool> threadpool_;
    std::unique_ptr<HeapTimer> timer_;
};

#endif //MYWEBSERVER_WEBSERVER_H
