#include <unistd.h>
#include "server/webserver.h"

int main() {
    WebServer server(8080, 3, 60000, true, 8,                   /* 端口 ET模式 timeoutMs 优雅退出 线程池数量  */
                     3306, "root", "xxx", "webserver", 12,      /* Mysql配置：端口号，用户名，密码，数据库名称，连接池数量 */
                     true, 1, 1024);                            /* 日志开关 日志等级 日志异步队列容量 */
    server.Start();
}
