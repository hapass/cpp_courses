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

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_name_history[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        last_name_history[year] = last_name;
    }

    string GetFullName(int year) {
        string first_name = GetName(first_name_history, year);
        string last_name = GetName(last_name_history, year);
        if (first_name == "" && last_name == "") {
            return "Incognito";
        }
        if (first_name == "" && last_name != "") {
            return last_name + " with unknown first name";
        }
        if (first_name != "" && last_name == "") {
            return first_name + " with unknown last name";
        }
        return first_name + " " + last_name;
    }
private:
    string GetName(map<int, string>& name_history, int year) {
        string name;
        if (name_history[year] == "") {
            int previousYear = -1;
            for (const auto& [key, value] : name_history) {
                if (key == year) {
                    break;
                }

                if (value != "") {
                    previousYear = key;
                }
            }
            if (previousYear != -1) {
                name = name_history[previousYear];
            }
        }
        else {
            name = name_history[year];
        }
        return name;
    }
    map<int, string> first_name_history;
    map<int, string> last_name_history;
};

void TestChangeFirstNameOnly() {
  Person p;
  p.ChangeFirstName(1960, "Polina");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Polina with unknown last name", "1960");
  AssertEqual(p.GetFullName(1961), "Polina with unknown last name", "1961");
}

void TestChangeLastNameOnly() {
  Person p;
  p.ChangeLastName(1960, "Sergeeva");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Sergeeva with unknown first name", "1960");
  AssertEqual(p.GetFullName(1961), "Sergeeva with unknown first name", "1961");
}

void TestFirstAndLastName() {
  Person p;
  p.ChangeFirstName(1960, "Polina");
  p.ChangeLastName(1960, "Sergeeva");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Polina Sergeeva", "1960");
  AssertEqual(p.GetFullName(1961), "Polina Sergeeva", "1961");
}

void TestPreviousFirstName() {
  Person p;
  p.ChangeFirstName(1960, "Polina");
  p.ChangeLastName(1960, "Sergeeva");
  p.ChangeFirstName(1970, "Olga");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Polina Sergeeva", "1960");
  AssertEqual(p.GetFullName(1970), "Olga Sergeeva", "1970");
  AssertEqual(p.GetFullName(1970), "Olga Sergeeva", "1971");
}

void TestPreviousLastName() {
  Person p;
  p.ChangeFirstName(1960, "Polina");
  p.ChangeLastName(1960, "Sergeeva");
  p.ChangeLastName(1970, "Romanova");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Polina Sergeeva", "1960");
  AssertEqual(p.GetFullName(1970), "Polina Romanova", "1970");
  AssertEqual(p.GetFullName(1970), "Polina Romanova", "1971");
} 

void TestUpdateHistoryFirstName() {
  Person p;
  p.ChangeFirstName(1970, "Olga");
  p.ChangeLastName(1960, "Sergeeva");
  p.ChangeFirstName(1960, "Polina");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Polina Sergeeva", "1960");
  AssertEqual(p.GetFullName(1970), "Olga Sergeeva", "1970");
  AssertEqual(p.GetFullName(1970), "Olga Sergeeva", "1971");
}

void TestUpdateHistoryLastName() {
  Person p;
  p.ChangeFirstName(1960, "Polina");
  p.ChangeLastName(1970, "Romanova");
  p.ChangeLastName(1960, "Sergeeva");
  AssertEqual(p.GetFullName(1959), "Incognito", "1959");
  AssertEqual(p.GetFullName(1960), "Polina Sergeeva", "1960");
  AssertEqual(p.GetFullName(1970), "Polina Romanova", "1970");
  AssertEqual(p.GetFullName(1970), "Polina Romanova", "1971");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestChangeFirstNameOnly, "TestChangeFirstNameOnly");
  runner.RunTest(TestChangeLastNameOnly, "TestChangeLastNameOnly");
  runner.RunTest(TestFirstAndLastName, "TestFirstAndLastName");
  runner.RunTest(TestPreviousFirstName, "TestPreviousFirstName");
  runner.RunTest(TestPreviousLastName, "TestPreviousLastName");
  runner.RunTest(TestUpdateHistoryFirstName, "TestUpdateHistoryFirstName");
  runner.RunTest(TestUpdateHistoryLastName, "TestUpdateHistoryLastName");
  return 0;
}
