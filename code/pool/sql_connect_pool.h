//
// Created by xuxinyu on 23-3-19.
//

#ifndef MYWEBSERVER_SQL_CONNECT_POOL_H
#define MYWEBSERVER_SQL_CONNECT_POOL_H

#include <mysql/mysql.h>
#include <string>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <thread>
#include <cassert>

#include "/usr/include/mysql/mysql.h"
#include "../log/log.h"

class SqlConnPool {
public:
    static SqlConnPool *Instance();

    MYSQL *GetConn();
    void FreeConn(MYSQL * conn);

    void Init(const char* host, int port,
              const char* user,const char* pwd,
              const char* dbName, int connSize);
    void ClosePool();

    SqlConnPool(const SqlConnPool&) = delete;
    SqlConnPool& operator=(const SqlConnPool&) = delete;

private:
    SqlConnPool() = default;
    ~SqlConnPool();

    int MAX_CONN_;

    std::queue<MYSQL *> connQue_;
    std::mutex mtx_;
    sem_t semId_;                   // 创建信号量
};

#endif //MYWEBSERVER_SQL_CONNECT_POOL_H
