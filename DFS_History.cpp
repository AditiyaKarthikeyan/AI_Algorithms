#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

unordered_map<char, vector<char>> ntwrk;

bool DFS_Hist(char node, char trgt, unordered_set<char>& visited, string& path) {
    visited.insert(node);
    path.push_back(node);

    if (node == trgt) {
        return true;
    }

    for (char nextStop : ntwrk[node]) {
        if (!visited.count(nextStop)) {
            if (DFS_Hist(nextStop, trgt, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}

string findDFS(char start, char destination) {
    unordered_set<char> visited;
    string path;
    if (DFS_Hist(start, destination, visited, path)) {
        return path;
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

    string route = findDFS(origin, dstn);

    if (!route.empty()) {
        cout << "Route located: " << route << "\n";
    } else {
        cout << "No route available.\n";
    }

    return 0;
}
