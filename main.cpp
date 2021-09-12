#include <iostream>
#include "lab1.h"


int main() {
    int n, m;
    lab1::matrix f{};
    std::cout << "Enter the size of matrix (n, m): " << std::endl;
    std::cin >> n >> m;

    f.nonZeros = n*m;
    f.columns = n;
    f.string = m;
}