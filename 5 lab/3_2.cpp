#include <array>
#include <iostream>

// Шаблонная функция вычисления элемента линейной рекуррентной последовательности
template <size_t N, size_t M>
constexpr int linear_recurrence(const std::array<int, N>& coeffs, const std::array<int, N>& initial, size_t m) {
    std::array<int, M + 1> sequence{};

    // Копируем начальные значения
    for (size_t i = 0; i < N; ++i) {
        sequence[i] = initial[i];
    }

    // Вычисляем элементы до m
    for (size_t i = N; i <= m; ++i) {
        int value = 0;
        for (size_t j = 0; j < N; ++j) {
            value += coeffs[j] * sequence[i - j - 1];
        }
        sequence[i] = value;
    }

    return sequence[m];
}

// Пример использования: Фибоначчи
int main() {
    constexpr std::array<int, 2> fib_coeffs = {1, 1};   // x_n = x_{n-1} + x_{n-2}
    constexpr std::array<int, 2> fib_init = {0, 1};     // x_0 = 0, x_1 = 1
    constexpr size_t m = 10;

    constexpr int result = linear_recurrence<2, m>(fib_coeffs, fib_init, m);
    std::cout << "x_" << m << " = " << result << std::endl;  // Ожидается: 55

    return 0;
}
