#include <iostream>
#include <cassert>
#include <cmath>
#include <sstream>
#include <map>
#include <set>
#include <vector>

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

Rational operator*(const Rational& lhs, const Rational& rhs) {
    return { lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator() };
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
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
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}
