/**
 * @file 0058_function_pointersc.cpp
 * @author cg
 * @brief Function Pointers in C++
 * @version 0.1
 * @date 2023-09-30
 * 
 * @copyright Copyright (c) 2023
 * **Key Takeaway**
 * 1. Function pointer is just a way to assign a function to a variable.
 * 2. Why you might wanna use function pointers in the first place. (a useful example)
 * 
 */
#include <iostream>
#include <string>
#include <vector>

void hello_world() {
    std::cout << "hello world!\n";
}

void hi_you(std::string name) {
    std::cout << "Hi " << name << std::endl;
}

int square(int value) {
    return value * value;
}

void print_value(int value) {
    std::cout << "Value: " << value << std::endl;
}

void for_each(const std::vector<int>& values, void(*func)(int)) {
    for (int value : values)
        func(value);
}

int main()
{
    auto hello = hello_world;
    hello();
    auto world = &hello_world; // we don't actually use this ampersand (&)
                               // because there is an implicit conversion
    world();

    // 我们在上面使用了auto, but what type is this actually?
    // 鼠标停在 hello 上看看
    void(*name)() = hello_world;
    name();
    // my preferred way is actually to `typedef` it
    // or `using` it (creating alias for it).
    typedef void(*ft)();
    ft foo = hello_world;
    foo();

    typedef void(*hi)(std::string);
    // using hi = void(*)(std::string);
    hi bar = hi_you;
    bar("eastonchen");

    // Why you might wanna use function pointers in the first place.
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8};
    // It's a way that we can tell our function: 
    // hey, I want you to do <this> at a particular time.
    for_each(values, print_value);
    // 但是你还可以想到 lambada, std::function
    for_each(values, [](int value) { std::cout << "Value: " << value << std::endl; });

    std::cin.get();
}