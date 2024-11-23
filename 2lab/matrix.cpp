#include <iostream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cstdlib>  // Для rand()
#include <ctime>    // Для srand()

template<typename T>
class Matrix {
    std::vector<T> data; // Линейное хранение данных
    unsigned _cols, _rows;

public:
    // Конструктор: создание матрицы с заданным значением
    Matrix(unsigned rows, unsigned cols, T value = T())
        : data(rows * cols, value), _cols(cols), _rows(rows) {}

    // Статический метод: создание единичной матрицы
    static Matrix Identity(unsigned rows, unsigned cols) {
        if (rows != cols)
            throw std::invalid_argument("Identity matrix must be square.");
        Matrix m(rows, cols);
        for (unsigned i = 0; i < rows; ++i)
            m(i, i) = T(1);
        return m;
    }

    // Статический метод: создание матрицы с заданным детерминантом
    static Matrix getSpecificDeterminant(unsigned n, T determinant) {
    Matrix m(n, n); // Создаём пустую матрицу

    // Заполнение верхнедиагональной матрицы
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            if (i == j) {
                // Заполняем диагональ
                m(i, j) = (i == 0) ? determinant : T(1); // Первый элемент диагонали равен determinant
            } else if (i < j) {
                // Заполняем элементы выше диагонали случайными числами
                m(i, j) = static_cast<T>(rand() % 10 + 1); // Случайные числа от 1 до 10
            } else {
                // Элементы ниже диагонали равны нулю
                m(i, j) = T(0);
            }
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

    // Вывод матрицы (для отладки)
    void print() const {
        for (unsigned i = 0; i < _rows; ++i) {
            for (unsigned j = 0; j < _cols; ++j)
                std::cout << std::setw(8) << (*this)(i, j) << " ";
            std::cout << "\n";
        }
    }

    // Метод вычисления детерминанта
    T determinant() const {
        if (_rows != _cols)
            throw std::logic_error("Determinant is only defined for square matrices.");

        Matrix m = *this;  // Создаём копию для работы
        T det = 1;

        for (unsigned i = 0; i < _rows; ++i) {
            // Пивотинг: ищем ненулевой элемент на диагонали
            if (m(i, i) == T(0)) {
                bool swapped = false;
                for (unsigned j = i + 1; j < _rows; ++j) {
                    if (m(j, i) != T(0)) {
                        for (unsigned k = 0; k < _cols; ++k)
                            std::swap(m(i, k), m(j, k));
                        det = -det;
                        swapped = true;
                        break;
                    }
                }
                if (!swapped) return T(0);  // Детерминант равен нулю
            }

            // Нормализация строки
            T pivot = m(i, i);
            det *= pivot;
            for (unsigned j = 0; j < _cols; ++j)
                m(i, j) /= pivot;

            // Обнуление элементов ниже текущей строки
            for (unsigned j = i + 1; j < _rows; ++j) {
                T factor = m(j, i);
                for (unsigned k = 0; k < _cols; ++k)
                    m(j, k) -= factor * m(i, k);
            }
        }

        return det;
    }
};

int main() {
    // Инициализируем генератор случайных чисел
    std::srand(std::time(nullptr));

    // Задаём размер матрицы и детерминант
    const unsigned size = 5;
    const double determinant = 27.0;

    // Генерация верхнедиагональной матрицы с заданным детерминантом
    Matrix<double> m = Matrix<double>::getSpecificDeterminant(size, determinant);

    // Вывод матрицы
    std::cout << "Generated upper triangular matrix:\n";
    m.print();

    // Проверка детерминанта
    std::cout << "\nCalculated determinant: " << m.determinant() << "\n";

    return 0;
}
