#include <iostream>
#include <algorithm>
#include <locale>
#include <vector>

using namespace std;

int main() {
    int vectorSize = 0;
    cin >> vectorSize;

    vector<string> vec(vectorSize);
    for (auto& value : vec) {
        cin >> value;
    }

    sort(begin(vec), end(vec), [](string first, string second) {
        for (auto& ch : first) {
            ch = tolower(ch);
        }
        for (auto& ch : second) {
            ch = tolower(ch);
        }
        return first < second;
    });

    for (const auto& value : vec) {
        cout << value << ' ';
    }
    cout << endl;
    return 0;
}