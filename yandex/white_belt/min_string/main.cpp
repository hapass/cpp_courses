#include <iostream>
#include <string>
using namespace std;

int main() {
    string min;
    string b;
    string c;

    cin >> min >> b >> c;

    if (b < min) {
        min = b;
    }

    if (c < min) {
        min = c;
    }

    cout << min << std::endl;
    return 0;
}