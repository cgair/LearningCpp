/**
 * @file 0047_optimizing_the_usage_of_vector.cpp
 * @author cg
 * @brief Optimizing the usage of std::vector in C++
 * @version 0.1
 * @date 2023-08-16
 * 
 * @copyright Copyright (c) 2023
 * 
 * **Key Takeaway**
 * 1. should I be storing 
 *    pointers to heap allocated classes
 *    or
 *    stack allocated vertex classes/structs
 *    in my vecotr?
 * 2. vecctor 的使用优化
 *    1) reserve 提前申请内存, 避免动态申请开销
 *    2) emplace_back 直接在容器尾部创建元素, 省略 拷贝/移动 过程
 */
#include <vector>
#include <iostream>

struct Vertex
{
    float x, y, z;
    Vertex(float x, float y, float z) : x(x), y(y), z(z) { }
    Vertex(const Vertex& vertex) : x(vertex.x), y(vertex.y), z(vertex.z) {
        std::cout << "Copied!" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    
    return stream;
}

int main()
{
    std::cout << "+----------------------------------------+\n";
    // Vertex* vertices = new Vertex[5];

    // using std::vector 
    // 1. should I be storing pointers to heap allocated classes in my vecotr?
    // OR
    // 2. should I be storing stack allocated vertex classes/structs?
    // 
    // It depends!
    // The primary consideration is that it is technically more optimal to store
    // vertex object instead of pointers because your memory is going to be inline
    // (Dynamic arrays are arrays in the sense that their memory is contiguous which
    // means that it's not fragment in memory)
    // If you store vertex objects in line, it's like: XYZ,XYZ,XYZ
    std::vector<Vertex> vertices;
    // std::vector<Vertex*> vertices; // I'm not going to store a bunch of pointers
                                      // to the Vertex struct
    vertices.push_back(Vertex(1, 2, 3));
    // 打印一次 Copied! 的原因:
    // 1. line 56 打断点 debug: ni 然后看到 vertices size 0 -> 1; Debug Console: Copied!
    //    Why is that happening?
    //    1) when we construct our vertex we are actually constructing it in the current
    //       stack frame in the main function (constructing it in main)
    //    2) and then what needs to happen is to put it into that vector (main function -> the memory vector has allocated)
    //       copy!
    vertices.push_back(Vertex(4, 5, 6));
    // 又打印两次 Copied! 的原因:
    // resize
    vertices.push_back(Vertex(7, 8, 9));
    // 又又打印三次 Copied! 的原因:
    // resize twice

    std::cout << "+----------------------------------------+\n";
    std::vector<Vertex> vertices2;
    vertices2.reserve(3);
    vertices2.push_back(Vertex(1, 2, 3));
    vertices2.push_back(Vertex(4, 5, 6));
    vertices2.push_back(Vertex(7, 8, 9));
    std::cout << "We've saved a great deal of copies already!\n";

    std::cout << "+----------------------------------------+\n";
    // We can do better:s
    // I would like to construct it in the actual vector
    // using [emplace_back](https://en.cppreference.com/w/cpp/container/vector/emplace_back)
    std::cout << "But we can do better using emplace_back!\n";
    std::vector<Vertex> vertices3;
    vertices3.reserve(3);
    vertices3.emplace_back(1, 2, 3);
    vertices3.emplace_back(4, 5, 6);
    vertices3.emplace_back(7, 8, 9);
    std::cout << "This code over here is specifically is gonna\n";
    std::cout << "run a lot a lot faster\n";

    std::cin.get();
}
