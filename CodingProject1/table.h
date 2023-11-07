// Code for table structure
// Trevor McCormack
// CS33211

#ifndef TABLE_H
#define TABLE_H

#include <semaphore.h>

const int MAXITEMS = 5;            // max amount of items
const int TABLESIZE = 2;            // max amount allowed in the table at once

struct table {
    int sharedBuffer[2];            // shared array for both programs to use
    sem_t empty;                    // number of empty spaces
    sem_t full;                     // number of full spaces
};

#endif
