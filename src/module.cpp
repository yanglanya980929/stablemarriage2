#include "Rcpp.h"
using namespace Rcpp;

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include "fundamental_algorithm.h"

std::unordered_map<std::string, std::string> stable_marriage(const std::string& filename1, const std::string& filename2){
    std::ifstream file1(filename1);

    std::unordered_map<char, std::vector<char>> table1;
    std::string line1;
    while (std::getline(file1, line1)) {
        std::istringstream iss(line1);
        char key1;
        char value1;
        iss >> key1;
        table1[key1] = std::vector<char>();

        while (iss >> value1) {
            table1[key1].push_back(value1);
        }
    }
    file1.close();

    // Read and store values from the second file ('table2.txt')
    std::ifstream file2(filename2);

    std::unordered_map<char, std::vector<char>> table2;
    std::string line2;
    while (std::getline(file2, line2)) {
        std::istringstream iss(line2);
        char key2;
        char value2;
        iss >> key2;
        table2[key2] = std::vector<char>();

        while (iss >> value2) {
            table2[key2].push_back(value2);
        }
    }
    file2.close();

    std::unordered_map<char, char> matching = fundamental_algorithm(table1, table2);

     // New map with string keys
    std::unordered_map<std::string, std::string> stringMatching;

    for (const auto& pair : matching) {
        std::string key(1, pair.first);    // Convert char to string for key
        std::string value(1, pair.second); // Convert char to string for value
        stringMatching[key] = value; // Copy the key-value pair
    }

    return stringMatching;
}

RCPP_MODULE(task1) 
{
function("rcpp_stable_marriage", &stable_marriage);
}
