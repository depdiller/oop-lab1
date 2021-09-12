#ifndef UNTITLED_LAB1_H
#define UNTITLED_LAB1_H

namespace lab1 {
    struct listOfRows {
        int nOfRow;
        listOfRows *next;
    };

    struct listNonZ {
        int index;
        listNonZ *next;
    };

    struct matrix {
        int nonZeros;
        int columns;
        int string;
        listOfRows *head;
    };
    int getInt(int &a);
}

#endif