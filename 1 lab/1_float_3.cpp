#include <iostream>
#include <iomanip>

int main() {
    
    float a = 1.0f;
    float b = 1e20f; 
    float c = -1e20f; 
 
    float result1 = (a + b) + c;
    float result2 = a + (b + c);


    std::cout << std::fixed << std::setprecision(10);
    std::cout << "(a + b) + c = " << result1 << std::endl;
    std::cout << "a + (b + c) = " << result2 << std::endl;

    
}
