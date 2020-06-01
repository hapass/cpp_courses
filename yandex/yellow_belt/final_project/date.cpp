#include "date.h"

#include <string>
#include <stdexcept>
#include <sstream>
#include <iomanip>

using namespace std;

Date::Date() {}
Date::Date(int y, int m, int d): year(y), month(m), day(d) {
    if (!IsMonthValid()) throw invalid_argument("Month value is invalid: " + to_string(month));
    if (!IsDayValid()) throw invalid_argument("Day value is invalid: " + to_string(day));
}

bool Date::IsMonthValid() const { return 0 < month && month <= 12; }
bool Date::IsDayValid() const { return 0 < day && day <= 31; }

int Date::GetYear() const { return year; }
int Date::GetMonth() const { return month; }
int Date::GetDay() const { return day; }

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

Date ParseDate(istream& stream) {
    Date date;
    stream >> date;
    return date;
}