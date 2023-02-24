#pragma once

using namespace std;

void permute(vector<string>& nums, int n, vector<string>& current, set<vector<string>>& result);
set<vector<string>> permute(vector<string>& nums, int n);