// Code for producer program
// Trevor McCormack
// CS33211

#include "table.h"

#include <sys/mman.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    srand(time(NULL));

    int sharedMem;
    struct table *producerMem;
    int items = 0;

    sharedMem = shm_open("/SharedMemory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); // location of shared memory

    if(sharedMem == -1) {           // checks if it did not access sharedMem
        printf("Error during opening shared memory");
    }

    if(ftruncate(sharedMem, sizeof(struct table)) == -1) {  // checks if it did not set to size of struct
        printf("Error during truncate");
    }
    else {
        ftruncate(sharedMem, sizeof(struct table));         // set to size of struct
    }

    producerMem = mmap(0, sizeof(struct table), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMem, 0);  // points to shared mem buffer
   
    if(producerMem == MAP_FAILED) {     // check if did not point to shared mem buffer
        printf("Error pointing to shared mem buffer");
    }

    sem_init(&producerMem -> empty, 1, TABLESIZE);        // initialize first semaphore
    sem_init(&producerMem -> full, 1, 0);                 //initialize second semaphore

    for(int i = 0; i < TABLESIZE; ++i) {  // setting the elements in shared buffer to 0 to show they are empty
        producerMem -> sharedBuffer[i] = 0;
    }

    while(items < MAXITEMS) {       
        while(producerMem -> sharedBuffer[0] != 0 && producerMem -> sharedBuffer[1] != 0);  // busy while items in shared buffer
            
        sleep(1);
        sem_wait(&producerMem -> empty);

        int valueOfItem;

        for(int i = 0; i < TABLESIZE; ++i) {                          // produces 2 items
            valueOfItem = rand() % 1000;                              // get random item values
            if(valueOfItem == 0) {                                    // sets valueOfItem to 1 if 0 is generated
                valueOfItem = 1;
            }

            producerMem -> sharedBuffer[i] = valueOfItem;             // puts value in shared buffer
            printf("Added by producer: ", valueOfItem, "\n");
        }

        ++items;
        sem_post(&producerMem -> full);
    }

    return 0;
}