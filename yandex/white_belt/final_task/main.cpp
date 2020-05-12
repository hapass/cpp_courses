#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <exception>
#include <iomanip>

using namespace std;

class Date {
public:
    Date() {}
    Date(int y, int m, int d): year(y), month(m), day(d) {
        if (!IsMonthValid()) throw invalid_argument("Month value is invalid: " + to_string(month));
        if (!IsDayValid()) throw invalid_argument("Day value is invalid: " + to_string(day));
    }

    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }

private:
    bool IsMonthValid() { return 0 < month && month <= 12; }
    bool IsDayValid() { return 0 < day && day <= 31; }

    int year = 1;
    int month = 1;
    int day = 1;
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    else {
        return lhs.GetYear() < rhs.GetYear();
    }
}

bool IsDigit(char ch) {
    return 48 <= ch && ch <= 57;
}

bool MatchNumber(int& out, int& i, const string& str) {
    stringstream result;

    if (str[i] == '-') {
        result << str[i];
        i++;
    }

    if (str[i] == '+') {
        i++;
    }

    while(i < str.size() && IsDigit(str[i])) {
        result << str[i];
        i++;
    }

    return bool(result >> out);
}

bool SkipDelimiter(int& i, const string& str) {
    if (i < str.size() && str[i] == '-') {
        i++;
        return true;
    }
    return false;
}

bool MatchEnd(int& i, const string& str) {
    return i >= str.size();
}

istream& operator>>(istream& stream, Date& date) {
    string input;
    stream >> input;

    int year, month, day;
    int i = 0;
    bool success = true;
    success &= MatchNumber(year, i, input);
    success &= SkipDelimiter(i, input);
    success &= MatchNumber(month, i, input);
    success &= SkipDelimiter(i, input);
    success &= MatchNumber(day, i, input);
    success &= MatchEnd(i, input);
    if (success) {
        date = Date(year, month, day);
        return stream;
    }
    throw domain_error("Wrong date format: " + input);
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0')
        << setw(4) << date.GetYear()
        << '-'
        << setw(2) << date.GetMonth()
        << '-'
        << setw(2) << date.GetDay();
    return stream;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) {
        db[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const string& event) {
        if (db.count(date) != 0 && db.at(date).count(event) != 0) {
            db.at(date).erase(event);
            if (db.at(date).size() == 0) {
                db.erase(date);
            }
            return true;
        }
        return false;
    }

    int DeleteDate(const Date& date) {
        if (db.count(date) != 0) {
            int count = db.at(date).size();
            db.erase(date);
            return count;
        }
        return 0;
    }

    set<string> Find(const Date& date) const {
        return db.count(date) != 0 ? db.at(date) : set<string>{};
    }
    
    void Print() const {
        for (const auto& [date, events] : db) {
            for (const auto& event : events) {
                cout << date << " " << event << endl;
            }
        }
    }
private:
    map<Date, set<string>> db;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        try {
            stringstream ss(command);
            string action;
            if (ss >> action) {
                if (action == "Add") {
                    Date date;
                    string event;
                    if (ss >> date >> event) {
                        db.AddEvent(date, event);
                    }
                }
                else if (action == "Del") {
                    Date date;
                    string event;
                    if (ss >> date) {
                        if (ss >> event) {
                            if (db.DeleteEvent(date, event)) {
                                cout << "Deleted successfully" << endl;
                            }
                            else {
                                cout << "Event not found" << endl;
                            }
                        }
                        else {
                            cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                        }
                    }
                }
                else if (action == "Find") {
                    Date date;
                    if (ss >> date) {
                        set<string> events = db.Find(date);
                        for (const auto& event : events) {
                            cout << event << endl;
                        }
                    }
                }
                else if (action == "Print") {
                    db.Print();
                }
                else {
                    cout << "Unknown command: " << action << endl;
                }
            }
        }
        catch (domain_error& e) {
            cout << e.what() << endl;
        }
        catch (invalid_argument& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}