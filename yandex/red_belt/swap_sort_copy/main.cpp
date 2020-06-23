#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
void Swap(T* first, T* second) {
  T temp = *second;
  *second = *first;
  *first = temp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
  sort(pointers.begin(), pointers.end(), [](T* lhs, T* rhs) { return *lhs < *rhs; });
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
  T* source_end = source + count;
  T* r_source = source - 1;
  T* r_source_end = source + count - 1;
  T* destination_end = destination + count;
  T* r_destination = destination - 1;
  T* r_destination_end = destination + count - 1;

  if (source == destination) {
    reverse(source, source_end);
    return;
  }

  bool is_found = false;
  T* it_g = source;
  while (it_g != source_end) {
    if (it_g == destination) {
      is_found = true;
      break;
    }
    it_g++;
  }

  if (is_found) {
    reverse(destination, source_end);
    auto it = r_destination;
    while (it != r_source) {
      *source_end++ = *it--;
    }
    return;
  }

  is_found = false;
  it_g = destination;
  while (it_g != destination_end) {
    if (it_g == source) {
      is_found = true;
      break;
    }
    it_g++;
  }

  if (is_found) {
    reverse(source, destination_end);
    auto it = r_source_end;
    while (it != r_destination_end) {
      *destination++ = *it--;
    }
    return;
  }

  it_g = r_source_end;
  while (it_g != r_source) {
    *destination++ = *it_g--;
  }
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  delete[] dest;
  delete[] source;
}

void TestReverseCopyInPlaceOne() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }

  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

void TestReverseCopyInPlaceTwo() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }

  ReversedCopy(source + 1, count - 1, source);
  const vector<int> expected3 = {7, 6, 5, 4, 3, 2, 7};
  ASSERT_EQUAL(vector<int>(source, source + count), expected3);

  delete[] dest;
  delete[] source;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  RUN_TEST(tr, TestReverseCopyInPlaceOne);
  RUN_TEST(tr, TestReverseCopyInPlaceTwo);
  return 0;
}