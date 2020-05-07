#include <iostream>
#include <set>

using namespace std;

int main() {
    int stringCount = 0;
    cin >> stringCount;

    set<string> stringSet;
    while (--stringCount >= 0)
    {
        string value;
        cin >> value;
        stringSet.insert(value);
    }

    cout << stringSet.size() << endl;
    return 0;
}