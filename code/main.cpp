#include <unistd.h>
#include "server/webserver.h"

int main() {
    WebServer server(8080, 3, 60000, true);
    server.Start();
}
