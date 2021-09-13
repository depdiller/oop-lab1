#include <iostream>
#include "lab1.h"


int main() {
    lab1::matrix m;
    if (lab1::D_MatrixInit(m) ){
        std::cout << "Error initialising matrix, unsuitable data type" <<
        std::endl;
    }
    if (lab1::D_ReadElems(m)) {
        std::cout << "Error initialising matrix, unsuitable data type" <<
        std::endl;
    }

    return 0;
}