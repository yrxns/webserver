#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../error/error.h"

//ip4, udp

class udpsock {
public:
    udpsock() {
        sockfd = socket(PF_INET, SOCK_DGRAM, 0);
        if (sockfd == -1) {
            errmsg("socket()");
        }

        int option = true;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&option, sizeof(option));
    }
    ~udpsock() {

    }

    //一般在server端使用
    void bind(const char *addr, int port) {
        struct sockaddr_in serv_addr = sockaddr_in(addr, port);

        if (::bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            errmsg("bind()");
        }
    }

    //客户端用于向udp套接字注册目标IP和端口信息，connect()后，sendto() 和 recvfrom()可不再传服务器地址结构体
    void connect(const char *addr, int port) {
        struct sockaddr_in serv_addr = sockaddr_in(addr, port);

        if (::connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            errmsg("connect()");
        }
    }

    ssize_t sendto(const void *buf, ssize_t n, const char *addr, int port) {
        ssize_t len;
        if (addr == nullptr) {
            len = ::sendto(sockfd, buf, n, 0, nullptr, 0);
        } else {
            struct sockaddr_in serv_addr = sockaddr_in(addr, port);
            len = ::sendto(sockfd, buf, n, 0,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
        }

        if (len == -1) {
            errmsg("sendto()");
        }
        return len;
    }

    ssize_t recvfrom(void *buf, size_t n, sockaddr_in * she) {
        ssize_t len;
        if (she != nullptr) {
            socklen_t size = sizeof(struct sockaddr_in);
            len = ::recvfrom(sockfd, buf, n, 0, (struct sockaddr*)she, &size);
        } else {
            len = ::recvfrom(sockfd, buf, n, 0, nullptr, 0);
        }

        if (len == -1) {
            errmsg("sendto()");
        }
        return len;
    }

    struct sockaddr_in sockaddr_in(const char *addr, int port) {
        struct sockaddr_in it;
        bzero(&it, sizeof(it));
        it.sin_family = AF_INET;
        inet_pton(AF_INET, addr, &it.sin_addr.s_addr);
        it.sin_port = htons(port);

        return it;
    }

    operator int() {
        return sockfd;
    }

private:
    int sockfd;
};
