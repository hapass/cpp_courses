#include <iostream>
#include <cmath>
using namespace std;

bool isEqual(double value, double other) {
    return abs(value - other) < 0.00001;
}

int main() {
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;

    cin >> a >> b >> c;

    if (isEqual(a, 0)) {
        if (isEqual(b, 0)) {
            if (isEqual(c, 0)) {
                cout << endl;
            }
            else {
                cout << endl;
            }
            return 0;
        }
        else {
            cout << -c / b << endl;
            return 0;
        }
    }

    double d = b * b - 4 * a * c;

    if (d < 0)
    {
        cout << endl;
        return 0;
    }

    if (isEqual(d, 0))
    {
        cout << -b / (2 * a) << endl;
        return 0;
    }

    cout << (-b - sqrt(d)) / (2 * a) << " " << (-b + sqrt(d)) / (2 * a) << endl;
    return 0;
}