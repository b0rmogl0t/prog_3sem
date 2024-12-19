#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cstdlib>  
#include <ctime>    
#include <cmath>    

template<typename T>
class Matrix {
    std::vector<T> data; 
    unsigned _cols, _rows; 

public:
    // Конструктор: создание матрицы с заданным значением
    Matrix(unsigned rows, unsigned cols, T value = T())
        : data(rows * cols, value), _cols(cols), _rows(rows) {}

   
    static Matrix Identity(unsigned rows, unsigned cols) {
        if (rows != cols)
            throw std::invalid_argument("Identity matrix must be square.");
        Matrix m(rows, cols);
        for (unsigned i = 0; i < rows; ++i)
            m(i, i) = T(1);
        return m;
    }

    // Метод перестановки строк
    void swapRows(unsigned row1, unsigned row2) {
        if (row1 >= _rows || row2 >= _rows)
            throw std::out_of_range("Row index out of range.");
        for (unsigned col = 0; col < _cols; ++col)
            std::swap((*this)(row1, col), (*this)(row2, col));
    }

    // Метод сложения строк
    void addRows(unsigned targetRow, unsigned sourceRow, T multiplier) {
        if (targetRow >= _rows || sourceRow >= _rows)
            throw std::out_of_range("Row index out of range.");
        for (unsigned col = 0; col < _cols; ++col)
            (*this)(targetRow, col) += multiplier * (*this)(sourceRow, col);
    }

    // Метод умножения строки на число
    void multiplyRow(unsigned row, T multiplier) {
        if (row >= _rows)
            throw std::out_of_range("Row index out of range.");
        for (unsigned col = 0; col < _cols; ++col)
            (*this)(row, col) *= multiplier;
    }

    // Метод сложения столбцов
    void addCols(unsigned targetCol, unsigned sourceCol, T multiplier) {
        if (targetCol >= _cols || sourceCol >= _cols)
            throw std::out_of_range("Col index out of range.");
        for (unsigned row = 0; row < _rows; ++row)
            (*this)(row, targetCol) += multiplier * (*this)(row, sourceCol);
    }

    // Метод умножения столбца на число
    void multiplyCol(unsigned col, T multiplier) {
        if (col >= _cols)
            throw std::out_of_range("Col index out of range.");
        for (unsigned row = 0; row < _rows; ++row)
            (*this)(row, col) *= multiplier;
    }

    void transpose() {
        for (unsigned i = 0; i < _rows; i++) {
            for (unsigned j = 0; j < _cols; j++) {
                if (i == j) continue;
                std::swap((*this)(i, j), (*this)(j, i));
            }
        }
    }

    // Статический метод: создание матрицы с заданным детерминантом
    static Matrix getSpecificDeterminant(unsigned n, T determinant) {
        Matrix m(n, n); // Создаём пустую матрицу

    
        for (unsigned i = 0; i < n; ++i) {
            for (unsigned j = 0; j < n; ++j) {
                if (i == j) {
                    
                    m(i, j) = (i == 0) ? determinant : T(1); 
                } else if (i < j) {
                    
                    m(i, j) = static_cast<T>(rand() % 10 + 1); 
                } else {
                    
                    m(i, j) = T(0);
                }
            }
        }

        for (int _ = 0; _ < 2 * n; _++) {
            int action = rand() % 6;
            if (action == 0) {
                m.transpose();
            } else {
                unsigned row1 = rand() % n;
                unsigned row2 = rand() % n;

                if (row1 == row2) {
                    if (row1 > 0) {
                        row1--;
                    } else {
                        row1++;
                    }
                }

                m.swapRows(row1, row2);
            }
        }

        return m;
    }

    // Селекторы
    unsigned rows() const { return _rows; }
    unsigned cols() const { return _cols; }

    // Доступ к элементам
    T& operator()(unsigned row, unsigned col) {
        if (row >= _rows || col >= _cols)
            throw std::out_of_range("Matrix index out of range.");
        return data[row * _cols + col];
    }

    T operator()(unsigned row, unsigned col) const {
        if (row >= _rows || col >= _cols)
            throw std::out_of_range("Matrix index out of range.");
        return data[row * _cols + col];
    }

 
    void print() const {
        for (unsigned i = 0; i < _rows; ++i) {
            for (unsigned j = 0; j < _cols; ++j)
                std::cout << std::setw(8) << (*this)(i, j) << " ";
            std::cout << "\n";
        }
    }
};


template <typename T>
T determinant(const Matrix<T>& matrix) {
    // Проверяем, что матрица квадратная
    if (matrix.rows() != matrix.cols()) {
        throw std::logic_error("Determinant is only defined for square matrices.");
    }

    unsigned n = matrix.rows();
    Matrix<T> m = matrix;  // Создаём копию матрицы, чтобы не модифицировать исходную
    T det = 1;

    for (unsigned i = 0; i < n; ++i) {
        // Пивотинг: ищем ненулевой элемент на диагонали
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
            if (!swapped) return T(0);  // Если нельзя найти ненулевой элемент, детерминант равен 0
        }


        T pivot = m(i, i);
        det *= pivot;
        for (unsigned j = 0; j < n; ++j)
            m(i, j) /= pivot;

        // Обнуление элементов ниже текущей строки
        for (unsigned j = i + 1; j < n; ++j) {
            T factor = m(j, i);
            for (unsigned k = 0; k < n; ++k)
                m(j, k) -= factor * m(i, k);
        }
    }

    return det;
}

// Тесты
void run_tests() {
    std::srand(std::time(nullptr)); 

    // Определяем размеры матриц и их ожидаемые детерминанты
    struct TestCase {
        unsigned size;
        double determinant_value;
    } test_cases[] = {
        {5, 25.0},     // Матрица 5x5 с детерминантом 25
        {50, 50.0},    // Матрица 50x50 с детерминантом 50
        {200, 100.0}   // Матрица 200x200 с детерминантом 100
    };


    for (const auto& test : test_cases) {
        
        Matrix<double> m = Matrix<double>::getSpecificDeterminant(test.size, test.determinant_value);

        // Вычисление детерминанта
        double calculated_determinant = determinant(m);

        

        // Вывод результатов
        std::cout << "Test for matrix " << test.size << "x" << test.size << ":\n";
        std::cout << "  Expected determinant: " << test.determinant_value << "\n";
        std::cout << "  Calculated determinant: " << calculated_determinant << "\n";
       
    }
}


int main() {
    run_tests();

    return 0;
}
