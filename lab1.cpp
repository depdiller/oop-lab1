#include <iostream>
#include "lab1.h"

namespace lab1 {
    int getInt(int &a) {
        std::cin >> a;
        if (!std::cin.good())
            return 1;
        return 0;
    }

}