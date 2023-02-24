#pragma once

using namespace std;

void combine(vector<string>& nums, int n, int start, vector<string>& current, set<vector<string>>& result);
set<vector<string>> combine(vector<string>& nums, int n);
