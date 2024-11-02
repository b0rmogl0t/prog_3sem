#include <iostream>
#include <bitset>

void printBinary(unsigned int n) {


    
    
    for (int i = sizeof(n) * 8 - 1; i >= 0; --i) {
        
        std::cout << ((n >> i) & 1);
    }
    std::cout << std::endl;
}

int main() {
    unsigned int number;
    std::cout << "Введите число : ";
    std::cin >> number;

    printBinary(number);

    return 0;
}
