#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

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
  for (int i = 32; i <= 126; i++) oss << static_cast<char>(i);
  for (int i = 126; i >= 32; i--) oss << static_cast<char>(i);
  Assert(IsPalindrom(oss.str()), "all character palindrome");
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

void TestAllCharactersButLastPalindrome() {
  Assert(!IsPalindrom("zabbax"), "palindrome for all characters but last");
}

void TestAllCharactersButInsidePalindrome() {
  Assert(!IsPalindrom("ragnar"), "palindrome for all characters but inside");
}

void TestNotAPalindrome() {
  Assert(!IsPalindrom("abcdefg"), "not a palindrome");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestAllSymbolsPalindrome, "TestAllSymbolsPalindrome");
  runner.RunTest(TestEmptyStringPalindrome, "TestEmptyStringPalindrome");
  runner.RunTest(TestSingleCharacterPalindrome, "TestSingleCharacterPalindrome");
  runner.RunTest(TestSimpleOddCharacterNumberPalindrome, "TestSimpleOddCharacterNumberPalindrome");
  runner.RunTest(TestSimpleEvenCharacterNumberPalindrome, "TestSimpleEvenCharacterNumberPalindrome");
  runner.RunTest(TestAllCharactersButLastPalindrome, "TestAllCharactersButLastPalindrome");
  runner.RunTest(TestAllCharactersButInsidePalindrome, "TestAllCharactersButInsidePalindrome");
  runner.RunTest(TestNotAPalindrome, "TestNotAPalindrome");
  return 0;
}
