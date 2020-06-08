#include "test_runner.h"
#include <vector>

using namespace std;

template<typename T>
class Table {
public:
  Table(size_t rows, size_t columns): rows_(rows), columns_(columns), table_(rows, vector<T>(columns, T())) {}

  pair<size_t, size_t> Size() const { return { rows_, columns_ }; }

  void Resize(size_t rows, size_t columns) {
    for (auto& row : table_) {
      row.resize(columns, T());
    }
    table_.resize(rows, vector<T>(columns));
    rows_ = rows;
    columns_ = columns;
  }

  const vector<T>& operator[](size_t row) const { return table_[row]; }
  vector<T>& operator[](size_t row) { return table_[row]; }
private:
  size_t rows_;
  size_t columns_;
  vector<vector<T>> table_;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(2, 2);
  ASSERT_EQUAL(t.Size().first, 2u);
  ASSERT_EQUAL(t.Size().second, 2u);
  ASSERT_EQUAL(t[0][0], 42);
  ASSERT_EQUAL(t[1][0], 0);
  ASSERT_EQUAL(t[0][1], 0);
  ASSERT_EQUAL(t[1][1], 0);
  t.Resize(1, 1);
  ASSERT_EQUAL(t[0][0], 42);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
