#include <iostream>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(string word) {
    map<char, int> chars;
    for (char ch : word) {
        ++chars[ch];
    }
    return chars;
}

int main() {
    int pairCount = 0;
    cin >> pairCount;

    while (pairCount > 0)
    {
        string first, second;
        cin >> first >> second;
        if (BuildCharCounters(first) == BuildCharCounters(second)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        pairCount--;
    }

    return 0;
}