//Code for producer program
//Trevor McCormack
//CS33211

#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <sys/mman.h>

#include "../include/sharedMemBuff.hpp"


int main(int argc, char *argv[]) {
    int fd;
    char *sharedMemPath;
    struct sharedMemBuff *producerMem;

    sharedMemPath = argv[1];                                            // grab shared memory path from command

    fd = shm_open(sharedMemPath, O_CREAT | O_EXCL | O_RDWR, 0600);      // open shared memory
    ftruncate(fd, sizeof(*producerMem));                                       // set to the size of the struct 

    sem_init((&producerMem -> sem1), 1, 1);                                    // initialize first semaphore
    sem_init((&producerMem -> empty), 1, SIZE);                                // initialize empty semaphore
    sem_init((&producerMem -> full), 1, 0);                                    // initialize full semaphore

    producerMem -> in = 0;
    producerMem -> out = 0;

    for(int i = 4; i >= 0; --i) {
        sem_wait(&producerMem -> empty);                                       // check if buffer is empty
        sem_wait(&producerMem -> sem1);                                        // check if sem1 is not in use

        int producerValue = rand();                                     // create random producer value

        std::cout << "Produced: " << producerValue << std::endl;

        producerMem -> table[producerMem -> in] = producerValue;

        producerMem -> in = ((producerMem -> in) + 1) % SIZE;

        sem_post(&producerMem -> sem1);                                        // release sem1 from being active
        sem_post(&producerMem -> full);                                        // mark buffer as full

        sleep(rand() % 10);
    }

    shm_unlink(sharedMemPath);

    return 0;
}

