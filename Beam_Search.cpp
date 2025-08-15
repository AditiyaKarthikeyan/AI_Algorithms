#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string beamsearch(
    char node, char trgt, int width,
    unordered_map<char, vector<char>> &ntwrk,
    int depthLimit = 10
) {
    vector<string> currBeam = { string(1, node) };
    int depth = 0;

    while (!currBeam.empty() && depth < depthLimit) {
        vector<string> prospects;

        for (const string &rt : currBeam) {
            char last = rt.back();
            if (last == trgt) return rt;

            for (char nxt : ntwrk[last]) {
                prospects.push_back(rt + nxt);
            }
        }

        if (prospects.empty()) break;

        sort(prospects.begin(), prospects.end());
        currBeam.assign(
            prospects.begin(),
            prospects.begin() + min(width, (int)prospects.size())
        );

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

    string route = beamsearch(origin, dstn, beamWidth, ntwrk);

    if (!route.empty())
        cout << "Beam Search Route located: " << route << "\n";
    else
        cout << "No route available.\n";
}
