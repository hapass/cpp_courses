#include <iostream>

using namespace std;

int main() {
    int a = 1;
    int b = 30000;

    cin >> a >> b;

    for (int i = a; i <= b; i++) {
        if (i % 2 == 0) {
            cout << i << ' ';
        }
    }

    cout << endl;

    return 0;
}