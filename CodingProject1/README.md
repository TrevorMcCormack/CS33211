Coding Project 1
Trevor McCormack
CS33211

Assignment instructions:
Programming Assignment #1

In this programming assignment, you must provide the source codes, documents, and examples in detail on Github. They will be counted for the final score. Please submit the link to the project on Github. 

Requirements:
-	You are required to use C/C++ in Linux/Unix. You can consider installing VirtualBox in your non-Linux environment.
-	Programs must succeed in compilation and execution as required (80 points)
-	Readme, documentation and example are required (20 points).

Topic: Producer-Consumer Problem

The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use threads in the producer program and consumer program. Shared memory is used for the “table”.

We expect to use these two programs (producer and consumer) like this:

$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &




Included:
<semaphore.h>
<sys/mman.h>
<pthread.h>
<stdlib.h>
<stdio.h>
<time.h>
<sys/stat.h>
<unistd.h>
<fcntl.h>


Producer creates 2 random integers then puts them into the table. The consumer then consumes these 2 integers and removes them from the table and fills it with 0 to indicate empty space. The producer then creates another set of 2 integers and the cycle continues until "MAXITEMS" number of iterations which can be changed to any number. 


For the output, when both programs run it will create 5 item sets. In each of these item sets there will be 2 items which get added to the table by the producer and then removed from the table by the consumer. After completing the 5 item sets the producer will stop producing items and to end the program enter in the command: ctrl + c

Output:
[1] 844976
[2] 844977
Added by producer: 441
Added by producer: 559
Removed by consumer: 441
Removed by consumer: 559
Added by producer: 235
Added by producer: 886
Removed by consumer: 235
Removed by consumer: 886
Added by producer: 298
Added by producer: 452
Removed by consumer: 298
Removed by consumer: 452
Added by producer: 591
Added by producer: 384
Removed by consumer: 591
Removed by consumer: 384
Added by producer: 348
Added by producer: 627
Removed by consumer: 348
Removed by consumer: 627
^C
[1]-  Done                    ./producer
[2]+  Done                    ./consumer


