#include "../tcpsock/tcpsock.h"
#include <unistd.h>
#include <iostream>

int main() {
    tcpsock server;
    server.bind("127.0.0.1", 8890);
    server.listen();

    int clnt_sock = server.accept(nullptr);
    /* struct sockaddr_in clnt_addr; */
    /* int clnt_sock = server.accept(&clnt_addr); */

    char buf[24];
    read(clnt_sock, buf, 23);
    std::cout << buf << std::endl;

    close(clnt_sock);
    close(server);
    return 0;
}
