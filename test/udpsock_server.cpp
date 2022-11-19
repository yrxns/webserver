#include "../udpsock/udpsock.h"
#include <unistd.h>
#include <iostream>

int main() {
    udpsock server;
    server.bind("127.0.0.1", 9990);

    char buf[98];
    sockaddr_in clnt_adr;
    /* ssize_t len = server.recvfrom(buf, 98, nullptr); */
    ssize_t len = server.recvfrom(buf, 98, &clnt_adr);

    std::cout << "fd: " << server << std::endl;
    std::cout << "recv " << len << " byte..." << std::endl;
    std::cout << buf << std::endl;
    std::cout << "client port: " << clnt_adr.sin_port << std::endl;
    char ip[24];
    inet_ntop(AF_INET, &clnt_adr, ip, 24);
    std::cout << "client ip: " << clnt_adr.sin_port << std::endl;
    std::cout << "client ip: " << ip << std::endl;

    read(server, buf, 98);
    std::cout << buf << std::endl;

    return 0;
}
