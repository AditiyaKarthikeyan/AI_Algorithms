#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

string beamHist(
    char node, char trgt, int width,
    unordered_map<char, vector<char>> &ntwrk,
    int depthLimit = 10
) {
    vector<pair<string, unordered_set<char>>> currBeam;
    currBeam.push_back({ string(1, node), { node } });
    int depth = 0;

    while (!currBeam.empty() && depth < depthLimit) {
        vector<pair<string, unordered_set<char>>> prospects;

        for (auto &state : currBeam) {
            string rt = state.first;
            auto visited = state.second;
            char last = rt.back();

            if (last == trgt) return rt;

            for (char nxt : ntwrk[last]) {
                if (!visited.count(nxt)) {
                    auto newVisited = visited;
                    newVisited.insert(nxt);
                    prospects.push_back({ rt + nxt, newVisited });
                }
            }
        }

        if (prospects.empty()) break;

        sort(prospects.begin(), prospects.end(),
            [](auto &a, auto &b) { return a.first < b.first; });

        if ((int)prospects.size() > width)
            prospects.resize(width);

        currBeam = prospects;
        depth++;
    }

    return "";
}

int main() {
    unordered_map<char, vector<char>> ntwrk = {
        {'S', {'A', 'B'}},
        {'A', {'D'}},
        {'B', {'A', 'C'}},
        {'C', {'E'}},
        {'D', {'G'}},
        {'E', {}},
        {'G', {}}
    };

    char origin = 'S';
    char dstn = 'G';
    int beamWidth = 2;

    string route = beamHist(origin, dstn, beamWidth, ntwrk);

    if (!route.empty())
        cout << "Beam Search Route located: " << route << "\n";
    else
        cout << "No route available.\n";
}
