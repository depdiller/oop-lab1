#include <iostream>
#include "lab1.h"


int main() {

    lab1::matrix m{};
    if (lab1::D_MatrixInit(m) == lab1::eof){
        std::cout << "Error initialising matrix, unsuitable data type" <<std::endl;
        return 1;
    }
    int choice;
    while ((choice = lab1::Dialog())){
        if (FunctionCall(choice, m))
            break;
    }
    printf("That's all. Bye!\n");
    lab1::Delete(m);
    return 0;
}