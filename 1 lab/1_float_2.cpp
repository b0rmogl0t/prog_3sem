#include <iostream>
#include <iomanip>


int main() {
    float a = 0;

    unsigned long long value = 1;

    unsigned long long l = 1, r = 1;
    
    
    while (a + value + 1 != a + value) {
        value = r;
        l = r;
        r *= 2;
    }

    while (l + 1 != r) {
        unsigned long long m = (l + r) / 2;
        if (a + m + 1 != a + m) {
            l = m;
        } else {
            r = m;
        }
    }

    a = r - 1;
    std::cout << r - 1 << std::endl;
    std::cout << a << " == " << a + 1 << " | " << (a == (a + 1)) << std::endl;
    std::cout << std::endl;

    a = r;
    std::cout << r << std::endl;
    std::cout << a << " == " << a + 1 << " | " << (a == (a + 1)) << std::endl;
    
    

    return 0;
}
