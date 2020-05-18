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

int GetDistinctRealRootCount(double a, double b, double c) {
    return 0;
}

void TestDiscriminantZero() {
    int roots_count = GetDistinctRealRootCount(1, 2, 1);
    AssertEqual(roots_count, 1, "a: 1, b: 2, c: 1");
}

void TestDiscriminantNegative() {
    int roots_count = GetDistinctRealRootCount(2, 2, 2);
    AssertEqual(roots_count, 0, "a: 2, b: 2, c: 2");
}

void TestNormalDiscriminant() {
    int roots_count = GetDistinctRealRootCount(1, 10, 1);
    AssertEqual(roots_count, 2, "a: 1, b: 10, c: 1");
}

void TestLinearEquation() {
    int roots_count = GetDistinctRealRootCount(0, 1, 4);
    AssertEqual(roots_count, 1, "a: 0, b: 1, c: 4");
}

void TestSimpleSquare() {
    int roots_count = GetDistinctRealRootCount(1, 0, -4);
    AssertEqual(roots_count, 2, "a: 1, b: 0, c: -4");
}

void TestNegativeQuotients() {
    int roots_count = GetDistinctRealRootCount(-1, -2, -1);
    AssertEqual(roots_count, 1, "a: -1, b: -2, c: -1");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestDiscriminantZero, "TestDiscriminantZero");
  runner.RunTest(TestDiscriminantNegative, "TestDiscriminantNegative");
  runner.RunTest(TestNormalDiscriminant, "TestNormalDiscriminant");
  runner.RunTest(TestLinearEquation, "TestLinearEquation");
  runner.RunTest(TestSimpleSquare, "TestSimpleSquare");
  runner.RunTest(TestNegativeQuotients, "TestNegativeQuotients");
  return 0;
}