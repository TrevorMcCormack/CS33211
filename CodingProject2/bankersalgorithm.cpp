// Code for Banker's Algorithm
//Trevor McCormack
// CS33211

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <vector>


// function to read data from the matrix 
void inputFile(std::vector<std::vector<int>> &allocation, std::vector<std::vector<int>> &max, std::vector<int> &available, int &processes, int &resources) {
    std::ifstream in;   
    in.open("matrix.csv");                          // open matrix.csv

    if(!in) {                                       // checking if file did not open
        std::cerr << "File not Found" << std::endl;
        exit(1);
    }

    char ch;
    std::string str;
    int iterator = 0;
    std::vector<int> row;

    while(!in.eof()) {                              // while not end of file
        in.get(ch);                                 // get character

        if(!isdigit(ch)) {                          // check if ch is not numeric

            if(str != "") {                         // check if string is not blank
                int num = std::stoi(str);           // convert string to int

                if(iterator == 2) {                 // checks if iterator is 2
                    available.push_back(num);       // push num onto available
                }

                row.push_back(num);                 // push num onto row
            }

            str = "";                               // set string to blank
        }

        else if(isdigit(ch) && ch != ' ' && ch != ',') {
            str.push_back(ch);                      // adds ch to string if it is a number
        }

        if(ch == '\n') {                            // check if character is a newline
            iterator = 0;                           // resets the iterator
            row.clear();                            // clears the row values
        }

        else if(ch == ',') {
            if(iterator == 0) {                           
                allpcation.push_back(row);          // pushes row onto allocation vector
            }

            else if(iterator == 1) {
                max.push_back(row);                 // pushes row onto max vector
            }

            row.clear();
            iterator++;
        }
    }

    processes = allocation.size();                  // makes processes = number of rows in allocation
    resources = available.size();                   // makes resources = number of rows in available
}


int main() {
    int processes;
    int resources;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> max;
    std::vector<int> available;

    inputFile(allocation, max, available, processes, resources);


    std::cout << "Max resource table:" << std::endl;
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            std::cout << allocation[i][j] << " ";       //output allocation vector
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;


    std::cout << "Available resources:" << std::endl;
    for(int i = 0; i < resources; i++) {
        std::cout << available[i] << " ";   // output available vector
    }

    std::cout << std::endl;

    int finished[processes];                // for determining finished processes
    int end[processes];                     // for holding safe seq order
    int needed[processes][resources];       // for needed resources
    int it = 0;                             // iterator for order of processes

    for(int i = 0; i < processes; i++) {
        finished[i] = 0;                    // set all elements of finished to 0
    }

    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            needed[i][j] = max[i][j] - allocation[i][j];
        }
    }


    std::cout << "Needed resource list:" << std::endl;
    for(int i = 0; i < processes; i++) {
        for(int j = 0; j < resources; j++) {
            std::cout << needed[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for(int i = 0; i < processes; i++) {                // iterate through processes
        int flag = 0;                                   // flag set to false

        for(int j = 0; j < processes; j++) {            

            if(finished[j] == 0) {                      // if process is not finished

                for(int k = 0; k < resources; k++) {    // iterate through resources

                    if(needed[j][k] > available[k]) {   // check if needed > available
                        flag = 1;                       // set flag to true
                        break;
                    }
                }                                       // end k loop

                if(flag == 0) {                         // check if flag is false
                    end[it++] = j;                      // add process to position of iterator

                    for(int l = 0; l < resources; l++) {
                        available[l] = available[l] + allocation[j][l]; // add allocated resource to available
                    }                                   // end l loop

                    finished[j] = 1;                    // set finished to true
                }
            }
        }                                               // end j loop
    }                                                   // end i loop

    int flag = 1;                                       // safe flag is true
    for(int i = 0; i < processes; i++) {                // iterate through all processes
        if(finished[i] == 0) {                          // check if process is unfinished
            flag = 0;                                   // set safe flag to false
            std::cout << "The sequence is unsafe" << std::end;  
            break;
        }
    }


    if(flag == 1) {                                     // check if flag is safe
        std::cout << "The sequence is safe" << std::endl;

        for(int i = 0; i < processes - 1; i++) {
            std::cout << "P" << end[i] << " -> ";
        }

        std::cout << "P" << end[processes] << std::endl;    //print last process
    }
    
    return 0;
}