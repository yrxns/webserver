#include "../udpsock/udpsock.h"
#include <unistd.h>
#include <iostream>

int main() {
    udpsock client;

    char buf[98];
    /* std::cin >> buf; */
    std::cin.getline(buf, 24);
    std::cout << buf << std::endl;
    client.connect("127.0.0.1", 9990);
    ssize_t len = client.sendto(buf, strlen(buf), nullptr, 0);
    write(client, buf, strlen(buf));
    std::cout << "fd: " << client << std::endl;
    std::cout << "send: " << buf << std::endl;
    std::cout << "send " << len << " byte..." << std::endl;

    return 0;
}
