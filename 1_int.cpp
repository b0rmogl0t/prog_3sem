#include <iostream>
#include <bitset>



// Функция для вывода побитового представления числа
void printBinary(int value) {
    
    int bitCount = sizeof(int) * 8;

    
    for (int i = bitCount - 1; i >= 0; i--) {
        
        std::cout << ((value >> i) & 1);
    }
    std::cout << std::endl;
}

int main() {
    int positive = 3;
    int negative = -3;

    std::cout << "3: ";
    printBinary(positive);

    std::cout << "-3: ";
    printBinary(negative);

    std::cout << "INT_MAX: ";
    printBinary(INT_MAX);

    std::cout << "INT_MAX + 1: ";
    printBinary(INT_MAX + 1);

    return 0;
}
