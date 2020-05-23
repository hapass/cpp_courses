#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "test_runner.h"

using namespace std;

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
        auto it = name_history.lower_bound(year);

        if (it != name_history.end() && it->first == year) {
            return it->second;
        }

        if (it == name_history.begin()) {
            return "";
        }

        return prev(it)->second;
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
