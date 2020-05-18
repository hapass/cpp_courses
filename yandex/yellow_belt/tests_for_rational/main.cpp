#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

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

void TestDefaultCtor() {
  Rational r;
  AssertEqual(r.Numerator(), 0, "Numerator is 0 for default rational");
  AssertEqual(r.Denominator(), 1, "Denominator is 1 for default rational");
}

void TestRationalIsReduced() {
  {
    Rational r(8, 16);
    AssertEqual(r.Numerator(), 1, "Numerator is 1 for 8/16");
    AssertEqual(r.Denominator(), 2, "Denominator is 2 for 8/16");
  }

  {
    Rational r(300, 400);
    AssertEqual(r.Numerator(), 3, "Numerator is 3 for 300/400");
    AssertEqual(r.Denominator(), 4, "Denominator is 4 for 300/400");
  }

  {
    Rational r(50, 20);
    AssertEqual(r.Numerator(), 5, "Numerator is 5 for 50/20");
    AssertEqual(r.Denominator(), 2, "Denominator is 2 for 50/20");
  }
}

void TestNegativeRational() {
  {
    Rational r(-8, 16);
    AssertEqual(r.Numerator(), -1, "Numerator is -1 for -8/16");
    AssertEqual(r.Denominator(), 2, "Denominator is 2 for -8/16");
  }

  {
    Rational r(-8, -16);
    AssertEqual(r.Numerator(), 1, "Numerator is 1 for -8/-16");
    AssertEqual(r.Denominator(), 2, "Denominator is 2 for -8/-16");
  }

  {
    Rational r(8, -16);
    AssertEqual(r.Numerator(), -1, "Numerator is -1 for 8/-16");
    AssertEqual(r.Denominator(), 2, "Denominator is 2 for 8/-16");
  }
}

void TestZero() {
  {
    Rational r(0, 16);
    AssertEqual(r.Numerator(), 0, "Numerator is 0 for 0/16");
    AssertEqual(r.Denominator(), 1, "Denominator is 1 for 0/16");
  }

  {
    Rational r(0, -16);
    AssertEqual(r.Numerator(), 0, "Numerator is 0 for 0/-16");
    AssertEqual(r.Denominator(), 1, "Denominator is 1 for 0/-16");
  }
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDefaultCtor, "TestDefaultCtor");
  runner.RunTest(TestRationalIsReduced, "TestRationalIsReduced");
  runner.RunTest(TestNegativeRational, "TestNegativeRational");
  runner.RunTest(TestZero, "TestZero");
  return 0;
}
