// Item 2: Prefer consts, enums, and inlines to #defines.
// 
// Things to Remember:
// ✦ For simple constants, prefer const objects or enums to #defines. 
// ✦ For function-like macros, prefer inline functions to #defines.
#include <iostream>
#include "item_02.h"

void f(int m) {
    std::cout << "Max = "
              << m
              << std::endl;
}

// 最好改用 inline 的模板函数
template<typename T>                              // because we don’t
inline void call_with_max(const T& a, const T& b) {   // know what T is, we
    f(a>b?a:b);                                       // pass by reference-to-const
}

int main()
{
    // 使用 #define 定义的常量
    double result_define = 10 * ASPECT_RATIO;

    // 使用 const 定义的常量
    double result_const = 10 * two::aspect_ratio_const;

    // even if you parenthesize all the arguments in the macro body
    // weird things can still happen:
    int a = 5, b = 0;
    CALL_WITH_MAX(++a, b);      // a is incremented twice

    call_with_max(a, b);


    // 引用和指针都无法绑定在一个枚举常量上。
    // int& rf = two::FIRST;
    // int* pf = &two::FIRST;

    return 0;
}