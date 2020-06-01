#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>

class Date;

class Database
{
public:
    void Add(const Date &date, const std::string &event);

    template <typename P>
    bool RemoveIf(P predicate)
    {
        return false;
    }

    template <typename P>
    std::set<std::string> FindIf(P predicate) const
    {
        return {};
    }

    std::string Last(const Date &date) const;
    void Print(std::ostream &stream) const;

private:
    std::map<Date, std::set<std::string>> db;
};