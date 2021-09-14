#include <iostream>
#include "lab1.h"

namespace lab1 {
    const char *stateMsgs[] = {"Success", "Improper type", "You should use non zero ints", "You cannot use negative ints",
                               "Exceeded the size of matrix", "You already have element at this position"};

    int getInt(int &a) {
        std::cin >> a;
        if (!std::cin.good())
            return impr_type;
        else if (a == 0)
            return non_zero;
        else if (a < 0)
            return less_zero;
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
        rows *tmp = new rows();
        tmp->next = nullptr;
        tmp->listOfNodes = nullptr;
        tmp->nOfRow = 1;
        m.nOfRows = nRows;
        m.nOfColumns = nColumns;
        m.firstRow = tmp;
        for (int i = 2; i <= nRows; ++i) {
            rows *tmp1 = new rows;
            tmp1->nOfRow = i;
            tmp1->listOfNodes = nullptr;
            tmp1->next = nullptr;
        }
        return success;
    }

    int D_ReadElems(matrix &m) {
        int stateIndic;
        int currRow, currColumn, currNum;
        std::cout << "Ok, now enter elements of your matrix." << std::endl;
        std::cout << "Enter the row of element: " << std::endl;
        if (getInt(currRow))
            return impr_type;
        std::cout << "Enter the column of element: " << std::endl;
        if (getInt(currColumn))
            return impr_type;
        std::cout << "Enter number to save in matrix: " << std::endl;
        if (getInt(currNum))
            return impr_type;
        stateIndic = ReadElems(m, currRow, currColumn, currNum);
        std::cout << stateMsgs[stateIndic];
        return success;
    }



    int ReadElems(matrix &m, int nRow, int nColumn, int &number) {
        node *tmp, *recent;
        try {
            tmp = CheckAndSend(m, nRow, nColumn);
        }
        catch (int sizeExeption) {
            return exceeded_size;
        }
        if (tmp == nullptr)
            return alrd_exist;
        else {
            recent = new node;
            recent->nColumn = nColumn;
            recent->nRow = nRow;
            recent->number = number;
            if (tmp->next == nullptr) {
                recent->next = nullptr;
                tmp->next = recent;
            }
            else {
                recent->next = tmp->next;
                tmp->next = recent;
            }
        }
        return success;
    }

    // если элемент нет, то возвращается ссылка на последний элемент,
    // если элемент есть, возвращается nullptr
    node *CheckAndSend(matrix &m, int nRow, int nColumn) {
        rows *tmp1 = m.firstRow;
        if (nRow > m.nOfRows || nColumn > m.nOfColumns)
            throw exceeded_size;
        for (int i = 1; i < nRow; ++i) {
            tmp1 = tmp1->next;
        }
        node *tmp2 = tmp1->listOfNodes;
        while (tmp2 != nullptr) {
            if (tmp2->nColumn < nColumn && (tmp2->next == nullptr || tmp2->next->nColumn > nColumn))
                return tmp2;
            tmp2 = tmp2->next;
        }
        return nullptr;
    }
}