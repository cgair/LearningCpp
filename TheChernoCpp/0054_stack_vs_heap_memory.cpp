/**
 * @file 0054_stack_vs_heap_memory.cpp
 * @author cg
 * @brief Stack vs Heap Memory in C++
 * @version 0.1
 * @date 2023-09-29
 * 
 * @copyright Copyright (c) 2023
 * **Key Takeaway**
 * 1. 栈通常是一个预定义大小的内存区域 (通常约 2 MB)
 * 2. 栈和堆内存区域的实际位置 (物理上) 都在我们的 RAM 中,
 *    people tend to think that the stack might be something
 *    that stores in the CPU cache (it's likely to be hot in
 *    the cache because we'are continually accessing it)
 * 3. You should try and allocate on the stack whenever possible.
 * 
 */
#include <iostream>

struct Vector3 {
    float x, y, z;

    Vector3() : x(10), y(11), z(12) { }
};

int main()
{
    // Why a stack allocation is extremely fast?
    // All we do is moving the stack pointer and
    // then we return the address of that stack pointer.
    int value = 5;
    int array[5] = {1, 2, 3, 4, 5};
    Vector3 vector;
    std::cout << " array addr: " << &array[0] << std::endl;
    std::cout << "vector addr: " << &vector << std::endl;

    // heap allocation
    // What `new` and `delete` do?
    int* hvalue = new int;
    *hvalue = 5;
    int* harray = new int[5];
    Vector3* hvector = new Vector3();
    std::cout << " hvalue addr: " << hvalue << std::endl;
    std::cout << " harray addr: " << harray << std::endl;
    std::cout << " harray addr: " << &harray[0] << std::endl;
    std::cout << "hvector addr: " << hvector << std::endl;

    delete hvalue;
    delete[] harray;
    delete hvector;

    // You should try and allocate on the stack whenever possible
    // because that's very very real **performance difference**
    // The performance difference is the **allocation**
    // `delete` 也同样 incredibly heavy.
    // 从 assembly 就可以看出:
    // 1.1 int value = 5;
    // mov    DWORD PTR [rbp-0x4],0x5
    // 
    // 1.2 int* hvalue = new int; *hvalue = 5;
    // mov    edi,0x4
    // call   43 <main+0x43>
    //     R_X86_64_PLT32 operator new(unsigned long)-0x4
    // mov    QWORD PTR [rbp-0x10],rax
    // 
    // mov    rax,QWORD PTR [rbp-0x10]
    // mov    DWORD PTR [rax],0x5

    std::cin.get();
}