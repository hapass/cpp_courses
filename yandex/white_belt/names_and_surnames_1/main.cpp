#include <iostream>
#include <algorithm>
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

int main() {
    Person person;
    
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }
    
    return 0;
}