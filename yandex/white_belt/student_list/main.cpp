#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string name;
    string last_name;
    int day;
    int month;
    int year;
};

int main() {
    int student_count = 0;
    cin >> student_count;

    vector<Student> students(student_count);

    for (Student& s : students) {
        cin >> s.name;
        cin >> s.last_name;
        cin >> s.day;
        cin >> s.month;
        cin >> s.year;
    }

    int command_count = 0;
    cin >> command_count;

    while (--command_count >= 0) {
        string command;
        int student_id;
        if (cin >> command && cin >> student_id) {
            int i = student_id - 1;
            if (command == "name") {
                cout << students[i].name << " " << students[i].last_name << endl;
            }
            else if (command == "date") {
                cout << students[i].day << "." << students[i].month << "." << students[i].year << endl;
            }
            else {
                cout << "bad request" << endl;
            }
        }
        else {
            cout << "bad request" << endl;
        }
    }

    return 0;
}