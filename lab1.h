#ifndef UNTITLED_LAB1_H
#define UNTITLED_LAB1_H

namespace lab1 {
    extern  const char *stateMsgs[];

    enum status {
        success = 0,
        impr_type = 1
    };

    struct node {
        int *nRows;
        int nColumns;
        int number;
        node *next;
    };

    struct  rows {
        int nRows;
        node *elINrow;
        rows *next;
    };

    struct matrix {
        int nOFr;
        int nOFc;
        int nOFnonzer;
        rows *head;
    };
    int a;
    std::cout << a;

    int getInt(int &a);
    int D_MatrixInit(matrix &m);
    int MatrixInit(matrix &m, int &nRows, int &nColumns);
    int D_ReadElems(matrix &m);
    int ReadElems(matrix &m, int nRow, int nColumn, int &number);
}

#endif