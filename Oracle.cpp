#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

string oracle(
    char node, char trgt,
    unordered_map<char, vector<pair<char, int>>> &ntwrk,
    unordered_map<char, int> &hval
) {
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<>
    > pq;

    pq.push({hval[node], string(1, node)});

    while (!pq.empty()) {
        auto [f, route] = pq.top();
        pq.pop();

        char last = route.back();
        if (last == trgt) return route;

        int gCost = 0;
        for (int i = 0; i + 1 < route.size(); i++) {
            char u = route[i], v = route[i + 1];
            for (auto &edge : ntwrk[u]) {
                if (edge.first == v) {
                    gCost += edge.second;
                    break;
                }
            }
        }

        for (auto &nghbr : ntwrk[last]) {
            char nxt = nghbr.first;
            int edgeCost = nghbr.second;

            if (route.find(nxt) != string::npos) continue; 

            int gNew = gCost + edgeCost;
            int fNew = gNew + hval[nxt];

            pq.push({fNew, route + nxt});
        }
    }
    return "";
}

int main() {
    unordered_map<char, vector<pair<char, int>>> ntwrk = {
        {'S', {{'A', 3}, {'B', 5}}},
        {'A', {{'D', 5}, {'B', 4}}},
        {'B', {{'A', 4}, {'C', 4}}},
        {'C', {{'E', 6}}},
        {'D', {{'G', 3}}},
        {'E', {}},
        {'G', {}}
    };

    unordered_map<char, int> hval = {
        {'S', 11},
        {'A', 8},
        {'B', 12},
        {'C', INT_MAX},
        {'D', 3},
        {'E', INT_MAX},
        {'G', 0}
    };

    char origin = 'S';
    char dstn = 'G';

    string route = oracle(origin, dstn, ntwrk, hval);

    if (!route.empty())
        cout << "Route located: " << route << "\n";
    else
        cout << "No route available.\n";
}
