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
  int size = static_cast<int>(s.size());
  for (int i = 0; i < size / 2 ; i++) {
    if (s[i] != s[size - 1 - i]) return false;
  }
  return true;
}

void TestAllSymbolsPalindrome() {
  ostringstream palindrome_stream;
  ostringstream stream;
  vector<char> ascii;

  for (int i = 32; i <= 126; i++) ascii.push_back(static_cast<char>(i));

  std::random_device rd;
  std::mt19937 g(rd());
  for (int i = 0; i < 20; i++) {
    shuffle(ascii.begin(), ascii.end(), g);

    palindrome_stream.str("");
    int size = static_cast<int>(ascii.size());
    for (int j = 0; j < size; j++) palindrome_stream << ascii[j];
    for (int j = 0; j < size; j++) stream << ascii[j];
    for (int j = size - 1; j >= 0; j--) palindrome_stream << ascii[j];

    Assert(IsPalindrom(palindrome_stream.str()), "random string is palindrome");
    Assert(!IsPalindrom(stream.str()), "random string is not palindrome");
  }
}

void TestSpacePalindrome() {
  Assert(IsPalindrom(" "), " is a palindrome");
  Assert(IsPalindrom("!"), "! is a palindrome");
  Assert(IsPalindrom("!!"), "!! is a palindrome");
  Assert(!IsPalindrom("!*"), "!* is not a palindrome");
  Assert(IsPalindrom("\n"), "\n is a palindrome");
  Assert(IsPalindrom("\n\n"), "\n\n is a palindrome");
  Assert(IsPalindrom("\n\n\n"), "\n\n\n is a palindrome");
  Assert(!IsPalindrom("1\n\n"), "1\n\n is not a palindrome");
  Assert(IsPalindrom("a a"), "a a is a palindrome");
  Assert(IsPalindrom(" a b a "), " a b a  is a palindrome");
  Assert(IsPalindrom(" a  b  a "), " a b a  is a palindrome");
  Assert(!IsPalindrom(" a! b  a "), " a b a  is a palindrome");
}

void TestRepeatingCharacterPalindrome() {
  Assert(IsPalindrom("aaaaa"), "aaaaa is a palindrome");
  Assert(IsPalindrom("bbbbbb"), "bbbbbb is a palindrome");
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
  Assert(!IsPalindrom("zdabtbadx"), "zdabtbadx is not a palindrome");
  Assert(!IsPalindrom("zdabtbad"), "zdabtbad is not a palindrome");
  Assert(!IsPalindrom("dabtbadx"), "dabtbadx is not a palindrome");
  Assert(!IsPalindrom("xfabtbadx"), "xfabtbadx is not a palindrome");
  Assert(!IsPalindrom("xdrbtbadx"), "xdrbtbadx is not a palindrome");
  Assert(!IsPalindrom("xdantbadx"), "xdantbadx is not a palindrome");
}

void TestNotAPalindrome() {
  Assert(!IsPalindrom("abcdefg"), "abcdefg is not a palindrome");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestAllSymbolsPalindrome, "TestAllSymbolsPalindrome");
  runner.RunTest(TestRepeatingCharacterPalindrome, "TestRepeatingCharacterPalindrome");
  runner.RunTest(TestSpacePalindrome, "TestSpacePalindrome");
  runner.RunTest(TestEmptyStringPalindrome, "TestEmptyStringPalindrome");
  runner.RunTest(TestSingleCharacterPalindrome, "TestSingleCharacterPalindrome");
  runner.RunTest(TestSimpleOddCharacterNumberPalindrome, "TestSimpleOddCharacterNumberPalindrome");
  runner.RunTest(TestSimpleEvenCharacterNumberPalindrome, "TestSimpleEvenCharacterNumberPalindrome");
  runner.RunTest(TestAllCharactersAreComparedInPalindrome, "TestAllCharactersAreComparedInPalindrome");
  runner.RunTest(TestNotAPalindrome, "TestNotAPalindrome");
  return 0;
}
