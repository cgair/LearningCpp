#ifndef UTILS_H_
#define UTILS_H_
#include <iostream>
#include <string_view> 
// std::string 适用于需要对字符串进行频繁修改或需要拥有独立拷贝的场景
// std::string_view 适用于避免不必要的字符串拷贝, 只读操作或者用作函数参数,
//                  允许在不实际拷贝字符串的情况下对字符串进行操作和处理.

template<class T>
void print(const std::string_view name, const T& c) {

    std::cout << name << ": \t";
    for (auto &v : c) {
        std::cout << v << ((v != c.back()) ? ", " : "");
    }
    std::cout << std::endl;
}


#endif