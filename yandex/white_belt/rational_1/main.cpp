#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

int Sign(int numerator, int denominator) {
    if (numerator < 0 && denominator > 0) return -1;
    if (numerator > 0 && denominator < 0) return -1;
    return 1;
}

class Rational {
public:
    Rational() {}
    Rational(int n, int d) {
        assert(d != 0);
        sign = Sign(n, d);
        numerator = abs(n);
        denominator = abs(d);
        int gcd = Gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    int Numerator() const {
        return sign * numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int Gcd(int lhs, int rhs) {
        if (lhs == 0) return rhs;
        if (rhs < lhs) return Gcd(rhs, lhs);
        return Gcd(lhs, rhs % lhs);
    }

    int numerator = 0;
    int denominator = 1;
    int sign = 1;
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}