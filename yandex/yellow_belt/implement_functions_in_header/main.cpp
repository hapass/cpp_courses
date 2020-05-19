#include "test_runner.h"
#include "sum_reverse_sort.h"

void TestSum() {
    AssertEqual(Sum(2, 3), 5, "Sum: 2+3");
    AssertEqual(Sum(2, -3), -1, "Sum: 2-3");
    AssertEqual(Sum(-2, 3), 1, "Sum: -2+3");
    AssertEqual(Sum(0, 3), 3, "Sum: 0+3");
    AssertEqual(Sum(0, 0), 0, "Sum: 0+0");
    AssertEqual(Sum(-2, -3), -5, "Sum: -2-3");
}

void TestSort() {
    {
        vector<int> unsorted = {4, 3, 6, 1};
        vector<int> expected = {1, 3, 4, 6};
        Sort(unsorted);
        AssertEqual(unsorted, expected, "Array of positives is sorted.");
    }

    {
        vector<int> unsorted = {5, 4, 3, 2};
        vector<int> expected = {2, 3, 4, 5};
        Sort(unsorted);
        AssertEqual(unsorted, expected, "Array of reversed positives is sorted.");
    }
}

void TestReverse() {
    string str("abcde");
    AssertEqual(Reverse(str), "edcba");
}

int main() {
    TestRunner r;
    r.RunTest(TestSum, "TestSum");
    r.RunTest(TestSort, "TestSort");
    r.RunTest(TestReverse, "TestReverse");
    return 0;
}

