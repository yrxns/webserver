#include "../tcpsock/tcpsock.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

int main() {
    tcpsock server;
    server.bind("127.0.0.1", 8890);
    server.listen();

    /* int clnt_sock = server.accept(nullptr); */
    struct sockaddr_in clnt_addr;
    int clnt_sock = server.accept(&clnt_addr);

    char buf[24];
    read(clnt_sock, buf, 23);
    std::cout << buf << std::endl;
    std::cout << "client addr: " << clnt_addr.sin_addr.s_addr << std::endl;
    std::cout << "client port: " << clnt_addr.sin_port << std::endl;
    char s[120];
    inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, s, 120);
    std::cout << "client addr: " << s << std::endl;

    write(clnt_sock, "server ok...", 13);

    while(1);

    close(clnt_sock);
    close(server);
    return 0;
}
