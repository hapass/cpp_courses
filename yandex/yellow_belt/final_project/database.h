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
        std::vector<std::pair<Date, std::string>> result = FindIf(predicate);
        for (const auto &pair : result)
        {
            auto &vec = db_vec.at(pair.first);
            auto it = std::remove(vec.begin(), vec.end(), pair.second);
            vec.erase(it, vec.end());
            db_set.at(pair.first).erase(pair.second);

            if (db_set.count(pair.first) != 0 && db_set.at(pair.first).size() == 0)
            {
                db_set.erase(pair.first);
                db_vec.erase(pair.first);
            }
        }
        return result.size();
    }

    template <typename P>
    std::vector<std::pair<Date, std::string>> FindIf(P predicate) const
    {
        std::vector<std::pair<Date, std::string>> result;
        for (const auto &pair : db_vec)
        {
            for (const auto &event : pair.second)
            {
                if (predicate(pair.first, event))
                {
                    result.push_back({pair.first, event});
                }
            }
        }
        return result;
    }

    std::pair<Date, std::string> Last(const Date &date) const;
    void Print(std::ostream &stream) const;

private:
    std::map<Date, std::vector<std::string>> db_vec;
    std::map<Date, std::set<std::string>> db_set;
};

std::ostream &operator<<(std::ostream &stream, const std::pair<Date, std::string> &pair);