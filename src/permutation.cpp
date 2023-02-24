#include <iostream>
#include <vector>
#include <set>
#include "permutation.hpp"

// Recursive function that generates permutations of a given size n from the given array of strings
void permute(vector<string>& nums, int n, vector<string>& current, set<vector<string>>& result) {
    // If the size of the current permutation equals n, add it to the result set
    if (current.size() == n) {
        result.insert(current);
        return;
    }

    // Loop through all elements in the input array
    for (int i = 0; i < nums.size(); i++) {
        string num = nums[i];
        // Add the current element to the current permutation
        current.push_back(num);
        // Remove the current element from the input array to avoid duplicates
        nums.erase(nums.begin() + i);
        // Recursively generate permutations of the remaining elements in the input array
        permute(nums, n, current, result);
        // Re-insert the current element back into the input array for the next iteration
        nums.insert(nums.begin() + i, num);
        // Remove the current element from the current permutation for the next iteration
        current.pop_back();
    }
}

// Function that generates permutations of a given size n from the given array of strings
set<vector<string>> permute(vector<string>& nums, int n) {
    vector<string> current;
    set<vector<string>> result;
    permute(nums, n, current, result);
    return result;
}