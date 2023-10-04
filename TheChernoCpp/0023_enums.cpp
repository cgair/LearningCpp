/**
 * @file 0023_enums.cpp
 * @author cg
 * @brief ENUMS in C++
 * @version 0.1
 * @date 2023-10-04
 * 
 * @copyright Copyright (c) 2023
 * **Key Takeaway**
 * 1. When you want to use integers to represent certain states/values, 
 *    however you want to give them a name so that you code is more readable.
 * 2. You can specify which type of integer you wanna this enum to be.
 *    (enums by default are 32-bit integers)
 * 
 */
#include <iostream>

// Key Takeaway 2
enum EXAMPLE : unsigned char { // 8-bit integer (less memory)
// enum EXAMPLE : float // Error 枚举必须是一个整数
    A, B, C
};

int main()
{
    int a = A; 

    EXAMPLE e = B;

    if (e == 2)
        std::cout << e << std::endl;

    // 应用: 枚举和 switch case 是好搭档
    enum STEP {
        STEP0 = 0,
        STEP1 = 1,
        STEP2 = 2,
    };

    STEP s = static_cast<STEP>(2);
    switch (s) {
        case STEP0:
        // 
        break;
        case STEP1:
        // 
        break;
        case STEP2:
        // 
        break;
        default:
        break;
    }

    std::cin.get();
}