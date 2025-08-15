#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>

using namespace std;

unordered_map<char, vector<char>> ntwrk;

string BFS(char node, char trgt) {
    queue<string> routeQueue;
    routeQueue.push(string(1, node));

    while (!routeQueue.empty()) {
        string currPath = routeQueue.front();
        routeQueue.pop();

        char lastStop = currPath.back();
        if (lastStop == trgt) {
            return currPath;
        }

        for (char nghbr : ntwrk[lastStop]) {
            if (currPath.find(nghbr) == string::npos) {
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

    string route = BFS(origin, dstn);

    if (!route.empty()) {
        cout << "Route located: " << route << "\n";
    } else {
        cout << "No route available.\n";
    }

    return 0;
}
