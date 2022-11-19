#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "../error/error.h"

//ip4, stream

class tcpsock {
public:
    tcpsock() {
        sockfd = socket(PF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            errmsg("socket()");
        }

        int option = true;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&option, sizeof(option));
    }
    ~tcpsock() {

    }

    void bind(const char *addr, int port) {
        /* struct sockaddr_in serv_addr; */
        /* bzero(&serv_addr, sizeof(serv_addr)); */
        /* serv_addr.sin_family = AF_INET; */
        /* inet_pton(AF_INET, addr, &serv_addr.sin_addr.s_addr); */
        /* serv_addr.sin_port = htons(port); */
        struct sockaddr_in serv_addr = sockaddr_in(addr, port);

        if (::bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            errmsg("bind()");
        }
    }
    void listen(int num = 9) {
        if (::listen(sockfd, num) == -1) {
            errmsg("listen()");
        }
    }
    int accept(struct sockaddr_in *clnt_addr) {
        int clnt_sock;
        if (clnt_addr != nullptr) {
            socklen_t len = sizeof(struct sockaddr_in);
            clnt_sock = ::accept(sockfd, (struct sockaddr*)clnt_addr, &len);
        } else {
            clnt_sock = ::accept(sockfd, nullptr, 0);
        }

        if (clnt_sock == -1) {
            errmsg("accept()");
        }
        return clnt_sock;
    }

    void connect(const char *addr, int port) {
        /* struct sockaddr_in serv_addr; */
        /* bzero(&serv_addr, sizeof(serv_addr)); */
        /* serv_addr.sin_family = AF_INET; */
        /* inet_pton(AF_INET, addr, &serv_addr.sin_addr.s_addr); */
        /* serv_addr.sin_port = htons(port); */
        struct sockaddr_in serv_addr = sockaddr_in(addr, port);

        if (::connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
            errmsg("connect()");
        }
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
