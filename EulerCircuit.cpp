#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/*
    adj: 
        \    0  1  2  3  4

        0    0  0  1  0  1
        1    0  0  0  1  1
        2    1  0  0  1  2
        3    0  1  1  0  0
        4    1  1  2  0  0
    result: 
        02314240
*/
vector<vector<int> > adj({
    vector<int>{0, 0, 1, 0, 1},
    vector<int>{0, 0, 0, 1, 1},
    vector<int>{1, 0, 0, 1, 2},
    vector<int>{0, 1, 1, 0, 0},
    vector<int>{1, 1, 2, 0, 0},
});
vector<int> circuit;

void getEulerCircuit(int here) {
    for (int there = 0; there < adj[here].size(); ++there) {
        while (adj[here][there]) {
            adj[here][there]--;
            adj[there][here]--;
            getEulerCircuit(there);
        }
    }
    circuit.push_back(here);
}

int main() {
    getEulerCircuit(0);
    reverse(circuit.begin(), circuit.end());
    cout << "hello" << endl;
    for (int i = 0; i < circuit.size(); ++i) {
        cout << circuit[i];
    }

    return 0;
}