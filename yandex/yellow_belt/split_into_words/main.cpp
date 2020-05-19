#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto it = begin(s);
    while (true) {
        auto space_it = find(it, end(s), ' ');
        result.push_back({it, space_it});

        if (space_it == end(s)) break;
        it = ++space_it;
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
