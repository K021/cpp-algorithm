#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define INVALID "IMPOSSIBLE"

int number_of_cases;
int number_of_words;

string word;
vector<string> words;

vector<vector<int> > adj;
vector<string> word_bank[26][26];
vector<int> indegree, outdegree;
vector<int> circuit;

bool is_trail = false;
int trail_start = 0;

void makeGraph() {
    adj = vector<vector<int> >(26, vector<int>(26, 0));
    indegree = outdegree = vector<int>(26, 0);
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            word_bank[i][j].clear();
        }
    }
    for (int k = 0; k < words.size(); ++k) {
        int from = words[k][0] - 'a';
        int to = words[k][words[k].length() - 1] - 'a';
        word_bank[from][to].push_back(words[k]);
        adj[from][to]++;
        outdegree[from]++;
        indegree[to]++;
    }
}

bool isValidDegree() {
    int delta, plusone, minusone;
    for (int i = 0; i < 26; ++i) {
        delta = outdegree[i] - indegree[i];
        if (delta < -1 || delta > 1) return false;
        else if (delta == 1) {
            plusone++;
            is_trail = true;
            trail_start = i;
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
    if (is_trail) getEulerCircuit(trail_start);
    else {
        for (int i = 0; i < 26; ++i) {
            if (outdegree[i]) {
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
        if (!isValidDegree()) {
            cout << INVALID << endl;
            continue;
        }
        getEulerCircuitOrTrail();
        if (circuit.size()-1 != words.size()) {
            cout << INVALID << endl;
            continue;
        }
        reverse(circuit.begin(), circuit.end());
        string result = "";
        for (int k = 0; k < circuit.size()-1; ++k) {
            if (result.length()) result += " ";
            result += word_bank[circuit[k]][circuit[k+1]].back();
            word_bank[circuit[k]][circuit[k+1]].pop_back();
        }
        cout << result << endl;
    }
}