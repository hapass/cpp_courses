#include <iostream>

using namespace std;

int main() {
    string input;

    cin >> input;

    int entryCount = 0;
    int index = 0;
    while (index < input.size()) {
        if (input[index] == 'f' && ++entryCount == 2) {
            break;
        }
        index++;
    }

    switch (entryCount)
    {
        case 0: cout << -2; break;
        case 1: cout << -1; break;
        case 2: cout << index; break;
        default: break;
    }

    cout << endl;

    return 0;
}