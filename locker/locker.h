#ifndef _locker_
#define _locker_

#include <pthread.h>
#include <stdlib.h>
#include <iostream>

class locker {
public:
    locker() {
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            std::cout << "pthread_mutex_init() fail..." << std::endl;
            exit(-1);
        }
    }
    ~locker() {
        pthread_mutex_destroy(&m_mutex);
    }
    bool lock() {
        return pthread_mutex_lock(&m_mutex) == 0;
    }
    bool unlock() {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }
    pthread_mutex_t *get() {
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};


#endif
