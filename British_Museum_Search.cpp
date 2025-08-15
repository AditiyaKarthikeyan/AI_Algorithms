#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<char, vector<char>> ntwrk;

void findallpaths(char node, char trgt, string visited, vector<string>& results) {
    visited.push_back(node);

    if (node == trgt) {
        results.push_back(visited);
        return;
    }

    for (char next : ntwrk[node]) {
        if (visited.find(next) == string::npos) {
            findallpaths(next, trgt, visited, results);
        }
    }
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
    vector<string> allpaths;

    findallpaths(origin, dstn, "", allpaths);

    if (!allpaths.empty()) {
        cout << "Possible routes found:\n";
        for (const auto& route : allpaths) {
            cout << route << '\n';
        }
    } else {
        cout << "No route available.\n";
    }

    return 0;
}

