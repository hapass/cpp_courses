#include <iostream>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        first_name_history[year] = first_name;
    }

    void ChangeLastName(int year, const string& last_name) {
        last_name_history[year] = last_name;
    }

    string GetFullName(int year) const {
        stack<string> first_name_history_to_year = GetNameHistoryToYear(first_name_history, year);
        stack<string> last_name_history_to_year = GetNameHistoryToYear(last_name_history, year);
        return GetNamePair(GetLatestName(first_name_history_to_year), GetLatestName(last_name_history_to_year));
    }

    string GetFullNameWithHistory(int year) const {
        stack<string> first_name_history_to_year = GetNameHistoryToYear(first_name_history, year);
        stack<string> last_name_history_to_year = GetNameHistoryToYear(last_name_history, year);
        return GetNamePair(GetLatestNameWithHistory(first_name_history_to_year), GetLatestNameWithHistory(last_name_history_to_year));
    }
private:
    string GetNamePair(const string& first_name, const string& last_name) const {
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

    string GetLatestName(stack<string>& history) const {
        string current_name;
        if (!history.empty())
        {
            current_name = history.top();
            while (!history.empty() && current_name == history.top()) history.pop();
        }
        return current_name;
    }

    string GetLatestNameWithHistory(stack<string>& history) const {
        string latest_name = GetLatestName(history);

        string history_string = "(";
        while(!history.empty()) {
            string next_name = history.top();
            while (!history.empty() && next_name == history.top()) history.pop();
            history_string += next_name;
            history_string += ", ";
        }

        if (history_string.size() == 1) {
            return latest_name;
        }

        history_string.resize(history_string.size() - 2);
        history_string += ')';
        return latest_name + ' ' + history_string;
    }

    stack<string> GetNameHistoryToYear(const map<int, string>& name_history, int year) const {
        stack<string> history_to_year;
        for (const auto& [key, value] : name_history) {
            if (key <= year) {
                history_to_year.push(value);
            }
            else {
                break;
            }
        }
        return history_to_year;
    }

    map<int, string> first_name_history;
    map<int, string> last_name_history;
};

int main() {
  Person person;
  
  person.ChangeFirstName(1965, "Polina");
  person.ChangeLastName(1967, "Sergeeva");
  for (int year : {1900, 1965, 1990}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1970, "Appolinaria");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1968, "Volkova");
  for (int year : {1969, 1970}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1990, "Polina");
  person.ChangeLastName(1990, "Volkova-Sergeeva");
  cout << person.GetFullNameWithHistory(1990) << endl;
  
  person.ChangeFirstName(1966, "Pauline");
  cout << person.GetFullNameWithHistory(1966) << endl;
  
  person.ChangeLastName(1960, "Sergeeva");
  for (int year : {1960, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeLastName(1961, "Ivanova");
  cout << person.GetFullNameWithHistory(1967) << endl;
  
  return 0;
}