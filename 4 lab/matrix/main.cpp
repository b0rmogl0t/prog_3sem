#include "Matrix.hpp"
#include <iostream>

int main() {
    Matrix<double> mat = Matrix<double>::getSpecificDeterminant(3, 10.0);
    mat.print();
    std::cout << "Determinant: " << determinant(mat) << std::endl;
    return 0;
}
