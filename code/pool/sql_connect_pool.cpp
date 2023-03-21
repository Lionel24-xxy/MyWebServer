//
// Created by xuxinyu on 23-3-19.
//

#include <iostream>
#include "sql_connect_pool.h"
using namespace std;

SqlConnPool::~SqlConnPool() {
    ClosePool();
}

SqlConnPool* SqlConnPool::Instance() {      // 使用静态变量的懒汉单例模式
    static SqlConnPool connPool;
    return &connPool;
}

// 初始化数据库连接池
void SqlConnPool::Init(const char* host, int port,
                       const char* user,const char* pwd, const char* dbName,
                       int connSize = 10) {
    assert(connSize > 0);
    for (int i = 0; i < connSize; i++) {
        MYSQL *sql = nullptr;
        sql = mysql_init(sql);
        if (!sql) {
            LOG_ERROR("MySql init error!");
            cout << "MySql init error!" << endl;
            assert(sql);
        }
        sql = mysql_real_connect(sql, host,
                                 user, pwd,
                                 dbName, port, nullptr, 0);
        if (!sql) {
            LOG_ERROR("MySql Connect error!");
            cout << "MySql Connect error!" << endl;
        }
        connQue_.push(sql);
    }
    MAX_CONN_ = connSize;
    sem_init(&semId_, 0, MAX_CONN_);    // 初始化信号量
}

MYSQL* SqlConnPool::GetConn() {                 // 从连接池取一个连接
    MYSQL *sql = nullptr;
    if(connQue_.empty()){
        LOG_WARN("SqlConnPool busy!");
        return nullptr;
    }
    sem_wait(&semId_);                      // 等待信号量
    {
        lock_guard<mutex> locker(mtx_);       // 操作数据库连接池需要加锁
        sql = connQue_.front();
        connQue_.pop();
    }
    return sql;
}

void SqlConnPool::FreeConn(MYSQL* sql) {        // 释放一个连接
    assert(sql);
    lock_guard<mutex> locker(mtx_);
    connQue_.push(sql);
    sem_post(&semId_);                     // 释放信号量
}

void SqlConnPool::ClosePool() {
    lock_guard<mutex> locker(mtx_);
    while(!connQue_.empty()) {
        auto item = connQue_.front();
        connQue_.pop();
        mysql_close(item);
    }
    mysql_library_end();
}