#include <unistd.h>
#include "server/webserver.h"

int main() {
    WebServer server(8080, 3, 60000, true, 8,
                     3306, "root", "xxx", "webserver", 12);
    server.Start();
}
