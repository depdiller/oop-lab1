#include <iostream>
#include "lab1.h"

namespace lab1 {
    const char *stateMsgs[] = {"Success", "Improper type", "Exceeded the size of matrix", "You already have element "
                                                                                          "at this position", "End of"
                                                                                                              " File"};
    const char *msgs[] = {"0. Quit", "1. Add element to matrix", "2. Print matrix", "3. Vector", "4. Free"};
    int (*functPtr[])(matrix &) = {nullptr, D_ReadElems, D_Print, D_Vector, D_Free};
    const int numbMsgs = sizeof(msgs) / sizeof(msgs[0]);

    int FunctionCall(int choice, matrix &m) {
        if (functPtr[choice](m) == eof) {
            return eof;
        }
        return success;
    }

    int Dialog() {
        int choice;
        const char *errmsg = "";
        do {
            std::cout << errmsg << std::endl;
            errmsg = "There is no such command.\n";
            for(auto & msg : msgs) {
                std::cout << msg << "   ";
            }
            std::cout << std::endl;
            if (GetIntZero(choice)) {
                choice = 0;
            }
        } while (choice < 0 || choice > numbMsgs - 1);
        return choice;
    }

    int D_MatrixInit(matrix &m) {
        int stateIndic;
        int nRows, nColumns;
        std::cout << "Hello, enter the size of matrix, number of (rows, columns): ";
        if (GetInt(nRows) != eof && GetInt(nColumns) != eof) {
            stateIndic = MatrixInit(m, nRows, nColumns);
        }
        else
            return eof;
        std::cout <<stateMsgs[stateIndic]<< std::endl;
        return success;
    }

    int MatrixInit(matrix &m, int &nRows, int &nColumns) {
        rows *tmp = new rows();
        tmp->next = nullptr;
        tmp->listOfNodes = nullptr;
        m.nOfRows = nRows;
        m.nOfColumns = nColumns;
        m.firstRow = tmp;
        for (int i = 2; i <= nRows; ++i) {
            rows *tmp1 = new rows;
            tmp1->listOfNodes = nullptr;
            tmp1->next = nullptr;
            tmp1->status = 0;
            tmp->next = tmp1;
            tmp = tmp->next;
        }
        return success;
    }

    int D_ReadElems(matrix &m) {
        int stateIndic;
        int currRow, currColumn, currNum;
        std::cout <<"Enter parameters of new element (row, column): ";
        if (GetInt(currRow) != eof && GetInt(currColumn) != eof) {
            std::cout <<"Enter number to save in matrix: "<< std::endl;
            if (GetIntNegative(currNum))
                return eof;
            else
                stateIndic = ReadElems(m, currRow, currColumn, currNum);
        }
        else
            return eof;
        std::cout <<stateMsgs[stateIndic]<< std::endl;
        return success;
    }


