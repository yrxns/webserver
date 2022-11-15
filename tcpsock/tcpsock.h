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
    }
    ~tcpsock();

    void bind(const char *addr, int port) {
        struct sockaddr_in serv_addr;
        bzero(&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        inet_pton(AF_INET, addr, &serv_addr.sin_addr.s_addr);
        serv_addr.sin_port = htons(port);

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
        socklen_t len = sizeof(struct sockaddr_in);
        int clnt_sock = ::accept(clnt_sock, (struct sockaddr*)clnt_addr, &len);

        if (clnt_sock == -1) {
            errmsg("accept()");
        }
        return clnt_sock;
    }

    operator int() {
        return sockfd;
    }

private:
    int sockfd;
};