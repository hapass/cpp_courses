#include "database.h"
#include "date.h"

using namespace std;

ostream &operator<<(ostream &stream, const pair<Date, string> &pair)
{
    return stream << pair.first << " " << pair.second;
}

void Database::Add(const Date &date, const string &event)
{
    auto p = make_pair(date, event);
    auto it = equal_range(db.begin(), db.end(), p, [](const pair<Date, string> &element, const pair<Date, string> &value) {
        return element.first < value.first;
    });
    if (find(it.first, it.second, p) == it.second)
    {
        db.insert(it.second, {date, event});
    }
}

pair<Date, string> Database::Last(const Date &date) const
{
    auto iter_after = upper_bound(db.begin(), db.end(), make_pair(date, ""), [](const pair<Date, string> &element, const pair<Date, string> &value) {
        return element.first < value.first;
    });
    if (iter_after == db.begin())
    {
        throw invalid_argument("no entries");
    }
    return *(--iter_after);
}

void Database::Print(ostream &stream) const
{
    for (const auto &pair : db)
    {
        stream << pair << endl;
    }
}