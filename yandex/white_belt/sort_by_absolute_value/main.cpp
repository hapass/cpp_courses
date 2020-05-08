#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int vectorSize = 0;
    cin >> vectorSize;

    vector<int> vec(vectorSize);
    for (auto& value : vec) {
        cin >> value;
    }

    sort(begin(vec), end(vec), [](int first, int second){return abs(first) < abs(second);});

    for (auto value : vec) {
        cout << value << ' ';
    }
    cout << endl;
    return 0;
}