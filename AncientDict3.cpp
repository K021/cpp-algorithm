#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

#define ALPHABETS 26

string input;
string word;
int number_of_cases;
int number_of_words;
vector<string> words;

vector<vector<bool> > adj;
vector<bool> visited;
vector<int> closed_order;

void setGraph() {
    int n = words.size();
    int min_size, a, b;
    string former, latter;
    adj = vector<vector<bool> >(ALPHABETS, vector<bool>(ALPHABETS, false));
    for (int i = 0; i < n-1; ++i) {
        former = words[i];
        latter = words[i+1];
        min_size = min(former.size(), latter.size());
        for (int j = 0; j < min_size; ++j) {
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
    visited = vector<bool>(ALPHABETS, false);
    closed_order.clear();
    for (int i = 0; i < adj.size(); ++i) {
        if (!visited[i]) 
            dfs(i);
    }
}

vector<int> topSort() {
    int n = closed_order.size();
    int a, b;
    reverse(closed_order.begin(), closed_order.end());
    for (int i = 0; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            a = closed_order[i];
            b = closed_order[j];
            if (adj[b][a])
                return vector<int>();
        }
    }
    return closed_order;
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
        setGraph();
        dfsAll();
        closed_order = topSort();
        if (closed_order.size()) {
            for (int i = 0; i < closed_order.size(); ++i) 
                cout << "abcdefghijklmnopqrstuvwxyz"[closed_order[i]];
        } else {
            cout << "INVALID HYPOTHESIS";
        }
        cout << endl;
    }
    return 0;
}