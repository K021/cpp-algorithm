#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s;

    cin >> s;
    cout << "Hello, World!" << s << endl;

    s = "abcdefg";
    string::reverse_iterator riter;
    for (riter = s.rbegin(); riter != s.rend(); ++riter) {
        cout << *riter << ", ";
    }
    cout << endl;

    vector<int> v;
    for (int i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    v.pop_back();
    cout << v.size() << endl;

    return 0;
}