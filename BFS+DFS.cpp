#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

unordered_map<char, vector<char>> ntwrk;

bool DFS(char node, char dstn, unordered_set<char>& visited, string& path) {
    visited.insert(node);
    path.push_back(node);

    if (node == dstn) {
        return true;
    }

    for (char nghbr : ntwrk[node]) {
        if (!visited.count(nghbr)) {
            if (DFS(nghbr, dstn, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back(); 
    return false;
}

string hybridSearch(char start, char dstn) {
    queue<string> routes;
    unordered_set<char> visited;

    routes.push(string(1, start));
    visited.insert(start);

    while (!routes.empty()) {
        string currentroute = routes.front();
        routes.pop();
        char laststop = currentroute.back();

        if (laststop == dstn) {
            return currentroute;
        }

        vector<char> availnxtStops;
        for (char nghbr : ntwrk[laststop]) {
            if (!visited.count(nghbr)) {
                availnxtStops.push_back(nghbr);
            }
        }

        if (availnxtStops.size() >= 2) {
            for (char next : availnxtStops) {
                string temproute = currentroute;
                unordered_set<char> tempvisited = visited;
                tempvisited.insert(next);
                if (DFS(next, dstn, tempvisited, temproute)) {
                    return temproute;
                }
            }
        } else {
            for (char next : availnxtStops) {
                visited.insert(next);
                routes.push(currentroute + next);
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

    string route = hybridSearch(origin, dstn);

    if (!route.empty()) {
        cout << "Route located: " << route << "\n";
    } else {
        cout << "No route available.\n";
    }

    return 0;
}
