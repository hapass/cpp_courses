#include <iostream>

using namespace std;

void UpdateIfGreater(int first, int& second) {
    if (first > second) {
        second = first;
    }
}

int main() {
    int a = 0;
    int b = 0;
    cin >> a >> b;
    UpdateIfGreater(a, b);
    cout << a << ' ' << b << endl;
    return 0;
}