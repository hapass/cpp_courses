#include "database.h"
#include "date.h"

using namespace std;

void Database::Add(const Date &date, const string &event)
{
    db[date].insert(event);
}

string Database::Last(const Date &date) const {
    return string();
}

void Database::Print(ostream &stream) const
{
    for (const auto &[date, events] : db)
    {
        for (const auto &event : events)
        {
            stream << date << " " << event << endl;
        }
    }
}