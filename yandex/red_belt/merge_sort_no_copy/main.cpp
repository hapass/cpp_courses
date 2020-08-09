#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) return;
    vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));
    size_t part_size = (elements.size() / 3);
    RandomIt first_boundary = elements.begin() + part_size;
    RandomIt second_boundary = first_boundary + part_size;

    MergeSort(elements.begin(), first_boundary);
    MergeSort(first_boundary, second_boundary);
    MergeSort(second_boundary, elements.end());

    vector<typename RandomIt::value_type> merged_parts;
    merge(make_move_iterator(elements.begin()), 
      make_move_iterator(first_boundary),
      make_move_iterator(first_boundary),
      make_move_iterator(second_boundary),
      back_inserter(merged_parts));
    merge(make_move_iterator(merged_parts.begin()),
          make_move_iterator(merged_parts.end()),
          make_move_iterator(second_boundary),
          make_move_iterator(elements.end()),
          range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
