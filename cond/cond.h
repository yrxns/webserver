#ifndef _cond_
#define _cond_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>

class cond {
public:
    cond() {
        if (pthread_cond_init(&m_cond, NULL) != 0) {
            std::cout << "pthread_cond_init() error..." << std::endl;
            exit(-1);
        }
    }
    ~cond() {
        pthread_cond_destroy(&m_cond);
    }
    bool wait(pthread_mutex_t *m_mutex) {
        return pthread_cond_wait(&m_cond, m_mutex) == 0;
    }
    bool signal() {
        return pthread_cond_signal(&m_cond) == 0;
    }
    bool broadcast() {
        return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    pthread_cond_t m_cond;
};


#endif
