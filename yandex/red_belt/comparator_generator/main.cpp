#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

ostream& operator<<(ostream& stream, const Date& date) {
  stream << date.year << "." << date.month << "." << date.day;
  return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
  return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}

ostream& operator<<(ostream& stream, const Time& time) {
  stream << time.hours << "." << time.minutes;
  return stream;
}

bool operator<(const Time& lhs, const Time& rhs) {
  return tie(lhs.hours, lhs.minutes) < tie(rhs.hours, rhs.minutes);
}

bool operator==(const Time& lhs, const Time& rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}

ostream& operator<<(ostream& stream, const AirlineTicket& ticket) {
  stream << ticket.from << " ";
  stream << ticket.to << " ";
  stream << ticket.airline << " ";
  stream << ticket.departure_date << " ";
  stream << ticket.departure_time << " ";
  stream << ticket.arrival_date << " ";
  stream << ticket.arrival_time << " ";
  stream << ticket.price;
  return stream;
}

#define SORT_BY(field) [](const AirlineTicket& lhs, const AirlineTicket& rhs) { \
  return lhs.field < rhs.field; \
}

void TestSortBy() {
  vector<AirlineTicket> tixs = {
    {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
    {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
    {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
    {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
    {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
  };

  sort(begin(tixs), end(tixs), SORT_BY(price));
  ASSERT_EQUAL(tixs.front().price, 1200);
  ASSERT_EQUAL(tixs.back().price, 9000);

  sort(begin(tixs), end(tixs), SORT_BY(from));
  ASSERT_EQUAL(tixs.front().from, "AER");
  ASSERT_EQUAL(tixs.back().from, "VKO");

  sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
  ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
  ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));

  sort(begin(tixs), end(tixs), SORT_BY(arrival_time));
  ASSERT_EQUAL(tixs.front().arrival_time, (Time{3, 30}));
  ASSERT_EQUAL(tixs.back().arrival_time, (Time{20, 30}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSortBy);
}
