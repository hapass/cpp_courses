#include <iostream>

using namespace std;

int factorial(int number) {
    if (number <= 0) {
        return 1;
    }

    return number * factorial(number - 1);
}

int main() {
    int number = 0;
    cin >> number;
    cout << factorial(number) << endl;
    return 0;
}