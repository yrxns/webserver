#include "../tcpsock/tcpsock.h"
#include <unistd.h>

int main() {
    tcpsock client;
    char buf[18];
    client.connect("127.0.0.1", 8890);
    write(client, "client...", 10);

    read(client, buf, 18);

    while(1);
    close(client);

    return 0;
}
