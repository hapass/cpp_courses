#pragma once

#include "date.h"

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class Database
{
public:
    void Add(const Date &date, const std::string &event);

    template <typename P>
    int RemoveIf(P predicate)
    {
        auto it = std::remove_if(db.begin(), db.end(), [predicate](const std::pair<Date, std::string> &pair) {
            return predicate(pair.first, pair.second);
        });
        int count = db.end() - it;
        db.erase(it, db.end());
        return count;
    }

    template <typename P>
    std::vector<std::pair<Date, std::string>> FindIf(P predicate) const
    {
        std::vector<std::pair<Date, std::string>> result;
        std::copy_if(db.begin(), db.end(), std::back_inserter(result), [predicate](const std::pair<Date, std::string> &pair) {
            return predicate(pair.first, pair.second);
        });
        return result;
    }

    std::pair<Date, std::string> Last(const Date &date) const;
    void Print(std::ostream &stream) const;

private:
    std::vector<std::pair<Date, std::string>> db;
};

std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &pair);