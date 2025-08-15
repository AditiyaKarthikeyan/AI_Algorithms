#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <utility>

using namespace std;

const int INF = INT_MAX / 4;

string BrBoExt(
    char node, char trgt,
    unordered_map<char, vector<pair<char,int>>> &ntwrk,
    unordered_map<char,int> &oraclecost
) {
    if (!oraclecost.count(node) || oraclecost[node] == INF) return "";

    int bestCost = INF;
    string bestRoute;

    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<>> pq;
    pq.push({ oraclecost[node], string(1, node) });

    unordered_map<char,int> bestG;
    bestG[node] = 0;

    auto calcG = [&](const string &route) {
        int cost = 0;
        for (size_t i = 0; i + 1 < route.size(); ++i) {
            char u = route[i], v = route[i+1];
            for (auto &e : ntwrk[u]) {
                if (e.first == v) { cost += e.second; break; }
            }
        }
        return cost;
    };

    while (!pq.empty()) {
        auto [f, route] = pq.top(); pq.pop();
        if (f >= bestCost) continue;

        char u = route.back();
        int g = calcG(route);

        if (bestG.count(u) && g > bestG[u]) continue;

        if (u == trgt) {
            if (g < bestCost) {
                bestCost = g;
                bestRoute = route;
            }
            continue;
        }

        for (auto &[nbr, w] : ntwrk[u]) {
            if (route.find(nbr) != string::npos) continue;

            if (!oraclecost.count(nbr) || oraclecost[nbr] == INF) continue;

            int gNew = g + w;
            if (bestG.count(nbr) && gNew >= bestG[nbr]) continue;

            int fNew = gNew + oraclecost[nbr];
            if (fNew >= bestCost) continue;

            bestG[nbr] = gNew;
            pq.push({ fNew, route + nbr });
        }
    }

    return bestRoute;
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

    unordered_map<char,int> oraclecost = {
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
    string route = BrBoExt(origin, dstn, ntwrk, oraclecost);

    if (!route.empty()) {
        int totalCost = 0;
        for (size_t i = 0; i + 1 < route.size(); ++i) {
            char u = route[i], v = route[i+1];
            for (auto &e : ntwrk[u]) if (e.first == v) { totalCost += e.second; break; }
        }
        cout << "Branch & Bound (Extended) Route located: " << route << " | Cost = " << totalCost << "\n";
    } else {
        cout << "No route available.\n";
    }

    return 0;
}
