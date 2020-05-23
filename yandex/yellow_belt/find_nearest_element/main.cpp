#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {
    if (numbers.begin() == numbers.end()) return numbers.end();

    auto not_less = numbers.lower_bound(border);

    if (not_less != numbers.begin()) {
        auto distance_not_less = abs(border - *not_less);
        auto distance_less = abs(border - *prev(not_less));
        return distance_less <= distance_not_less ? prev(not_less) : not_less;
    }

    return not_less;
}

int main() {
  set<int> numbers = {1, 4, 6};
  cout <<
      *FindNearestElement(numbers, 0) << " " <<
      *FindNearestElement(numbers, 3) << " " <<
      *FindNearestElement(numbers, 5) << " " <<
      *FindNearestElement(numbers, 6) << " " <<
      *FindNearestElement(numbers, 100) << endl;
      
  set<int> empty_set;
  
  cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
  return 0;
}
