#include "../tcpsock/tcpsock.h"
#include <unistd.h>

int main() {
    tcpsock client;
    client.connect("127.0.0.1", 8890);
    write(client, "client...", 10);

    return 0;
}
