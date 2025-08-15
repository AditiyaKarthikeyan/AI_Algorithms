#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <set>

using namespace std;

unordered_map<char, vector<char>> ntwrk;

string BFSHist(char node, char trgt) {
    queue<string> routeQueue;
    set<char> visited;

    routeQueue.push(string(1, node));
    visited.insert(node);

    while (!routeQueue.empty()) {
        string currPath = routeQueue.front();
        routeQueue.pop();

        char lastnode = currPath.back();

        if (lastnode == trgt) {
            return currPath;
        }

        for (char nghbr : ntwrk[lastnode]) {
            if (!visited.count(nghbr)) {
                visited.insert(nghbr);
                routeQueue.push(currPath + nghbr);
            }
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

    string shortestPath = BFSHist(origin, dstn);

    if (!shortestPath.empty()) {
        cout << "Shortest path: " << shortestPath << "\n";
    } else {
        cout << "No route available.\n";
    }

    return 0;
}

