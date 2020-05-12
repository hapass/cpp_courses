#include <iostream>
#include <cmath>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <exception>

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
        if (d == 0) {
            throw invalid_argument("Denominator can't be zero.");
        }
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

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("Denominator can't be zero.");
    }
    return { lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator() };
}

ostream& operator<<(ostream& stream, const Rational& number) {
    stream << number.Numerator() << "/" << number.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& number) {
    int numerator, denominator;
    if (stream >> numerator && stream.ignore(1) && stream >> denominator) {
        number = { numerator, denominator };
    }
    return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return rhs.Denominator() * lhs.Numerator() < lhs.Denominator() * rhs.Numerator();
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}