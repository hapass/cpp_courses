#include "test_runner.h"
#include <vector>
#include <future>
using namespace std;

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    size_t row_count = matrix.size();
    if (row_count == 0) return 0;
    size_t col_count = matrix.at(0).size();
    if (col_count == 0) return 0;
    
    size_t parts = row_count < 8 ? 1 : 8;
    size_t chunk = row_count / parts;

    vector<future<int64_t>> sums;
    for (size_t part = 0; part < parts; part++) {
        sums.push_back(async([part, parts, chunk, row_count, col_count, &matrix]{
            int64_t sum = 0;
            size_t chunk_start = part * chunk;
            size_t chunk_end = part == (parts - 1) ? row_count : chunk_start + chunk;
            for (size_t i = chunk_start; i < chunk_end; i++)
            for (size_t j = 0; j < col_count; j++) {
                sum += matrix[i][j];
            }
            return sum;
        }));
    }

    int64_t sum = 0;
    for (size_t i = 0; i < sums.size(); i++) {
        sum += sums[i].get();
    }
    return sum;
}

void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestCalculateMatrixSum);
}
