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
    struct sharedMemBuff *shmp;

    sharedMemPath = argv[1];                                            // grab shared memory path from command

    fd = shm_open(sharedMemPath, O_CREAT | O_EXCL | O_RDWR, 0600);      // open shared memory
    ftruncate(fd, sizeof(*shmp));                                       // set to the size of the struct 

    sem_init((&shmp -> sem1), 1, 1);                                    // initialize first semaphore
    sem_init((*shmp -> empty), 1, SIZE);                                // initialize empty semaphore
    sem_init((*shmp -> full), 1, 0);                                    // initialize full semaphore

    shmp -> in = 0;
    shmp -> out = 0;

    for(int i = 4; i >= 0; --i) {
        sem_wait(*shmp -> empty);                                       // check if buffer is empty
        sem_wait(*shmp -> sem1);                                        // check if sem1 is not in use

        int producerValue = rand();                                     // create random producer value

        std::cout << "Produced: " << producerValue << std::endl;

        shmp -> table[shmp -> in] = producerValue;

        shmp -> in = ((shmp -> in) + 1) % SIZE;

        sem_post(&shmp -> sem1);                                        // release sem1 from being active
        sem_post(*shmp -> full);                                        // mark buffer as full

        sleep(rand() % 10);
    }

    shm_unlink(sharedMemPath);

    return 0;
}

