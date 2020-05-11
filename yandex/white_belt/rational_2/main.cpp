#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

int Sign(int numerator, int denominator) {
    if (numerator < 0 && denominator > 0) return -1;
    if (numerator > 0 && denominator < 0) return -1;
    return 1;
}

int Gcd(int lhs, int rhs) {
    if (lhs == 0) return rhs;
    if (rhs < lhs) return Gcd(rhs, lhs);
    return Gcd(lhs, rhs % lhs);
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
    int numerator = 0;
    int denominator = 1;
    int sign = 1;
};

bool operator==(const Rational& lhs, const Rational& rhs) {
    return lhs.Denominator() == rhs.Denominator() && 
        lhs.Numerator() == rhs.Numerator();
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    return {
        rhs.Denominator() * lhs.Numerator() + lhs.Denominator() * rhs.Numerator(),
        lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator-(const Rational& number) {
    return { -number.Numerator(), number.Denominator() };
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    return lhs + (-rhs);
}

int main() {
    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            cout << c.Numerator() << endl;
            cout << c.Denominator() << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
