#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

int main() {
    int operationsCount = 0;
    cin >> operationsCount;

    int currentMonth = 0;
    vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    vector<vector<string>> activities(daysInMonth[currentMonth]);

    while (operationsCount > 0)
    {
        string operation;
        cin >> operation;

        if (operation == "ADD") {
            int day = 0;
            cin >> day;
            int index = day - 1;

            string activity;
            cin >> activity;

            assert(index >= 0 && index < activities.size());
            activities[index].push_back(activity);
        }
        else if (operation == "DUMP") {
            int day = 0;
            cin >> day;
            int index = day - 1;

            cout << activities[index].size() << ' ';
            for (const string& activity : activities[index]) {
                cout << activity << ' ';
            }
            cout << endl;
        }
        else if (operation == "NEXT") {
            int nextMonth = (currentMonth + 1) % 12;

            if (daysInMonth[nextMonth] < daysInMonth[currentMonth]) {
                for (int day = daysInMonth[nextMonth]; day < daysInMonth[currentMonth]; day++) {
                    activities[daysInMonth[nextMonth] - 1].insert(end(activities[daysInMonth[nextMonth] - 1]), begin(activities[day]), end(activities[day]));
                }
            }

            activities.resize(daysInMonth[nextMonth]);
            currentMonth = nextMonth;
        }

        operationsCount--;
    }
    return 0;
}