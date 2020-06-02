#include "database.h"
#include "date.h"

using namespace std;

ostream &operator<<(ostream &stream, const pair<Date, string> &pair)
{
    return stream << pair.first << " " << pair.second;
}

void Database::Add(const Date &date, const string &event)
{
    if (db_set.count(date) == 0 || db_set.at(date).count(event) == 0) {
        db_set[date].insert(event);
        db_vec[date].push_back(event);
    }
}

pair<Date, string> Database::Last(const Date &date) const
{
    auto iter_after = db_set.upper_bound(date);
    if (iter_after == db_set.begin())
    {
        throw invalid_argument("no entries");
    }
    const Date& upper_date = (--iter_after)->first;
    return { upper_date, db_vec.at(upper_date).back() };
}

void Database::Print(ostream &stream) const
{
    for (const auto &pair : db_set)
    {
        for (const auto &event : db_vec.at(pair.first))
        {
            stream << make_pair(pair.first, event) << endl;
        }
    }
}