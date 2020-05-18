#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

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

bool IsPalindrom(const string& s) {
    if (s.length() <= 1) return true;
    return s[0] == s[s.length() - 1] && IsPalindrom(s.substr(1, s.length() - 2));
}

void TestAllSymbolsPalindrome() {
  ostringstream oss;
  vector<char> ascii;

  for (int i = 32; i <= 126; i++) ascii.push_back(static_cast<char>(i));

  std::random_device rd;
  std::mt19937 g(rd());
  for (int i = 0; i < 20; i++) {
    shuffle(ascii.begin(), ascii.end(), g);

    oss.str("");
    int size = static_cast<int>(ascii.size());
    for (int j = 0; j < size; j++) oss << ascii[j];
    for (int j = size - 1; j >= 0; j--) oss << ascii[j];

    Assert(IsPalindrom(oss.str()), "all character palindrome");
  }
}

void TestSpacePalindrome() {
  Assert(IsPalindrom(" "), "space is a palindrome");
  Assert(IsPalindrom("a a"), "space is a palindrome");
  Assert(IsPalindrom(" a b a "), "space is a palindrome");
}

void TestEmptyStringPalindrome() {
  Assert(IsPalindrom(""), "empty string is palindrome");
}

void TestSingleCharacterPalindrome() {
  Assert(IsPalindrom("a"), "single character is palindrome");
}

void TestSimpleOddCharacterNumberPalindrome() {
  Assert(IsPalindrom("aba"), "odd character palindrome");
}

void TestSimpleEvenCharacterNumberPalindrome() {
  Assert(IsPalindrom("abba"), "even character palindrome");
}

void TestAllCharactersAreComparedInPalindrome() {
  Assert(!IsPalindrom("zdabtbadx"), "0");
  Assert(!IsPalindrom("xfabtbadx"), "1");
  Assert(!IsPalindrom("xdrbtbadx"), "2");
  Assert(!IsPalindrom("xdantbadx"), "3");
}

void TestNotAPalindrome() {
  Assert(!IsPalindrom("abcdefg"), "not a palindrome");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestAllSymbolsPalindrome, "TestAllSymbolsPalindrome");
  runner.RunTest(TestSpacePalindrome, "TestSpacePalindrome");
  runner.RunTest(TestEmptyStringPalindrome, "TestEmptyStringPalindrome");
  runner.RunTest(TestSingleCharacterPalindrome, "TestSingleCharacterPalindrome");
  runner.RunTest(TestSimpleOddCharacterNumberPalindrome, "TestSimpleOddCharacterNumberPalindrome");
  runner.RunTest(TestSimpleEvenCharacterNumberPalindrome, "TestSimpleEvenCharacterNumberPalindrome");
  runner.RunTest(TestAllCharactersAreComparedInPalindrome, "TestAllCharactersAreComparedInPalindrome");
  runner.RunTest(TestNotAPalindrome, "TestNotAPalindrome");
  return 0;
}
