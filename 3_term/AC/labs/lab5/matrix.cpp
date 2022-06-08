#include "matrix.hpp"
#include <iostream>
#include <ctime>
#include <random>

int rand_int(int min, int max) {
    static std::random_device rd;
    static std::seed_seq seed{ rd(), static_cast<unsigned int>(time(nullptr)) };
    static std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}


Matrix::Matrix(const int& size_r, const int& size_c, const int& zero_flag) {
    _elements = new int* [size_r];
    for (int i = 0; i < size_r; i++) {
        _elements[i] = new int[size_c];
        for (int j = 0; j < size_c; j++)
            _elements[i][j] = (zero_flag) ? 0 : rand_int(0, 10);
    }
    rows = size_r;
    columns = size_c;
}

int Matrix::operator()(int index_r, int index_c) const {
    return _elements[index_r][index_c];
}

int& Matrix::operator()(int index_r, int index_c) {
    return _elements[index_r][index_c];
}

int* Matrix::operator()(int index_r) const {
    return _elements[index_r];
}

Matrix Matrix::operator+(const Matrix& M) const {
    Matrix res(this->rows, this->columns, true);

    if ((this->rows != M.rows) || (this->columns != M.columns))
        return *(this);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            res(i, j) = (*this)(i, j) + M(i, j);

    return res;
}

Matrix Matrix::operator-(const Matrix& M) const {
    Matrix res(this->rows, this->columns, true);

    if ((this->rows != M.rows) || (this->columns != M.columns))
        return *(this);

    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++)
            res(i, j) = (*this)(i, j) - M(i, j);

    return res;
}

bool Matrix::operator==(const Matrix& M) const {
    if (this->rows != M.rows || this->columns != M.columns) return false;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            if ((*this)(i, j) != M(i, j)) return false;
        }
    }
    return true;
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << _elements[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

Matrix matrixMultiply(const Matrix& A, const Matrix& B) {
    Matrix C(A.rows, B.columns, true);
    if ((A.rows != B.columns) || (A.columns != B.rows))
        return A;
    for (int i = 0; i < A.rows; i++)
        for (int j = 0; j < B.columns; j++)
            for (int k = 0; k < A.columns; k++)
                C(i, j) += A(i, k) * B(k, j);
    return C;
}

Matrix strassenAlgorithmStep(const Matrix& A, const Matrix& B, const int& size) {
    if (size <= 128) return matrixMultiply(A, B);
    Matrix A11(size / 2, size / 2, true);
    Matrix A12(size / 2, size / 2, true);
    Matrix A21(size / 2, size / 2, true);
    Matrix A22(size / 2, size / 2, true);
    Matrix B11(size / 2, size / 2, true);
    Matrix B12(size / 2, size / 2, true);
    Matrix B21(size / 2, size / 2, true);
    Matrix B22(size / 2, size / 2, true);
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            A11(i, j) = A(i, j);
            A12(i, j) = A(i, j + size / 2);
            A21(i, j) = A(i + size / 2, j);
            A22(i, j) = A(i + size / 2, j + size / 2);
            B11(i, j) = B(i, j);
            B12(i, j) = B(i, j + size / 2);
            B21(i, j) = B(i + size / 2, j);
            B22(i, j) = B(i + size / 2, j + size / 2);
        }
    }
    Matrix P = strassenAlgorithmStep(A11 + A22, B11 + B22, size / 2);
    Matrix Q = strassenAlgorithmStep(A21 + A22, B11, size / 2);
    Matrix R = strassenAlgorithmStep(A11, B12 - B22, size / 2);
    Matrix S = strassenAlgorithmStep(A22, B21 - B11, size / 2);
    Matrix T = strassenAlgorithmStep(A11 + A12, B22, size / 2);
    Matrix U = strassenAlgorithmStep(A21 - A11, B11 + B12, size / 2);
    Matrix V = strassenAlgorithmStep(A12 - A22, B21 + B22, size / 2);
    A11 = P + S - T + V;
    A12 = R + T;
    A21 = Q + S;
    A22 = P + R - Q + U;
    Matrix C(size, size, true);
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            C(i, j) = A11(i, j);
            C(i, j + size / 2) = A12(i, j);
            C(i + size / 2, j) = A21(i, j);
            C(i + size / 2, j + size / 2) = A22(i, j);
        }
    }
    return C;
}
Matrix strassenAlgorithm(const Matrix& A, const Matrix& B) {
    if ((A.rows != B.columns) || (A.columns != B.rows))
        return A;
    int new_size = 1, curr_size = (A.rows < A.columns) ? A.columns : A.rows;
    while (new_size < curr_size)
        new_size *= 2;
    Matrix new_A(new_size, new_size, true);
    Matrix new_B(new_size, new_size, true);
    for (int i = 0; i < A.rows; i++)
        std::copy(A(i) + 0, A(i) + A.columns, new_A(i));
    for (int i = 0; i < B.rows; i++)
        std::copy(B(i) + 0, B(i) + B.columns, new_B(i));
    Matrix res(A.rows, B.columns, true);
    Matrix sub_res = strassenAlgorithmStep(new_A, new_B, new_size);
    for (int i = 0; i < A.rows; i++)
        std::copy(sub_res(i) + 0, sub_res(i) + B.columns, res(i));
    return res;
}