#include <iostream>
#include <string>

using namespace std;

bool IsPalindrom(string value) {
    if (value.length() <= 1) {
        return true;
    }

    return value[0] == value[value.length() - 1] && IsPalindrom(value.substr(1, value.length() - 2));
}

int main() {
    string value;
    cin >> value;
    cout << boolalpha << IsPalindrom(value) << endl;
    return 0;
}