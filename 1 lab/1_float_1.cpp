#include <iostream>
#include <bitset>



void printBinary(int value) {
    
    int bitCount = sizeof(int) * 8;

    
    for (int i = bitCount - 1; i >= 0; i--) {
        
        std::cout << ((value >> i) & 1);
    }
    std::cout << std::endl;
}


int main() {
    float a;

    std::cin >> a;

    int b = * (int *) &a;

    std::cout << b << std::endl;

    printBinary(b);
    return 0;
}
