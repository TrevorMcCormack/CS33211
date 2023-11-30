Coding Project 2
Trevor McCormack
CS33211

Assignment Instructions:
In this programming assignment, you are required to provide the source codes, documents, and examples in detail on github. You only need to submit your GitHub project to me.  

 

Requirements:

You are required to use C/C++ in Linux/Unix. You can consider installing virtualBox in your non-Linux environment.
Programs must succeed in compilation and execution as required (80 points)
Readme, documentation, and example are required (20 points).
 

Banker’s Algorithm for deadlock avoidance.

 

Considering a system with five processes P0 through P4 and three resources of type A, B, C. Resource type A has 10 instances, B has 5 instances and type C has 7 instances. Suppose at time t0 following snapshot of the system has been taken:

Process     |   Allocation      |   Max          |  Available    |
            |   A    B    C     |   A   B   C    |  A   B   C    |
__________________________________________________________________
P0          |   0    1    0     |   7   5   3    |  3   3   2    |
P1          |   2    0    0     |   3   2   2    |               |
P2          |   3    0    2     |   9   0   2    |               |
P3          |   2    1    1     |   2   2   2    |               |
P4          |   0    0    2     |   4   3   3    |               |




Implement the Banker’s algorithm to answer the following question： Is the system in a safe state? If Yes, then what is the safe sequence?

 

What should be included in the submission:

Source codes (C/C++)
Input file (you should create an input file, e.g., .txt, with your customized format that stores the data that is provided in the table).  
Your code should print out the safe sequence if the system is safe.
Documents and readme.


Included:
<iostream>
<fstream>
<string>
<ctype.h>
<vector>


The program reads in the data inputted in matrix.csv and stores the data into 3 different vectors. Allocation vector used for the allocation matrix, max vector for the max resource matrix, and available vector for the available resource list. Then the program creates a needed matrix by subtracting the allocated resource values from the max resource values. It prints all of the resource matrices to the console. Then it iterates through each process and determines whether there is a position in the sequence where the process finishes and it's needed resource is met. Then the program loops until either all finishable processes are finished it is possible a process will not have a position in the sequence where it can finish. Then the program iterates through the finish array and checks if all processes were finished. If not then the program will print the sequnce is unsafe. If it finishes then the program prints the processes in the safe sequnce order.


The output prints out all of the resource matrices then prints the safe sequnce if it is safe or prints that the sequnce is unsafe it it is not safe.

To compile the program use the commands:
g++ bankersalgorithm.cpp -o output
./output


Output:
Allocation resource table:
0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 

Max resource table:
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 

Available resources:
3 3 2 

Needed resource list:
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

The safe sequnce is:
P1 -> P3 -> P4 -> P0 -> P2