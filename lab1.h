#ifndef UNTITLED_LAB1_H
#define UNTITLED_LAB1_H

namespace lab1 {
    extern  const char *stateMsgs[];

    enum status {
        success = 0,
        impr_type = 1,
        non_zero = 2,
        less_zero = 3,
        exceeded_size = 4,
        alrd_exist = 5
    };

    struct node {
        int nRow;
        int nColumn;
        int number;
        node *next;
    };

    struct  rows {
        int nOfRow;
        node *listOfNodes;
        rows *next;
    };

    struct matrix {
        int nOfRows;
        int nOfColumns;
        int nOfNonZero;
        rows *firstRow;
    };


    int getInt(int &a);
    int D_MatrixInit(matrix &m);
    int MatrixInit(matrix &m, int &nRows, int &nColumns);
    int D_ReadElems(matrix &m);
    int ReadElems(matrix &m, int nRow, int nColumn, int &number);
    node *CheckAndSend(matrix &, int, int);
}

#endif