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
    
    return 0;
}