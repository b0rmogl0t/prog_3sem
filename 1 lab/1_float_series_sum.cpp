#include <iostream>
#include <limits>
#include <cmath>

int main() {
    
    float sum = 0.0f;  
    int k = 1;         

   
    while (true) {
        float term = 1.0f / k;  
        float new_sum = sum + term; 

        
        if (new_sum == sum) {
            std::cout << "первый элемент (номер " << k << "), не меняющий сумму: "
                      << term << "\n";
            break;
        }
        sum = new_sum;  
        k++;            
    }

    
    int n = k + 100;
    float sum_forward = 0.0f; // Сумма вперед
    float sum_backward = 0.0f; // Сумма назад

    // Суммируем вперед
    for (int i = 1; i <= n; ++i) {
        sum_forward += 1.0f / i;
    }

    // Суммируем назад
    for (int i = n; i >= 1; --i) {
        sum_backward += 1.0f / i;
    }

    // Выводим результаты
    std::cout << "сумма ряда от 1 до " << n << " (вперед): "
              << sum_forward << "\n";
    std::cout << "сумма ряда от " << n << " до 1 (назад): "
              << sum_backward << "\n";

    return 0;
}
