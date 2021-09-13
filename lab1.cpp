#include <iostream>
#include "lab1.h"

namespace lab1 {
    const char *stateMsgs[] = {"Success", "Improper type"};

    int getInt(int &a) {
        std::cin >> a;
        if (!std::cin.good())
            return impr_type;
        return success;
    }

    int D_MatrixInit(matrix &m) {
        int stateIndic;
        int nRows, nColumns;
        std::cout << "Hello, enter the size of matrix: " << std:: endl
        << "Number of rows: ";
        if (getInt(nRows))
            return impr_type;
        std::cout << std::endl << "Number of columns: ";
        if (getInt(nColumns))
            return impr_type;
        stateIndic = MatrixInit(m, nRows, nColumns);
        std::cout << stateMsgs[stateIndic];
        return  success;
    }

    int MatrixInit(matrix &m, int &nRows, int &nColumns) {
        rows *head;
        head = new rows;
        head->nRows = nRows;
        m.nOFr = nRows;
        m.nOFc = nColumns;
        m.head = head;
        return success;
    }

    int D_ReadElems(matrix &m) {
        int stateIndic;
        int currRow, currColmn, currNum;
        std::cout << "Ok, now enter elements of your matrix." << std::endl;
        std::cout << "Enter the row of element: " << std::endl;
        if (getInt(currRow))
            return impr_type;
        std::cout << "Enter the column of element: " << std::endl;
        if (getInt(currColmn))
            return impr_type;
        std::cout << "Enter number to save in matrix: " << std::endl;
        if (getInt(currNum))
            return impr_type;
        stateIndic = ReadElems(m, currRow, currColmn, currNum);
        std::cout << stateMsgs[stateIndic];
        return success;
    }

    int ReadElems(matrix &m, int nRow, int nColumn, int &number) {

    }
}