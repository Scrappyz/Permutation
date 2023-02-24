#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <sstream>
#include "combination.hpp"
#include "permutation.hpp"

using namespace std;

template<typename T>
void print(const vector<T> &v)
{
    for(auto n : v) {
        cout << n << ", ";
    }
}

template<typename K, typename V>
void printMap(const unordered_map<K, V>& m)
{
    for(const auto& i : m) {
        cout << "[" << i.first << ", " << i.second << "]" << endl;
    }
}

void printSet(const set<vector<string>>& s)
{
    for (const auto& permutation : s) {
        cout << "{";
        for (int i = 0; i < permutation.size(); i++) {
            cout << permutation[i];
            if (i != permutation.size() - 1) {
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
}

void missingArgs(const string& program_name, const string& error, const string& advice)
{
    cout << error << endl;
    cout << advice << program_name << " -h" << endl;
}

int factorial(int n)
{
    if(n <= 1)
        return 1;
    return n * factorial(n-1);
}

void printFormula(const unordered_map<string, bool>& options, int n, int r)
{
    if(options.at("-p") || options.at("--permutation")) {
        cout << "n!/(n-r)! = " << n << "!/(" << n;
        if(r >= 0) cout << "-";
        cout << r << ")! = " << factorial(n) / factorial(n-r);
    } else if(options.at("-c") || options.at("--combination")) {
        cout << "n!/r!(n-r)! = " << n << "!/" << r << "!(" << n;
        if(r >= 0) cout << "-";
        cout << r << ")! = " << factorial(n) / (factorial(r)*factorial(n-r));
    }
    cout << endl;
}

string getProgramName(const vector<string>& args)
{
    string str = args[0];
    for(int i = str.size()-1; i>=0; i--) {
        if(str[i] == '\\' || str[i] == '/') {
            str.erase(str.begin(), str.begin()+(i+1));
            break;
        }
    }
    return str;
}

int getSampleSize(const vector<string>& args) // extract a number from args (which is the sample size)
{
    for(int i = 0; i<args.size(); i++) {
        if(args[i][0] >= '0' && args[i][0] <= '9') {
            stringstream ss(args[i]);
            int x = 0;
            ss >> x;
            return x;
        }
    }
    return 0;
}

string getArray(const vector<string>& v) // extract the array '{a1, a2, a3}' from args
{
    for(int i = 0; i<v.size(); i++) {
        if(v[i][0] == '{' || v[i][0] == '[' || v[i][0] == '(')
            return v[i];
    }
    return string();
}

vector<string> parseArray(const string& str) // parse array into more readable form
{
    string temp;
    vector<string> v;
    for(int i = 0; i<str.size(); i++) {
        if(str[i] >= 'A' && str[i] <= 'Z' || str[i] >= 'a' && str[i] <= 'z' || str[i] >= '0' && str[i] <= '9') {
            temp += str[i];
        } else if(str[i] == ',' || i == str.size()-1) {
            v.push_back(temp);
            temp.clear();
        }
    }
    return v;
}

void setOptions(vector<string>& args, unordered_map<string, bool>& options)
{
    for(int i = 0; i<args.size(); i++) {
        if(args[i][0] == '-' && options.count(args[i])) { // set the options that are listed in the initialization of options
            options[args[i]] = true;
            args.erase(args.begin()+i); // remove from args after initializing to true
            i--;
        } else if(args[i][0] == '-' && !options.count(args[i])) { // remove options in args that are not available
            args.erase(args.begin()+i);
            i--;
        }
    }
}

void showHelp(const string& program_name)
{
    cout << "FORMAT: " << endl;
    cout << program_name << " <OPTION> <SAMPLE_SIZE> '<ARRAY>'" << endl;
    cout << "EXAMPLE: " << endl;
    cout << program_name << " -p 2 '{1, 2, 3, 4}'" << endl;
    cout << program_name << " -p 3 '{apple, pear, strawberry, orange, banana}'" << endl;
    cout << "CONSTRAINTS: " << endl;
    cout << "0 <= SAMPLE_SIZE <= ARRAY.SIZE" << endl;
    cout << "OPTIONS: " << endl;
    cout << "-h, --help                             Show help menu" << endl;
    cout << "-p, --permutation                      Gives the permutation of the given array with the given sample size" << endl;
    cout << "-c, --combination                      Gives the combination of the given array with the given sample size" << endl;
}

int main(int argc, char* argv[])
{
    vector<string> args;
    unordered_map<string, bool> options = {{"-p", 0}, {"--permutation", 0}, {"-c", 0}, {"--combination", 0},
        {"-h", 0}, {"--help", 0}
    }; // list of available options

    args.assign(argv, argv+argc); // assign argv into args
    string program_name = getProgramName(args); // save program name into string

    if(args.size() <= 1) {
        missingArgs(program_name, "No arguments passed...", "Try: ");
        return 0;
    }

    setOptions(args, options); // set option flags
    if(options["-h"] || options["--help"]) {
        showHelp(program_name);
        return 0;
    }

    string s = getArray(args);
    vector<string> arr = parseArray(s);
    int r = getSampleSize(args);
    if(r > arr.size()) {
        missingArgs(program_name, "Sample size cannot be greater than array size...", "Check constraints with: ");
        return 0;
    }

    set<vector<string>> result;
    if(options["-p"] || options["--permutation"]) {
        result = permute(arr, r);
    } else if(options["-c"] || options["--combination"]) {
        result = combine(arr, r);
    } else {
        missingArgs(program_name, "No options passed...", "Try: ");
        return 0;
    }

    cout << "Formula: ";
    printFormula(options, arr.size(), r);
    printSet(result);

    return 0;
}