    int ReadElems(matrix &m, int nRow, int nColumn, int &number) {
        node *tmp, *recent;
        try {
            tmp = CheckAndSend(m, nRow, nColumn, number);
        }
        catch (std::out_of_range &i) {
            return exceeded_size;
        }
        if (tmp == nullptr)
            return alrd_exist;
        // if there were no elements in the row
        else if (tmp->nColumn == -1) {
            tmp->nColumn = nColumn;
            tmp->number = number;
        }
        //
        else {
            recent = new node;
            recent->nColumn = nColumn;
            recent->number = number;

            if (tmp->nColumn > nColumn) {
                rows *pLine = m.firstRow;
                for (int i = 1; i < nRow; ++i) {
                    pLine = pLine->next;
                }
                pLine->listOfNodes = recent;
                recent->next = tmp;
            }
            else if (tmp->next == nullptr) {
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

    // ???????? ?????????????? ??????, ???? ???????????????????????? ???????????? ???? ?????????????????? ??????????????,
    // ???????? ?????????????? ????????, ???????????????????????? nullptr
    node *CheckAndSend(matrix &m, int nRow, int nColumn, int number) {
        rows *tmp1 = m.firstRow;
        if (nRow > m.nOfRows || nColumn > m.nOfColumns)
            throw std::out_of_range("Matrix size is limited");
        for (int i = 1; i < nRow; ++i) {
            tmp1 = tmp1->next;
        }
        node *tmp2 = tmp1->listOfNodes;
        // if there is no elements in a row
        if (tmp2 == nullptr) {
            node *new_el = new node;
            new_el->next = nullptr;
            new_el->nColumn = -1;
            tmp1->listOfNodes = new_el;
            if (number < 0 && tmp1->status == 0)
                tmp1->status = 1;
            return tmp1->listOfNodes;
        }
        //
        while (tmp2 != nullptr) {
            if (tmp2->nColumn < nColumn && (tmp2->next == nullptr || tmp2->next->nColumn > nColumn)) {
                if (number < 0 && tmp1->status == 0)
                    tmp1->status = 1;
                return tmp2;
            }
            else if (tmp2->nColumn > nColumn){
                if (number < 0 && tmp1->status == 0)
                    tmp1->status = 1;
                return  tmp2;
            }
            tmp2 = tmp2->next;
        }
        return nullptr;
    }

    int D_Print(matrix &m) {
        int stateIndic;
        stateIndic = Print(m);
        std::cout <<stateMsgs[stateIndic]<< std::endl;
        return success;
    }

    int Print(matrix &m) {
        rows *tmp1 = m.firstRow;
        for (int i = 0; i < m.nOfRows; ++i) {
            node *tmp2 = tmp1->listOfNodes;
            for (int j = 1; j <= m.nOfColumns; ++j) {
                if (tmp2 != nullptr && j == tmp2->nColumn) {
                    std::cout << tmp2->number << " ";
                    tmp2 = tmp2->next;
                }
                else
                    std::cout << 0 << " ";
            }
            std::cout << std::endl;
            tmp1 = tmp1->next;
        }
        return success;
    }

    int D_Vector(matrix &m) {
        int stateIndic;
        stateIndic = Vector(m);
        std::cout <<stateMsgs[stateIndic]<< std::endl;
        return success;
    }

    int Vector(matrix &m) {
        vector *v = InitVector(m);
        // print
        node *tmp = v->firstNode;
        for (int i = 0; i < m.nOfRows; ++i) {
            std::cout << tmp->number << std::endl;
            tmp = tmp->next;
        }
        std::cout << std::endl;
        // delete
        node *delNode, *thruNodes = v->firstNode;
        while (thruNodes != nullptr) {
            delNode = thruNodes;
            thruNodes = thruNodes->next;
            delNode->next = nullptr;
            delete delNode;
        }
        delete v;
        return success;
    }

    vector *InitVector(matrix &m) {
        int numFromVector;
        auto *v = new vector;
        rows *rowSearch = m.firstRow;
        node *nodeSearch, *tmp;
        for (int i = 1; i <= m.nOfRows; ++i) {
            node *newInVector = new node;
            nodeSearch = rowSearch->listOfNodes;
            if (rowSearch->status == 0) {
                if (nodeSearch == nullptr || nodeSearch->nColumn != 1)
                    numFromVector = 0;
                else
                    numFromVector = nodeSearch->number;
            }
            else {
                while (nodeSearch != nullptr) {
                    if (nodeSearch->next == nullptr && nodeSearch->nColumn == m.nOfRows) {
                        numFromVector = nodeSearch->number;
                    }
                    else if (nodeSearch->next == nullptr && nodeSearch->nColumn != m.nOfRows){
                        numFromVector = 0;
                    }
                    nodeSearch = nodeSearch->next;
                }
            }
            newInVector->nColumn = i;
            newInVector->number = numFromVector;
            newInVector->next = nullptr;
            if (i == 1) {
                v->firstNode = newInVector;
                tmp = v->firstNode;
            }
            else {
                tmp->next = newInVector;
                tmp = tmp->next;
            }
            rowSearch = rowSearch->next;
        }
        return v;
    }

    int GetInt(int &a) {
        int indic;
        do {
            std::cin >> a;
            indic = 1;
            if (std::cin.eof())
                indic = -1;
            else if (!std::cin.good() || a == 0 || a < 0) {
                std::cout << "Incorrect input. Try again" << std::endl;
                indic = 0;
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
        } while (indic == 0);
        return indic < 0 ? eof : success;
    }

    int GetIntZero(int &a) {
        int indic ;
        do {
            std::cin >> a;
            indic = 1;
            if (std::cin.eof())
                indic = -1;
            else if (!std::cin.good() || a < 0) {
                std::cout << "Incorrect input. Try again" << std::endl;
                indic = 0;
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
        } while (indic == 0);
        return indic < 0 ? eof : success;
    }

    int GetIntNegative(int &a) {
        int indic ;
        do {
            std::cin >> a;
            indic = 1;
            if (std::cin.eof())
                indic = -1;
            else if (!std::cin.good() || a == 0) {
                std::cout << "Incorrect input. Try again" << std::endl;
                indic = 0;
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
            }
        } while (indic == 0);
        return indic < 0 ? eof : success;
    }

    int D_Free(matrix &m) {
        int stateIndic;
        stateIndic = Free(m);
        std::cout <<stateMsgs[stateIndic]<< std::endl;
        return success;
    }

    int Delete(matrix &m) {
        node *delNode;
        rows *thruRows = m.firstRow, *delRow;
        for (int i = 0; i < m.nOfRows; ++i) {
            node *thruNodes = thruRows->listOfNodes;
            if (thruNodes != nullptr)
                thruRows->listOfNodes = nullptr;
            while (thruNodes != nullptr) {
                delNode = thruNodes;
                thruNodes = thruNodes->next;
                delNode->next = nullptr;
                delete delNode;
            }
            delRow = thruRows;
            thruRows = thruRows->next;
            delRow->next = nullptr;
            delete delRow;
        }
        return success;
    }

    int Free(matrix &m) {
        node *delNode;
        rows *thruRows = m.firstRow;
        for (int i = 0; i < m.nOfRows; ++i) {
            node *thruNodes = thruRows->listOfNodes;
            if (thruNodes != nullptr)
                thruRows->listOfNodes = nullptr;
            while (thruNodes != nullptr) {
                delNode = thruNodes;
                thruNodes = thruNodes->next;
                delNode->next = nullptr;
                delete delNode;
            }
            thruRows = thruRows->next;
        }
        return success;
    }
}
