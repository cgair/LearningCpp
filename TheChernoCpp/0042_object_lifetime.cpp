/**
 * @file 0042_object_lifetime.cpp
 * @author cg
 * @brief Object Lifetime in C++ (Stack/Scope Lifetimes)
 * @version 0.1
 * @date 2023-08-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * What lifetime means for stack-based variables?
 * 
 * **Key Takeaways**
 * 
 * 1. Scopes: a scope can be anything, 
 *    函数作用域, if语句作用域, for 和 while 循环作用域,
 *    或者空作用域, 类作用域 
 * 2. 基于栈的变量的好处: 
 */
#include <iostream>

class Entity
{
public:
    Entity() { std::cout << "Construct Entity!\n"; }
    ~Entity() { std::cout << "Destruct Entity!\n"; }
};

// A classic mistake:
// create stack based variable and 
// try to return a pointer to it
int* CreateArray() {
    int arr[5] = {0, 1, 2, 3, 4};

    return arr;
}

// ScopedPtr 是我们写的一个最基本的作用域指针, 由于其是在栈上分配的, 
// 然后作用域结束的时候, ScopedPtr 这个类就被析构, 
// 析构时我们又调用 delete 把堆上的指针删除内存.
class ScopedPtr {
    Entity* ptr_;
public:
    ScopedPtr(Entity* ptr) : ptr_(ptr) { }
    ~ScopedPtr() { delete ptr_; }
};

int main()
{
    // 编译运行查看输出理解
    // difference in object lifetime between
    // a stack-based variable and
    // a heap-based variable
    {
        {
            Entity e0;
        } // stack-based variables get freed(destroyed)
          // as soon as we go out of the scope
        Entity* ep = new Entity(); // our entity never destroyed 
                                   // of course that memory does get cleaned up
                                   // by the operating system when our program terminates
    }

    {
        ScopedPtr ep = new Entity();
        Entity* e = new Entity();
    }

    std::cin.get();
}