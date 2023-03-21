# WebServer 高性能服务器
## 功能
* 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型；

* 利用正则与状态机解析HTTP请求报文，实现处理静态资源的请求；

* 利用标准库容器封装char，实现自动增长的缓冲区；

* 基于小根堆实现的定时器，关闭超时的非活动连接；

* 利用单例模式与阻塞队列实现异步的日志系统，记录服务器运行状态；

* 利用RAII机制实现了数据库连接池，减少数据库连接建立与关闭的开销，同时实现了用户注册登录功能。
## 使用方法：
```sql
// 建立yourdb库
create database webse;

// 创建user表
USE yourdb;
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;
```

* `make`
* `./bin/server`

## 使用 Webbench 测试：

* `./webbench-1.5/webbench -c 10500 -t 5 http://ip:port/`

## 系列文章

[WebServer 高性能服务器]: https://blog.csdn.net/weixin_57209831/article/details/129629386?spm=1001.2014.3001.5502
[WebServer 高性能服务器v2]: https://blog.csdn.net/weixin_57209831/article/details/129647845?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22129647845%22%2C%22source%22%3A%22weixin_57209831%22%7D
[WebServer 高性能服务器v3]: https://blog.csdn.net/weixin_57209831/article/details/129673676?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22129673676%22%2C%22source%22%3A%22weixin_57209831%22%7D
[WebServer 高性能服务器v4]: https://blog.csdn.net/weixin_57209831/article/details/129697168?csdn_share_tail=%7B%22type%22%3A%22blog%22%2C%22rType%22%3A%22article%22%2C%22rId%22%3A%22129697168%22%2C%22source%22%3A%22weixin_57209831%22%7D

## 致谢
* 《Linux 高性能服务器编程》
* [markparticle/WebServer: C++ Linux WebServer服务器 (github.com)](https://github.com/markparticle/WebServer)
