#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "test_runner.h"

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix, int index) {
    string ss(index + 1, prefix);
    return equal_range(range_begin, range_end, ss, [index](const string& lhs, const string& rhs) {
        if (index >= lhs.size()) return true;
        return lhs[index] < rhs[index];
    });
}

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, const string& prefix) {
    pair<RandomIt, RandomIt> result = { range_begin, range_end };
    for (int i = 0; i < prefix.size(); i++) {
        result = FindStartsWith(result.first, result.second, prefix[i], i);
    }
    return result;
}

int main() {
    const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
    
    const auto mo_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    const auto mt_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " <<
        (mt_result.second - begin(sorted_strings)) << endl;
    
    const auto na_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " <<
        (na_result.second - begin(sorted_strings)) << endl;
    return 0;
}
