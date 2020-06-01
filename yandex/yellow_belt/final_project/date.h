#pragma once

#include <iostream>

class Date {
public:
    Date();
    Date(int y, int m, int d);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    bool IsMonthValid() const;
    bool IsDayValid() const;

    int year = 1;
    int month = 1;
    int day = 1;
};

bool operator<(const Date& lhs, const Date& rhs);
std::istream& operator>>(std::istream& stream, Date& date);
std::ostream& operator<<(std::ostream& stream, const Date& date);

Date ParseDate(std::istream& stream);
