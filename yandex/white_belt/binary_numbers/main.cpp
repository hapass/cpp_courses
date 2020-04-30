#include <iostream>
#include <vector>

using namespace std;

void print_binary(int number) {
    if (number == 0) return;
    print_binary(number / 2);
    cout << number % 2;
}

int main() {
    int a = 0;
    cin >> a;
    if (a == 0) {
        cout << 0;
    } else {
        print_binary(a);
    }
    cout << endl;
    return 0;
}