// Item 2: Use const whenever possible.
// 
// Things to Remember:
// ✦ Declaring something const helps compilers detect usage errors. 
//   const can be applied to objects at any scope, to function parameters 
//   and return types, and to member functions as a whole.
// ✦ Compilers enforce bitwise constness, but you should program using logical constness.
// ✦ When const and non-const member functions have essentially identical implementations, 
//   code duplication can be avoided by having the non-const version call the const version.
#include <vector>
#include <iostream>

// 1. 老生常谈:
//    const 和 pointer 的不同组合
//    ❗️只要记住const后面是什么 (数据类型不看), 什么就不变. 
void I_const_and_pointer() {
    char hello[] = "hello";
    char* world = "world";
    char* p1 = hello;               // non-const pointer, non-const data

    const char* p2 = hello;         // non-const pointer, const data
    p2 = world;
    // p2[0] = 'W';  // ❌
    
    char* const p3 = hello;         // const pointer, non-const data
    // p3 = world;   // ❌
    p3[0] = 'H';

    const char* const p4 = hello;   // const pointer, const data
    // p4 = world;   // ❌
    // p4[0] = 'H';  // ❌
}

// 3. 编译器强制实施 bitwise constness, 
// 但我们编写程序的时候应该遵循 logical constness.
class CTextBlock {
    char* p_text_;
public:
    // Constructor to create CTextBlock from a string
    CTextBlock(const char* str) {
        // Calculate the length of the input string
        std::size_t length = std::strlen(str);

        // Allocate memory for the character data, including null-terminator
        p_text_ = new char[length + 1];

        // Copy the input string into the allocated memory
        std::strcpy(p_text_, str);
    }

    // Destructor to release the allocated memory
    ~CTextBlock() {
        delete[] p_text_;
    }

    // 4. Avoiding Duplication in const and Non-const Member Functions
    char& operator[] (std::size_t position) const { // inappropriate (but bitwise
        return p_text_[position];                   // const) declaration of
    }                                               // operator[]

    // char& operator[](std::size_t position) {
    //     // do bounds checking
    //     // log access data
    //     // verify data integrity 
    //     return p_text_[position];
    // }
    // 
    // When const and non-const member functions 
    // have essentially identical implementations, 
    // code duplication can be avoided by 
    // having the non-const version call the const version
    char& operator[](std::size_t position) {
        return 
            const_cast<char&>(
                static_cast<const CTextBlock&>(*this)[position]
            );
    }
};  

int main()
{
    // 将某些东西声明为 const 可帮助编译器侦测出错误用法
    // 
    // Declaring an iterator const is like declaring a pointer const 
    // (i.e., declaring a T* const pointer): 
    // the iterator isn’t allowed to point to something different, 
    // but the thing it points to may be modified. 
    std::vector<int> v = {1, 2, 3, 4};
    const std::vector<int>::iterator iter = v. begin();   // iter acts like a T* const
    *iter = 4;  // OK, changes what iter points to
    // ++iter;  // error! iter is const
    
    std::vector<int>::const_iterator citer = v.begin();   // citer acts like a const T*
    // *citer = 1;  // error! *cIter is const
    ++citer;    // fine, changes cIter


    // 3. you create a constant object with a particular value 
    // and you invoke only const member functions on it, 
    // yet you still change its value!
    CTextBlock ctb("hello");    // declare constant object
    std::cout << ctb[0] << std::endl;

    char* p = &ctb[0]; // call the const operator[] to get a
                       //  pointer to ctb’s data
    *p = 'J';
    std::cout << ctb[0] << std::endl;   // ctb now has the value “Jello”

    return 0;
}