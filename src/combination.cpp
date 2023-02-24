#include <iostream>
#include <vector>
#include <set>
#include "combination.hpp"

// Recursive function that generates combinations of a given size n from the given array of strings
void combine(vector<string>& nums, int n, int start, vector<string>& current, set<vector<string>>& result) {
    // If the size of the current combination equals n, add it to the result set
    if (current.size() == n) {
        result.insert(current);
        return;
    }

    // Loop through all elements in the input array starting from the current index
    for (int i = start; i < nums.size(); i++) {
        string num = nums[i];
        // Add the current element to the current combination
        current.push_back(num);
        // Recursively generate combinations of the remaining elements in the input array
        combine(nums, n, i + 1, current, result);
        // Remove the current element from the current combination for the next iteration
        current.pop_back();
    }
}

// Function that generates combinations of a given size n from the given array of strings
set<vector<string>> combine(vector<string>& nums, int n) {
    vector<string> current;
    set<vector<string>> result;
    combine(nums, n, 0, current, result);
    return result;
}