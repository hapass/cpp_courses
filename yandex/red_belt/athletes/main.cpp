#include <iostream>
#include <map>
#include <list>

using namespace std;

int main() {
  map<int, list<int>::iterator> athletes_set;
  list<int> athletes_list;

  int n;
  cin >> n;
  while (n-- > 0)
  {
    int new_athlete, athlete_after;
    cin >> new_athlete >> athlete_after;
    if (athletes_set.count(athlete_after) == 0)
    {
      athletes_list.push_back(new_athlete);
      athletes_set[new_athlete] = prev(athletes_list.end());
    }
    else
    {
      athletes_set[new_athlete] = athletes_list.insert(athletes_set.at(athlete_after), new_athlete);
    }
  }

  for (const int number : athletes_list)
  {
    cout << number << "\n";
  }
  return 0;
}
