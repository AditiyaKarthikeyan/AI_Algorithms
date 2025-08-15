#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

string branchBound(
    char node, char trgt,
    unordered_map<char, vector<pair<char,int>>> &ntwrk,
    unordered_map<char, int> &oraclecost
) {
    const int INF = INT_MAX / 4;
    if (!oraclecost.count(node) || oraclecost[node] == INF) return "";

    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<>> pq;
    pq.push({oraclecost[node], string(1, node)});

    int bestCost = INF;
    string bestPath;

    auto pathCost = [&](const string& r) {
        int g = 0;
        for (int i = 0; i + 1 < (int)r.size(); ++i) {
            char u = r[i], v = r[i+1];
            for (auto &e : ntwrk[u]) if (e.first == v) { g += e.second; break; }
        }
        return g;
    };

    while (!pq.empty()) {
        auto [f, route] = pq.top(); pq.pop();
        if (f >= bestCost) continue; 

        char u = route.back();
        int g = pathCost(route);

        if (u == trgt) {
            if (g < bestCost) {
                bestCost = g;
                bestPath = route;
            }
            continue;
        }

        for (auto &edge : ntwrk[u]) {
            char v = edge.first;
            int w = edge.second;

            if (route.find(v) != string::npos) continue;           
            if (!oraclecost.count(v) || oraclecost[v] == INF) continue;  

            int gNew = g + w;
            int fNew = gNew + oraclecost[v];
            if (fNew >= bestCost) continue;                      

            pq.push({fNew, route + v});
        }
    }

    return bestPath;
}

int main() {
    unordered_map<char, vector<pair<char,int>>> ntwrk = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 5}, {'B', 4}}},
        {'B', {{'A', 4}, {'C', 4}}},
        {'C', {{'E', 6}}},
        {'D', {{'G', 3}}},
        {'E', {}},
        {'G', {}}
    };

    const int INF = INT_MAX / 4;
    unordered_map<char, int> oraclecost = {
        {'S', 11},
        {'A', 8},
        {'B', 12},
        {'C', INF},
        {'D', 3},
        {'E', INF},
        {'G', 0}
    };

    char origin = 'S';
    char dstn   = 'G';

    string route = branchBound(origin, dstn, ntwrk, oraclecost);

    if (!route.empty()) {
        int cost = 0;
        for (int i = 0; i + 1 < (int)route.size(); ++i) {
            char u = route[i], v = route[i+1];
            for (auto &e : ntwrk[u]) if (e.first == v) { cost += e.second; break; }
        }
        cout << "Branch & Bound Route located: " << route << " | Cost = " << cost << "\n";
    } else {
        cout << "No route available.\n";
    }
    return 0;
}
