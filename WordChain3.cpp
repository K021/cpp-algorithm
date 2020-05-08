#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define INVALID "IMPOSSIBLE"
#define RANGE 26

int number_of_cases;
int number_of_words;
string word;
vector<string> words;

vector<vector<int> > adj;
vector<string> word_bank[RANGE][RANGE];
vector<int> indeg, outdeg;

bool is_trail = false;
int trail_start_node;

vector<int> circuit;

void makeGraph() {
    adj = vector<vector<int> >(RANGE, vector<int>(RANGE, 0));
    indeg = outdeg = vector<int>(RANGE, 0);
    for (int i = 0; i < RANGE; ++i) {
        for (int j = 0; j < RANGE; ++j) {
            word_bank[i][j].clear();
        }
    }
    for (int k = 0; k < words.size(); ++k) {
        int from = words[k][0] - 'a';
        int to = words[k][words[k].length() - 1] - 'a';
        word_bank[from][to].push_back(words[k]);
        adj[from][to]++;
        outdeg[from]++;
        indeg[to]++;
    }
}

bool isValidDeg() {
    int delta, plusone, minusone;
    for (int i = 0; i < RANGE; ++i) {
        delta = outdeg[i] - indeg[i];
        if (delta < -1 || delta > 1) return false;
        else if (delta == 1) {
            plusone++;
            is_trail = true;
            trail_start_node = i;
        }
        else if (delta == -1) minusone++;
    }
    return (plusone == 1 && minusone == 1) || (plusone == 0 && minusone == 0);
}

void getEulerCircuit(int here) {
    for (int there = 0; there < adj[here].size(); ++there) {
        while (adj[here][there]) {
            adj[here][there]--;
            getEulerCircuit(there);
        }
    }
    circuit.push_back(here);
}

void getEulerCircuitOrTrail() {
    circuit.clear();
    if (is_trail) getEulerCircuit(trail_start_node);
    else {
        for (int i = 0; i < RANGE; ++i) {
            if (outdeg[i]) {
                getEulerCircuit(i);
                return;
            }
        }
    }
}

int main() {
    cin >> number_of_cases;
    for (int i = 0; i < number_of_cases; ++i) {
        cin >> number_of_words;
        words.clear();
        for (int j = 0; j < number_of_words; ++j) {
            cin >> word;
            words.push_back(word);
        }
        makeGraph();
        if (!isValidDeg()) {
            cout << INVALID << endl;
            continue;
        }
        getEulerCircuitOrTrail();
        if (circuit.size() - 1 != words.size()) {
            cout << INVALID << endl;
            continue;
        }
        reverse(circuit.begin(), circuit.end());
        string result = "";
        for (int k = 0; k < circuit.size()-1; ++k) {
            if (result.size()) result += " ";
            result += word_bank[circuit[k]][circuit[k+1]].back();
            word_bank[circuit[k]][circuit[k+1]].pop_back();
        }
        cout << result << endl;
    }
    return 0;
}