#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <list>
#include <algorithm>

std::unordered_map<char, char> fundamental_algorithm(std::unordered_map<char, std::vector<char>>& preference1,
                                         std::unordered_map<char, std::vector<char>>& preference2) {
    // add 'o' at the end of each list 
    for (auto& entry : preference1) {
        entry.second.push_back('o');
    }

    for (auto& entry : preference2) {
        entry.second.push_back('o');
    }

    std::unordered_map<char, char> matching; // define matching
    // create lists of husbands and wives
    std::vector<char> husbands;
    std::vector<char> wives;
    
    for (const auto& entry : preference1) {
        husbands.push_back(entry.first);
    }

    for (const auto& entry : preference2) {
        wives.push_back(entry.first);
    }

    int k = 0;
    int n = wives.size();

    for (const auto& wife : wives) {
        matching[wife] = 'o';
    }

    while (k < n) {
        char X = husbands[k];
        while (X != 'o') {
            char x = preference1[X][0];
            std::vector<char>& prefer_x = preference2[x];
            char fiance_x = matching[x];
            int index_X = -1;
            int index_fiance_x = -1;
            // find the index of X in perfer_x
            for (int i = 0; i < prefer_x.size(); ++i) {
                if (prefer_x[i] == X) {
                    index_X = i;
                    break;
                }
            }
            // find the index of fiance_x in prefer_x
            for (int i = 0; i < prefer_x.size(); ++i) {
                if (prefer_x[i] == fiance_x) {
                    index_fiance_x = i;
                    break;
                }
            }

            if (index_X < index_fiance_x) {
                matching[x] = X;
                X = fiance_x;
            }

            if (X != 'o') {
                char elementToRemove = x;
                preference1[X].erase(std::remove(preference1[X].begin(), preference1[X].end(), elementToRemove), preference1[X].end());
            }
        }

        k = k + 1;
    }

    return matching;
}