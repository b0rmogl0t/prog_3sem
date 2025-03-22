#include "Matrix.hpp"

// Конструктор
template<typename T>
Matrix<T>::Matrix(unsigned rows, unsigned cols, T value)
    : data(rows * cols, value), _cols(cols), _rows(rows) {}

// Создание единичной матрицы
template<typename T>
Matrix<T> Matrix<T>::Identity(unsigned rows, unsigned cols) {
    if (rows != cols)
        throw std::invalid_argument("Identity matrix must be square.");
    Matrix m(rows, cols);
    for (unsigned i = 0; i < rows; ++i)
        m(i, i) = T(1);
    return m;
}

// Перестановка строк
template<typename T>
void Matrix<T>::swapRows(unsigned row1, unsigned row2) {
    if (row1 >= _rows || row2 >= _rows)
        throw std::out_of_range("Row index out of range.");
    for (unsigned col = 0; col < _cols; ++col)
        std::swap((*this)(row1, col), (*this)(row2, col));
}

// Добавление строки
template<typename T>
void Matrix<T>::addRows(unsigned targetRow, unsigned sourceRow, T multiplier) {
    if (targetRow >= _rows || sourceRow >= _rows)
        throw std::out_of_range("Row index out of range.");
    for (unsigned col = 0; col < _cols; ++col)
        (*this)(targetRow, col) += multiplier * (*this)(sourceRow, col);
}

// Умножение строки
template<typename T>
void Matrix<T>::multiplyRow(unsigned row, T multiplier) {
    if (row >= _rows)
        throw std::out_of_range("Row index out of range.");
    for (unsigned col = 0; col < _cols; ++col)
        (*this)(row, col) *= multiplier;
}

// Транспонирование
template<typename T>
void Matrix<T>::transpose() {
    for (unsigned i = 0; i < _rows; i++) {
        for (unsigned j = 0; j < _cols; j++) {
            if (i == j) continue;
            std::swap((*this)(i, j), (*this)(j, i));
        }
    }
}

// Получение матрицы с определённым детерминантом
template<typename T>
Matrix<T> Matrix<T>::getSpecificDeterminant(unsigned n, T determinant) {
    Matrix m(n, n);
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if (i == j) {
                m(i, j) = (i == 0) ? determinant : T(1);
            } else {
                m(i, j) = (i < j) ? static_cast<T>(rand() % 10 + 1) : T(0);
            }
        }
    }
    return m;
}

// Доступ к элементам
template<typename T>
T& Matrix<T>::operator()(unsigned row, unsigned col) {
    return data[row * _cols + col];
}

template<typename T>
T Matrix<T>::operator()(unsigned row, unsigned col) const {
    return data[row * _cols + col];
}

// Вычисление детерминанта
template<typename T>
T determinant(const Matrix<T>& matrix) {
    if (matrix.rows() != matrix.cols()) {
        throw std::logic_error("Determinant is only defined for square matrices.");
    }
    unsigned n = matrix.rows();
    Matrix<T> m = matrix;
    T det = 1;
    for (unsigned i = 0; i < n; ++i) {
        if (m(i, i) == T(0)) {
            bool swapped = false;
            for (unsigned j = i + 1; j < n; ++j) {
                if (m(j, i) != T(0)) {
                    for (unsigned k = 0; k < n; ++k)
                        std::swap(m(i, k), m(j, k));
                    det = -det;
                    swapped = true;
                    break;
                }
            }
            if (!swapped) return T(0);
        }
        T pivot = m(i, i);
        det *= pivot;
        for (unsigned j = 0; j < n; ++j)
            m(i, j) /= pivot;
        for (unsigned j = i + 1; j < n; ++j) {
            T factor = m(j, i);
            for (unsigned k = 0; k < n; ++k)
                m(j, k) -= factor * m(i, k);
        }
    }
    return det;
}
