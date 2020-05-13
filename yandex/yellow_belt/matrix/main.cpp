#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix() {}
    Matrix(int num_rows, int num_columns) {
        Reset(num_rows, num_columns);
    }

    void Reset(int num_rows, int num_columns) {
        if (num_rows < 0) throw out_of_range("number of rows cannot be negative");
        if (num_columns < 0) throw out_of_range("number of columns cannot be negative");

        rows = num_rows;
        columns = num_columns;
        data.assign(rows * columns, 0);
    }

    int At(int row, int column) const {
        if (row >= rows || row < 0) throw out_of_range("invalid row");
        if (column >= columns || column < 0) throw out_of_range("invalid column");

        return data.at(row * columns + column);
    }

    int& At(int row, int column) {
        if (row >= rows || row < 0) throw out_of_range("invalid row");
        if (column >= columns || column < 0) throw out_of_range("invalid column");

        return data.at(row * columns + column);
    }

    int GetNumRows() const { return rows; }
    int GetNumColumns() const { return columns; }
    bool IsEmpty() const { return data.size() == 0; }
private:
    vector<int> data;
    int rows = 0;
    int columns = 0;
};

istream& operator>>(istream& stream, Matrix& matrix) {
    int m, n;
    stream >> m >> n;
    matrix.Reset(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            stream >> matrix.At(i, j);
        }
    }
    return stream;
}

ostream& operator<<(ostream& stream, const Matrix& matrix) {
    stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int i = 0; i < matrix.GetNumRows(); i++) {
        for (int j = 0; j < matrix.GetNumColumns(); j++) {
            stream << matrix.At(i, j);
            if (j != matrix.GetNumColumns() - 1) {
                stream << " ";
            }
        }
        if (i != matrix.GetNumRows() - 1) {
            stream << endl;
        }
    }
    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.IsEmpty() && rhs.IsEmpty()) return true;
    if (lhs.GetNumColumns() != rhs.GetNumColumns()) return false;
    if (lhs.GetNumRows() != rhs.GetNumRows()) return false;
    for (int i = 0; i < lhs.GetNumRows(); i++) {
        for (int j = 0; j < lhs.GetNumColumns(); j++) {
            if (rhs.At(i, j) != lhs.At(i, j)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.IsEmpty() && rhs.IsEmpty()) return {};
    if (lhs.GetNumColumns() != rhs.GetNumColumns()) throw invalid_argument("different column sizes");
    if (lhs.GetNumRows() != rhs.GetNumRows()) throw invalid_argument("different row sizes");

    Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int i = 0; i < lhs.GetNumRows(); i++) {
        for (int j = 0; j < lhs.GetNumColumns(); j++) {
            result.At(i, j) = rhs.At(i, j) + lhs.At(i, j);
        }
    }
    return result;
}

int main() {
    Matrix one(1, 1);
    Matrix two(1, 1);
    Matrix three(1, 1);

    cin >> one >> two;
    cout << one + two << endl;

    return 0;
}
