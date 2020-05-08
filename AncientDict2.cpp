#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string input;
int number_of_cases;
int number_of_words;
vector<string> words;

vector<vector<bool> > adj;
vector<int> closed_order;
vector<bool> visited;

void setGraph() {
    int n = words.size();
    string former, latter;
    int a, b;
    int compsize;

    adj = vector<vector<bool> >(26, vector<bool>(26, false));

    for (int i = 0; i < n-1; ++i) {
        former = words[i];
        latter = words[i+1];
        compsize = min(former.length(), latter.length());
        for (int j = 0; j < compsize; ++j) {
            if (former[j] != latter[j]) {
                a = former[j] - 'a';
                b = latter[j] - 'a';
                adj[a][b] = true;
                break;
            }
        }
    }
}

void dfs(int here) {
    visited[here] = true;
    for (int there = 0; there < adj[here].size(); ++there) {
        if (adj[here][there] && !visited[there])
            dfs(there);
    }
    closed_order.push_back(here);
}

void dfsAll() {
    visited = vector<bool>(26, false);
    closed_order.clear();
    for (int i = 0; i < adj.size(); ++i) {
        if (!visited[i])
            dfs(i);
    }
}

vector<int> topSort() {
    int n = closed_order.size();
    reverse(closed_order.begin(), closed_order.end());
    for (int i = 0; i < n-1; ++i) {
        int former = closed_order[i];
        int latter = closed_order[i+1];
        if (adj[latter][former])
            return vector<int>();
    }
    return closed_order;
}

int main() {
    cin >> input;
    number_of_cases = stoi(input);
    for (int i = 0; i < number_of_cases; ++i) {
        cin >> input;
        number_of_words = stoi(input);
        words.clear();
        for (int j = 0; j < number_of_words; ++j) {
            cin >> input;
            words.push_back(input);
        }
        setGraph();
        dfsAll();
        closed_order = topSort();
        if (closed_order.size())
            for (int i = 0; i < closed_order.size(); ++i) {
                cout << "abcdefghijklmnopqrstuvwxyz"[closed_order[i]];
            }
        else 
            cout << "INVALID HYPOTHESIS";
        cout << endl;
    }
    return 0;
}