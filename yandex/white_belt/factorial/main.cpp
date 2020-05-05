#include <iostream>

using namespace std;

int Factorial(int number) {
    if (number <= 0) {
        return 1;
    }

    return number * Factorial(number - 1);
}

int main() {
    int number = 0;
    cin >> number;
    cout << Factorial(number) << endl;
    return 0;
}