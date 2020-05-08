#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define N_ALPHA 26
#define INVALID "IMPOSSIBLE"

int number_of_cases;
int number_of_words;
string word;
vector<string> words;

vector<string> word_bank[N_ALPHA][N_ALPHA];
vector<vector<int> > adj;
vector<int> circuit;
vector<int> indegree, outdegree;

bool is_trail = false;
int start_node = 0;

void getGraph() {
    adj = vector<vector<int> >(N_ALPHA, vector<int>(N_ALPHA, 0));
    indegree = outdegree = vector<int>(N_ALPHA, 0);  // 방향 그래프에서 오일러 서킷의 존재 여부를 판단할 때 사용
    for (int i = 0; i < N_ALPHA; ++i) {
        for (int j = 0; j < N_ALPHA; ++j) {
            word_bank[i][j].clear();
        }
    }
    for (int i = 0; i < words.size(); ++i) {
        int from = words[i][0] - 'a';
        int to = words[i][words[i].length()-1] - 'a';
        word_bank[from][to].push_back(words[i]);
        adj[from][to]++;
        outdegree[from]++;
        indegree[to]++;
    }
}

bool isValid() {
    int delta, plusone = 0, minusone = 0;
    for (int i = 0; i < N_ALPHA; ++i) {
        delta = outdegree[i] - indegree[i];  // 각 노드의 순출차수
        if (delta < -1 || delta > 1) return false;  // -1, 0, 1 만 true
        else if (delta == 1) {
            start_node = i;
            plusone++;  // 순출차수 = 1 인 노드의 수
        }
        else if (delta == -1) minusone++;  // 순입차수 = 1 인 노드의 수
    }
    // 오일러 트레일이거나 오일러 서킷이거나
    if (plusone == 1 && minusone == 1) {
        is_trail = true;
        return true;
    }
    else if (plusone == 0 && minusone == 0) 
        return true;
    return false;
    // return (plusone == 1 && minusone == 1) || (plusone == 0 && minusone == 0);
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
    // isValid() 실행이 선행되어야 한다
    circuit.clear();
    if (is_trail) getEulerCircuit(start_node);
    else
        for (int i = 0; i < N_ALPHA; ++i) 
            if (outdegree[i]) {
                getEulerCircuit(i);
                break; // 한번만 실행해야 한다
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
        getGraph();
        if (!isValid()) {
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
            if (result.size()) result += " ";
            result += word_bank[circuit[k]][circuit[k+1]].back();
            word_bank[circuit[k]][circuit[k+1]].pop_back();
        }
        cout << result << endl;
    }
    return 0;
}