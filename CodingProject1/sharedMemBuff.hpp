#ifndef SHAREDMEMBUFF_HPP
#define SHAREDMEMBUFF_HPP

#include <semaphore.h>
#include <stdlib.h>

#define SIZE = 2


struct sharedMemBuff {
    int table[SIZE];

    sem_t sem1;
    sem_t empty;
    sem_t full;

    int in;
    int out;
};


#endif
