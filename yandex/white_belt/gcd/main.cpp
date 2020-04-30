#include <iostream>

using namespace std;

int gcd(int one, int other) {
    if (one == 0) {
        return other;
    }

    if (other < one) {
        return gcd(other, one);
    }

    return gcd(one, other % one);
}

int main() {
    int one = 0;
    int other = 0;
    cin >> one >> other;
    cout << gcd(one, other) << endl;
    return 0;
}