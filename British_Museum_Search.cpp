#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<char, vector<char>> adjList;

void findallpaths(char node, char dstn, string visited, vector<string>& results) {
    visited.push_back(node);

    if (node == dstn) {
        results.push_back(visited);
        return;
    }

    for (char next : adjList[node]) {
        if (visited.find(next) == string::npos) {
            findallpaths(next, dstn, visited, results);
        }
    }
}

int main() {
    adjList['S'] = {'A', 'B'};
    adjList['A'] = {'D'};
    adjList['B'] = {'A', 'C'};
    adjList['C'] = {'E'};
    adjList['D'] = {'G'};
    adjList['E'] = {};
    adjList['G'] = {};

    char startnode = 'S';
    char goalnode = 'G';
    vector<string> allpaths;

    findallpaths(startnode, goalnode, "", allpaths);

    if (!allpaths.empty()) {
        cout << "Possible routes found:\n";
        for (const auto& route : allpaths) {
            cout << route << '\n';
        }
    } else {
        cout << "No route exists.\n";
    }

    return 0;
}
