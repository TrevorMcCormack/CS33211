// Code for consumer program
// Trevor McCormack
// CS33211

#include "table.h"

#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int sharedMem; 
    int items;
    struct table *consumerMem;

    sharedMem = shm_open("SharedMemory", O_CREAT | O_RDWR, S_IRUSR | S_ IWUSR);


    if(sharedMem == -1) {           // checks if it did not access sharedMem
        printf("Error during opening shared memory");
    }

    if(ftruncate(sharedMem, sizeof(struct table)) == -1) {  // checks if it did not set to size of struct
        printf("Error during truncate");
    }
    else {
        ftruncate(sharedMem, sizeof(struct table));         // set to size of struct
    }

    consumerMem = mmap(0, sizeof(struct table), PROT_READ | PROT_WRITE, MAP_SHARED, shared, 0); // points to shared mem buffer
    items = 0;

    while(items < MAXITEMS) {
        while(consumerMem -> sharedBuffer[0] != 0 && consumerMem -> sharedBuffer[1] != 0);
        sleep(1);
        sem_wait(&consumerMem -> full);

        for(int i = 0; i < TABLESIZE; ++i) {
            int consumed = consumerMem -> sharedBuffer[i];   // create consumed int to use in printf
            printf("Removed by consumer: ", consumed, "\n");
            consumerMem -> sharedBuffer = 0;    // create an empty space
        }

        ++items;
        sem_post(&consumerMem -> empty);
    }
    
    return 0;
}
