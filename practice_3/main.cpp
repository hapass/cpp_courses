#include <vector>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <iomanip>

class ValueValidator {
    public: virtual bool validate(float value) = 0;
};

class BitValueValidator: public ValueValidator {
    public: bool validate(float value);
};

bool BitValueValidator::validate(float value) {
    float ceil_value = ceilf(value);
    return ceil_value == value && (value == 0 || value == 1);
}

class IntegerValueValidator: public ValueValidator {
    public: bool validate(float value);
};

bool IntegerValueValidator::validate(float value) {
    float ceil_value = ceilf(value);
    return ceil_value == value && value >= -100 && value <= 100;
}

class FloatValueValidator: public ValueValidator {
    public: bool validate(float value);
};

bool FloatValueValidator::validate(float value) {
    return true;
}

enum class MatrixType {
    Undefined,
    Bit,
    Integer,
    Float
};

class MatrixFactory;

class Matrix {
    public:
        const int rows;
        const int columns;

        MatrixType type();

        float element(int row, int column) const;

        std::vector<float> row(int row) const;
        std::vector<float> column(int column) const;

        Matrix add(Matrix other) const;
        Matrix add(float value) const;

        Matrix multiply(Matrix other) const;
        Matrix multiply(float value) const;

        Matrix negate() const;
        Matrix transpose() const;

        friend class MatrixFactory;
    private:
        MatrixType matrixType;
        std::vector<float> matrix;

        Matrix(int rows, int columns);

        void element(int row, int column, float value);
        float dot(std::vector<float> first, std::vector<float> second) const;
};

Matrix::Matrix(int rows, int columns): rows(rows), columns(columns), matrix(rows * columns), matrixType(MatrixType::Undefined) {}

void Matrix::element(int row, int column, float value) {
    assert(row < rows && column < columns);
    matrixType = MatrixType::Undefined;
    matrix[row * columns + column] = value;
}

float Matrix::element(int row, int column) const {
    assert(row < rows && row >= 0 && column < columns && column >= 0);
    return matrix[row * columns + column];
}

MatrixType Matrix::type() {
    if(matrixType != MatrixType::Undefined) {
        return matrixType;
    }

    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            float value = element(row, column);

            if(matrixType != MatrixType::Float && matrixType != MatrixType::Integer && BitValueValidator().validate(value)) {
                matrixType = MatrixType::Bit;
                continue;
            }

            if(matrixType != MatrixType::Float && IntegerValueValidator().validate(value)) {
                matrixType = MatrixType::Integer;
                continue;
            }

            matrixType = MatrixType::Float;
        }
    }

    return matrixType;
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

Matrix Matrix::add(Matrix other) const {
    assert(rows == other.rows && columns == other.columns);

    Matrix result(rows, columns);
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            result.element(row, column, element(row, column) + other.element(row, column));
        }
    }

    return result;
}

Matrix Matrix::add(float value) const {
    Matrix result(rows, columns);
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            result.element(row, column, element(row, column) + value);
        }
    }

    return result;
}

Matrix Matrix::multiply(Matrix other) const {
    Matrix result(rows, other.columns);

    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < other.columns; column++) {
            result.element(row, column, Matrix::dot(Matrix::row(row), other.column(column)));
        }
    }

    return result;
}

Matrix Matrix::multiply(float value) const {
    Matrix result(rows, columns);
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            result.element(row, column, element(row, column) * value);
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
            result.element(column, row, element(row, column));
        }
    }

    return result;
}

std::ostream& operator<< (std::ostream& out, const std::vector<float>& vec) {
    for(auto i = vec.begin(); i < vec.end(); i++) {
        out << *i << out.fill();
    }
    return out;
}

std::ostream& operator<< (std::ostream& out, const Matrix& mat) {
    for(int row = 0; row < mat.rows; row++) {
        out << mat.row(row) << std::endl;
    }
    return out;
}

class MatrixFactory {
    private:
        ValueValidator& validator;
    public:
        MatrixFactory(ValueValidator& validator);
        Matrix from_stream(std::istream& in);
};

MatrixFactory::MatrixFactory(ValueValidator& validator): validator(validator) {}

Matrix MatrixFactory::from_stream(std::istream& in) {
    float rows;
    float columns;

    in >> rows >> columns;

    Matrix result(rows, columns);
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            float value;
            in >> value;

            assert(validator.validate(value));
            result.element(row, column, value);
        }
    }
    
    return std::move(result);
}

char matrix_char(MatrixType type) {
    char ch;
    switch(type) {
        case MatrixType::Bit: ch = '/';  break;
        case MatrixType::Integer: ch = '-'; break;
        case MatrixType::Float: ch = ' '; break;
        default: ch = '*'; break;
    }
    return ch;
}


int main() {
    std::ifstream matrixFile;
    matrixFile.open("matrix.txt");
    if(matrixFile.is_open()) {
        BitValueValidator validator;
        MatrixFactory factory(validator);

        Matrix one = factory.from_stream(matrixFile);
        Matrix other = one.transpose();

        std::cout << std::setfill(matrix_char(one.type())) << one << std::endl;
        std::cout << std::setfill(matrix_char(other.type())) << other << std::endl;

        Matrix result = one.multiply(other);
        std::cout << std::setfill(matrix_char(result.type())) << result << std::endl;

        std::cout << result.transpose().negate().add(10).multiply(2) << std::endl;
    }
}