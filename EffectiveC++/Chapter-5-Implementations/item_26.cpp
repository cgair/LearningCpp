// Item 26: Postpone variable definitions as long as possible.
// Things to Remember
// ✦ Postpone variable definitions as long as possible. 
//   It increases program clarity and improves program efficiency.
// 
// 问题: Defining variables too soon can cause a drag on performance.
#include <iostream>
#include <string>
#include "../utils.h"

const int PASSWORD_LENGTH_MIN = 10;

// 第一种常见的情况: 
// this function defines the variable "encrypted" too soon
std::string encrypt_password(const std::string password) {
    std::string encrypted; // you’ll pay for the construction and destruction of encrypted 
                           // even if encrypt_password throws an exception ❗️

    if (password.length() < PASSWORD_LENGTH_MIN) {
        throw std::logic_error("Password is too short");
    }

    // do whatever is necessary to place an
    // encrypted version of password in encrypted

    return encrypted;
}

// this function postpones encrypted’s definition until
// it’s necessary, but it’s still needlessly inefficient
std::string encrypt_password2(const std::string password) {

    if (password.length() < PASSWORD_LENGTH_MIN) {
        throw std::logic_error("Password is too short");
    }

    std::string encrypted; // default-construct encrypted
    encrypted = password; // assign to encrypted

    // A preferable approach is 
    // define and initialize via copy constructor ❗️
    // string encrypted(password);

    // do whatever is necessary to place an
    // encrypted version of password in encrypted

    return encrypted;
}

class Entity {
public:
    int value_;
    Entity() : value_(0) { }
    Entity(int value) : value_(value) { }
};

int main()
{
    // 第二种常见的情况: about loops
    // If a variable is used only inside a loop, 
    // is it better to define it outside the loop and make an assignment to it on each loop iteration, 
    // or is it be better to define the variable inside the loop?

    int n = 1000;
    // Approach A: define outside loop
    // 1 constructor + 1 destructor + n assignments.
    Entity e_a; // e_a 在比方法 B 更大的范围 (包含循环的范围) 中可见, 
                // 这与程序的可理解性和可维护性背道而驰.
    for(int i = 0; i < n; ++i) {
        e_a.value_ = i;
    }

    // Approach B: define inside loop
    // n constructors + n destructors.
    for(int i = 0; i < n; ++i) {
        Entity e_b(i);
    }

    // 对于赋值成本低于构造函数-析构函数对的类, 
    // 方法 A 通常更有效 (当 n 变大时尤其如此) 
    // 否则, 方法 B 可能更好.
    // 除非我们知道: 
    // (1) 赋值 is less expensive than 构造函数-析构函数
    // (2) 我们正在处理代码中对性能敏感的部分
    // 否则您应该默认使用 Approach B.

    std::cin.get();
}