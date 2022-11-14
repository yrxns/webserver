#ifndef _cond_
#define _cond_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>

class cond {
public:

private:
    pthread_cond_t m_cond;
};


#endif
