#include <iostream>
#include <algorithm>
#include <stack>
#include <map>

using namespace std;

class Person {
public:
    Person(const string& first_name, const string& last_name, int year) {
        ChangeFirstName(year, first_name);
        ChangeLastName(year, last_name);
    }

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
            return "No person";
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
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }
    
    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}