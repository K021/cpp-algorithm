#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <algorithm>

using namespace std;

vector<vector<bool> > adj_default(26, vector<bool>(26, false));
vector<vector<bool> > adj;
vector<bool> visited;
vector<int> closed_order;
vector<int>::reverse_iterator riter;
vector<string> words;

string alphabets = "abcdefghijklmnopqrstuvwxyz";
vector<bool> flag(26, true);

bool is_invalid = false;

void compare(string w1, string w2, int& from, int& to) {
    int len = min(w1.length(), w2.length());
    for (int i = 0; i < len; ++i) {
        if (w1[i] == w2[i]) continue;
        from = w1[i] - 'a';
        to = w2[i] - 'a';
        return;
    }
}

void dfs(int here) {
    visited[here] = true;
    for (int i = 0; i < adj.size(); ++i) {
        if (adj[here][i] && !visited[i]) 
            dfs(i);
    }
    closed_order.push_back(here);
}

void dfsAll() {
    visited = vector<bool>(adj.size(), false);
    closed_order.clear();
    for (int i = 0; i < adj.size(); ++i) {
        if (!visited[i])
            dfs(i);
    }
}

bool topSort() {
    // Topological Sort
    int m = closed_order.size();
    reverse(closed_order.begin(), closed_order.end());
    // 역방향 간선 있으면 
    for (int former = 0; former < m-1; ++former) {
        for (int latter = former+1; latter < m; ++latter) {
            if (adj[closed_order[latter]][closed_order[former]]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    time_t start_time, end_time;
    int ncases;
    int nwords;
    int former, latter;
    string input;
    string word;

    start_time = clock();
    
    cin >> input;
    ncases = stoi(input);
    for (int i = 0; i < ncases; ++i) {
        is_invalid = false;
        words.clear();
        adj.clear();
        adj.assign(adj_default.begin(), adj_default.end());

        cin >> input;
        nwords = stoi(input);
        // cout << "==case#" << i << "==" << endl;
        for (int j = 0; j < nwords; ++j) {
            cin >> word;
            words.push_back(word);
            // cout << "word: " << static_cast<int>(word[0])-97 << endl;
        }
        if (words.size() < 2) cout << "abcdefghijklmnopqrstuvwxyz" << endl;
        for (int fo = 0; fo < words.size()-1; ++fo) {
            int la = fo + 1;
            compare(words[fo], words[la], former, latter);
            // if (adj[latter][former]) {
            //         is_invalid = true;
            //         break;
            // }
            adj[former][latter] = true;
        }

        dfsAll();

        if (topSort()) {
            for (int idx = 0; idx < 26; ++idx) {
                cout << alphabets[closed_order[idx]];
            }
            cout << endl;
        }
        else cout << "INVALID HYPOTHESIS" << endl; 

        // if (is_invalid) {
        //     cout << "INVALID HYPOTHESIS" << endl; 
        // }
        // else {
        //     dfsAll();
        //     reverse(closed_order.begin(), closed_order.end());
        //     for (int idx = 0; idx < 26; ++idx) {
        //         cout << alphabets[closed_order[idx]];
        //     }
        //     // for (riter = closed_order.rbegin(); riter != closed_order.rend(); ++riter) {
        //     //     cout << alphabets[*riter];
        //     //     flag[*riter] = false;
        //     // }
        //     // cout << ":";
        //     // for (int idx = 0; idx < 26; ++idx) {
        //     //     if (flag[i]) cout << alphabets[i];
        //     // }
        //     cout << endl;
        // }

        // cout << endl << words.size() << endl;
    }

    // end_time = clock();
    // cout << "Elapsed Time: " << (double)(end_time - start_time) / 1000 << " s"<< endl;
    return 0;
}
