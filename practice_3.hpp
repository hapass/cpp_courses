#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>

namespace math
{
    class Matrix {
        private:
            std::vector<float> matrix;
        public:
            const int rows;
            const int columns;

            Matrix(int rows, int columns);

            float element(int row, int column) const;
            void set_element(int row, int column, float value);

            std::vector<float> row(int row) const;
            std::vector<float> column(int column) const;

            float dot(std::vector<float> first, std::vector<float> second) const;

            std::vector<float> add(std::vector<float> first, std::vector<float> second) const;
            Matrix add(Matrix other) const;
            Matrix add(float value) const;

            Matrix multiply(Matrix other) const;
            Matrix multiply(float value) const;

            Matrix negate() const;
            Matrix transpose() const;
    };

    Matrix::Matrix(int rows, int columns): rows(rows), columns(columns), matrix(rows * columns) {}

    void Matrix::set_element(int row, int column, float value) {
        assert(row < rows && column < columns);
        matrix[row * columns + column] = value;
    }

    float Matrix::element(int row, int column) const {
        assert(row < rows && row >= 0 && column < columns && column >= 0);
        return matrix[row * columns + column];
    }

    std::vector<float> Matrix::row(int row) const {
        std::vector<float> result;
        for(int column = 0; column < columns; column++) {
            result.push_back(element(row, column));
        }
        return result;
    }

    std::vector<float> Matrix::column(int column) const {
        std::vector<float> result;
        for(int row = 0; row < rows; row++) {
            result.push_back(element(row, column));
        }
        return result;
    }

    float Matrix::dot(std::vector<float> first, std::vector<float> second) const {
        assert(first.size() == second.size());

        float result = 0;
        for(int i = 0; i < first.size(); i++) {
            result += first[i] * second[i];
        }

        return result;
    }

    std::vector<float> Matrix::add(std::vector<float> first, std::vector<float> second) const {
        assert(first.size() == second.size());

        std::vector<float> result;
        for(int i = 0; i < first.size(); i++) {
            result.push_back(first[i] + second[i]);
        }

        return result;
    }

    Matrix Matrix::add(Matrix other) const {
        assert(rows == other.rows && columns == other.columns);

        Matrix result(rows, columns);
        for(int row = 0; row < rows; row++) {
            for(int column = 0; column < columns; column++) {
                result.set_element(row, column, element(row, column) + other.element(row, column));
            }
        }

        return result;
    }

    Matrix Matrix::add(float value) const {
        Matrix result(rows, columns);
        for(int row = 0; row < rows; row++) {
            for(int column = 0; column < columns; column++) {
                result.set_element(row, column, element(row, column) + value);
            }
        }

        return result;
    }

    Matrix Matrix::multiply(Matrix other) const {
        Matrix result(rows, other.columns);

        for(int row = 0; row < rows; row++) {
            for(int column = 0; column < other.columns; column++) {
                result.set_element(row, column, Matrix::dot(Matrix::row(row), other.column(column)));
            }
        }

        return result;
    }

    Matrix Matrix::multiply(float value) const {
        Matrix result(rows, columns);
        for(int row = 0; row < rows; row++) {
            for(int column = 0; column < columns; column++) {
                result.set_element(row, column, element(row, column) * value);
            }
        }

        return result;
    }

    Matrix Matrix::negate() const {
        return Matrix::multiply(-1);
    }

    Matrix Matrix::transpose() const {
        Matrix result(columns, rows);
        for(int row = 0; row < rows; row++) {
            for(int column = 0; column < columns; column++) {
                result.set_element(column, row, element(row, column));
            }
        }

        return result;
    }

    std::ostream& operator<< (std::ostream& out, const std::vector<float>& vec) {
        for(auto i = vec.begin(); i < vec.end(); i++) {
            out << *i << ' ';
        }
        return out;
    }

    std::ostream& operator<< (std::ostream& out, const Matrix& mat) {
        for(int row = 0; row < mat.rows; row++) {
            out << mat.row(row) << std::endl;
        }
        return out;
    }

    std::istream& operator>> (std::istream& in, Matrix& mat) {
        for(int row = 0; row < mat.rows; row++) {
            for(int column = 0; column < mat.columns; column++) {
                float value;
                in >> value;
                mat.set_element(row, column, value);
            }
        }
        return in;
    }

    class MatrixInput {
        private:
            bool (*validator)(float& value);
        public:
            MatrixInput(bool (*validator)(float& value));
            Matrix from_stream(std::istream& in);
            Matrix from_vector(std::vector<float> vec);
    };

    MatrixInput::MatrixInput(bool (*validator)(float& value)): validator(validator) {}

    Matrix MatrixInput::from_vector(std::vector<float> vec) {
        assert(vec.size() >= 2);
        assert(vec.size() == (vec[0] * vec[1]) + 2);

        Matrix result(vec[0], vec[1]);
        for(int row = 0; row < vec[0]; row++) {
            for(int column = 0; column < vec[1]; column++) {
                float value = vec[row * vec[1] + column + 2];
                assert(validator(value));
                result.set_element(row, column, value);
            }
        }
        return result;
    }

    Matrix MatrixInput::from_stream(std::istream& in) {
        float rows;
        float columns;

        in >> rows >> columns;

        Matrix result(rows, columns);
        for(int row = 0; row < rows; row++) {
            for(int column = 0; column < columns; column++) {
                float value;
                in >> value;

                assert(validator(value));
                result.set_element(row, column, value);
            }
        }
        return result;
    }

    void test_1() {
        std::ifstream matrixFile;
        matrixFile.open("matrix.txt");
        if(matrixFile.is_open()) {
            MatrixInput input([](float& value) { return true; });
            Matrix mat = input.from_stream(matrixFile);
            std::cout << mat << std::endl << std::endl;
            std::cout << mat.transpose();
        }
    }
}