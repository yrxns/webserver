#include "server.h"


server *server::getinstance() {
    static server it;
    return &it;
}
