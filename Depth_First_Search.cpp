#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

unordered_map<char, vector<char>> ntwrk;

string depthSearch(char node, char trgt) {
    if (node == trgt) {
        return {node}; 
    }

    for (char link : ntwrk[node]) {
        string subroute = depthSearch(link, trgt);
        if (!subroute.empty()) {
            return string(1, node) + subroute;
        }
    }
    return "";
}

int main() {
    ntwrk['S'] = {'A', 'B'};
    ntwrk['A'] = {'D'};
    ntwrk['B'] = {'A', 'C'};
    ntwrk['C'] = {'E'};
    ntwrk['D'] = {'G'};
    ntwrk['E'] = {};
    ntwrk['G'] = {};

    char origin = 'S';
    char dstn = 'G';

    string route = depthSearch(origin, dstn);

    if (!route.empty()) {
        cout << "Route located: " << route << "\n";
    } else {
        cout << "No route available.\n";
    }

    return 0;
}
