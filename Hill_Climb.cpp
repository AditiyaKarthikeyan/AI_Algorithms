#include <iostream>
#include <unordered_map>
#include <vector>
#include <climits>
#include <string>

using namespace std;

string hillClimb(
    char node, char trgt,
    unordered_map<char, vector<pair<char, int>>> &ntwrk,
    unordered_map<char, int> &hval
) {
    string route;
    char curr = node;
    route.push_back(curr);

    while (curr != trgt) {
        auto &links = ntwrk[curr];
        if (links.empty()) break;

        char bestNext = 0;
        int bestScore = INT_MAX;

        for (auto &link : links) {
            char nghbr = link.first;
            if (hval[nghbr] < bestScore) {
                bestScore = hval[nghbr];
                bestNext = nghbr;
            }
        }

        if (bestScore >= hval[curr]) break;

        curr = bestNext;
        route.push_back(curr); 
    }

    if (curr == trgt) return route;
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
        {'S', 8},
        {'A', 7},
        {'B', 6},
        {'C', 7},
        {'D', 3},
        {'E', 4},
        {'G', 0}
    };

    char origin = 'S';
    char dstn = 'G';

    string route = hillClimb(origin, dstn, ntwrk, hval);

    if (!route.empty())
        cout << "Route located: " << route << "\n";
    else
        cout << "No route available.\n";
}
