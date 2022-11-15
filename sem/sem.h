#ifndef _sem_
#define _sem_

#include <stdlib.h>
#include <semaphore.h>
#include <iostream>

class sem {
public:
    sem() {
        if (sem_init(&m_sem, 0, 0) != 0) {
            std::cout << "sem_init()..." << std::endl;
            exit(-1);
        }
    }
    sem(int num) {
        if (sem_init(&m_sem, 0, num) != 0) {
            std::cout << "sem_init()..." << std::endl;
            exit(-1);
        }
    }
    ~sem() {
        sem_destroy(&m_sem);
    }
    bool wait() {
        return sem_wait(&m_sem) == 0;
    }
    bool post() {
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};


#endif
