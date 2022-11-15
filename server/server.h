#ifndef _server_
#define _server_
#include <sys/socket.h>

class server {
public:
    server();
    ~server();

    static server *getinstance();

private:
    int serv_sock;
};

#endif
