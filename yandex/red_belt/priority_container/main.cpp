#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <map>
#include <utility>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = uint64_t;

  PriorityCollection(): id_(0) {}

  Id Add(T object) {
    objects_[id_++] = move(object);
    return id_;
  }

  template<typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
    auto ids_it = ids_begin;
    for (auto it = range_begin; it != range_end; it++) {
      *ids_it = Add(move(*it));
      ids_it++;
    }
  }

  bool IsValid(Id id) const {
    return objects_.count(id) != 0;
  }

  const T& Get(Id id) const {
    return objects_.at(id).first;
  }

  void Promote(Id id) {
    int old_priority = objects_.at(id).second;
    int new_priority = old_priority + 1;
    objects_.at(id).second = new_priority;
    priority_to_ids_.at(old_priority).erase(id);
    priority_to_ids_[new_priority].insert(id);
  }

  pair<const T&, int> GetMax() const {
    pair<Id, int> max_entry = GetMaxEntry();
    return {objects_.at(max_entry.first), max_entry.second};
  }

  pair<T, int> PopMax() const {
    pair<Id, int> max_entry = GetMaxEntry();
    pair<T, int> max_object = { move(objects_.at(max_entry.first)), max_entry.second };
    priority_to_ids_.at(max_entry.second).erase(max_entry.first);
    objects_.erase(max_entry.first);
    return max_object;
  }

private:
  pair<Id, int> GetMaxEntry() const {
    return {*priority_to_ids_.rbegin()->second.begin(), priority_to_ids_.rbegin()->first};
  }

  map<Id, pair<T, int>> objects_;
  map<int, set<Id>> priority_to_ids_;
  uint64_t id_;
};

int main() {
  PriorityCollection<string> collection;

  collection.Add("one");
  PriorityCollection<string>::Id two_id = collection.Add("two");
  PriorityCollection<string>::Id three_id = collection.Add("three");

  collection.Promote(two_id);
  collection.Promote(two_id);
  collection.Promote(three_id);

  auto first = collection.PopMax();
  auto second = collection.PopMax();
  auto third = collection.PopMax();
  cout << first.first << endl;
  cout << second.first << endl;
  cout << third.first << endl;
  return 0;
}
