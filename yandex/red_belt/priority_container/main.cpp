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
#include <assert.h>

using namespace std;

template <typename T>
class PriorityCollection {
public:
  using Id = uint64_t;

  PriorityCollection(): id_(0) {}

  Id Add(T object) {
    objects_[++id_] = make_pair<T, int>(move(object), 0);
    priority_to_ids_[0].insert(id_);
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
    assert(IsValid(id));
    return objects_.at(id).first;
  }

  void Promote(Id id) {
    assert(IsValid(id));
    int old_priority = objects_.at(id).second;
    int new_priority = old_priority + 1;
    objects_.at(id).second = new_priority;
    RemoveFromPriorityToId(old_priority, id);
    priority_to_ids_[new_priority].insert(id);
  }

  pair<const T&, int> GetMax() const {
    pair<Id, int> max_entry = GetMaxEntry();
    const pair<T, int>& max_object = objects_.at(max_entry.first);
    return tie(max_object.first, max_object.second);
  }

  pair<T, int> PopMax() {
    pair<Id, int> max_entry = GetMaxEntry();
    pair<T, int> max_object = move(objects_.at(max_entry.first));
    RemoveFromPriorityToId(max_entry.second, max_entry.first);
    objects_.erase(max_entry.first);
    return max_object;
  }

private:
  pair<Id, int> GetMaxEntry() const {
    assert(priority_to_ids_.size() > 0);
    auto max = priority_to_ids_.rbegin();
    assert(max->second.size() > 0);
    return {*max->second.rbegin(), max->first};
  }

  void RemoveFromPriorityToId(int priority, Id id) {
    priority_to_ids_.at(priority).erase(id);
    if (priority_to_ids_.at(priority).size() == 0) {
      priority_to_ids_.erase(priority);
    }
  }

  map<Id, pair<T, int>> objects_;
  map<int, set<Id>> priority_to_ids_;
  uint64_t id_;
};

class StringNonCopyable : public string {
public:
  using string::string;
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);

  {
    ASSERT_EQUAL(strings.GetMax().first, "red");
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
