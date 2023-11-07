//Code for consumer program
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
    struct sharedMemBuff consumerMem;

    sharedMemPath = argv[1];                                                   // grab shared memory path from command

    fd = shm_open(sharedMemPath, O_RDWR, 0);                                   // open shared memory
    ftruncate(fd, sizeof(*consumerMem));                                       // set to the size of the struct 

    consumerMem = static_cast<sharedMemBuff*>(mmap(NULL, sizeof(consumerMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

    for(int i = 4; i >= 0; --i) {
        sem_wait(&consumerMem -> full);                                        // check if buffer is full
        sem_wait(&consumerMem -> sem1);                                        // check if sem1 is not in use

        int consumerValue;                                    
        consumerValue = consumerMem -> table[consumerMem -> out];

        std::cout << "Consumed: " << consumerValue << std::endl;

        consumerValue -> out = ((consumerMem -> out) + 1) % SIZE;

        sem_post(&consumerMem -> sem1);                                        // release sem1 from being active
        sem_post(&consumerMem -> empty);                                       // mark buffer as empty

        sleep(rand() % 10);
    }

    shm_unlink(sharedMemPath);

    return 0;
}