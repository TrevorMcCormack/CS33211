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


paragraph about implementation


paragraph about output


Output:
