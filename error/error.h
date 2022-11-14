#ifndef _error_
#define _error_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void errmsg(const char *errmsg) {
    perror(errmsg);
    exit(-1);
}


#endif
