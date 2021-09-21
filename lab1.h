#ifndef UNTITLED_LAB1_H
#define UNTITLED_LAB1_H
#include <climits>

namespace lab1 {
    extern  const char *stateMsgs[];

    enum status {
        success = 0,
        exceeded_size = 2,
        alrd_exist = 3,
        eof = 4
    };

    struct node {
        int nColumn;
        int number;
        node *next;
    };

    struct  rows {
        int status; //0 positive or 1 negative
        node *listOfNodes;
        rows *next;
    };

    struct matrix {
        int nOfRows;
        int nOfColumns;
        rows *firstRow;
    };

    struct vector {
        node* firstNode;
    };


    int D_MatrixInit(matrix &m);
    int D_ReadElems(matrix &m);
    int D_Print(matrix &m);
    int D_Free(matrix &m);
    int D_Vector(matrix &m);

    int MatrixInit(matrix &m, int &nRows, int &nColumns);
    int ReadElems(matrix &m, int nRow, int nColumn, int &number);
    int Print(matrix &m);
    int Delete(matrix &m);
    int Vector(matrix &m);

    int FunctionCall(int , matrix &);
    vector *InitVector(matrix &);
    node *CheckAndSend(matrix &, int, int, int);
    int Dialog();
    int GetInt(int &a);
    int GetIntZero(int &);
    int GetIntNegative(int &);
    int Free(matrix &);
}

#endif