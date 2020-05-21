#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) return;
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    size_t part_size = (elements.size() / 3);
    RandomIt first_boundary = elements.begin() + part_size;
    RandomIt second_boundary = first_boundary + part_size;
    MergeSort(elements.begin(), first_boundary);
    MergeSort(first_boundary, second_boundary);
    MergeSort(second_boundary, elements.end());
    vector<typename RandomIt::value_type> merged_parts;
    merge(elements.begin(), first_boundary, first_boundary, second_boundary, back_inserter(merged_parts));
    merge(merged_parts.begin(), merged_parts.end(), second_boundary, elements.end(), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}