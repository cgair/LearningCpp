/**
 * @file 0033_const.cpp
 * @author cg
 * @brief CONST in C++
 * @version 0.1
 * @date 2023-10-04
 * 
 * @copyright Copyright (c) 2023
 * **Key Takeaway**
 * 
 */
#include <iostream>

// const的和变量没有关系的用法:
// 用在方法名的后面 (只有类才有这样的写法)
class Entity {
    int x;
    mutable double var;
public:
    Entity() : x(1), var(0.2) { }
    // 如果实际上没有修改 class 或者方法不应该修改 class,
    // 总是标记你的方法为 const, 否则在有常量引用或类似的情况下就用不了你的方法.
    int get_x() const {
        return x;
    }

    double get_var() const {
        return var <= 1 ? var + 1 : var;
    }

    void set_x(int value) {
        x = value;
    }
};

void print_entity(Entity& e) {
    std::cout << e.get_x() << std::endl;
}

void print_entity2(const Entity& e) { // const Entity 调用 const 函数
    std::cout << e.get_x() << std::endl;
}

int main()
{
    const int a = 1;
    // a = 2;

    int* p = new int;
    *p = 2;
    p = (int*)&a; // bypass this whole const thing
                  // const是伪关键字, 因为它在改变生成代码方面做不了什么
    std::cout << *p << std::endl;

    int value = 3;
    // 两种写法都可以, 重点是 const 在 * 之前, 
    // i.e., *ptr (指针指向是 constant)
    // const int* ptr1 = new int;
    int const* ptr1 = new int;
    // *ptr1 = 1;
    ptr1 = &value;

    int* const ptr2 = new int;
    *ptr2 = 3;
    // ptr2 = &value;

    const int* const ptr3 = new int;
    // *ptr3 = 4;
    // ptr3 = &value;

    std::cin.get();
}