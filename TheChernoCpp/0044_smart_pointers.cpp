/**
 * @file 0044_smart_pointers.cpp
 * @author cg
 * @brief SMART POINTERS in C++ (std::unique_ptr, std::shared_ptr, std::weak_ptr)
 * @version 0.1
 * @date 2023-08-19
 * 
 * @copyright Copyright (c) 2023
 * 
 * Focus on what smart pointer is and what it can do for you.
 * 
 * **Key Takeaway**
 * 1.1 unique_ptr is a scoped pointer, 超出作用域时, 它会被销毁然后调用 delete.
 *      It is just a stack allocated object and when that object dies it
 *      will call delete on your pointer and free that memory.
 * 1.2 unique_ptr 是唯一的, you cannot copy a unique_ptr 
 *     (如果复制一个 unique_ptr, 两个 unique_ptr 指向同一个内存块, 如果其中一个销毁了
 *     它会释放那段内存, i.e., 指向同一块内存的第二个 unique_ptr 指向了已经被释放的内存).
 * 2.1 shared_ptr 的工作方式是通过引用计数.
 */
#include <iostream>
#include <memory>

class Entity
{
public:
    Entity() { std::cout << "Construct Entity!\n"; }
    ~Entity() { std::cout << "Destruct Entity!\n"; }

    void Foo() { }
};


int main()
{   
    std::cout << "unique_ptr:\n";
    // I wanna make a unique pointer which lasts in a certain scope.
    {
        // unique_ptr's constructor is explicit,
        // meaning you do have to call the constructor explicitly.
        // There is no implicit kind of conversion or converting constructor.
        std::unique_ptr<Entity> e(new Entity());
        // std::unique_ptr<Entity> e0 = e; // 1.2 
    }

    // The preferred way though to construct this would actually be
    // using std::make_unique (introduced in C++14)
    // 主要原因是 exception safety.
    // 如果构造函数异常你不会有一个 dangling pointer (memory leak).
    std::unique_ptr<Entity> entity = std::make_unique<Entity>();
    entity->Foo();

    
    std::cout << "\nshared_ptr:";
    std::weak_ptr<Entity> weakEntity;
    {
        std::shared_ptr<Entity> e0;
        {
            // 这里使用 std::make_shared 除了 exception safety, 还因为
            // shared_ptr 需要分配额外一块内存(控制块, 用来存储引用计数)
            // 如果首先创建一个 new Entity, 然后将其传递给 shared_ptr 构造函数:
            // 一共做 2 次内存分配 (先做一次 new Entity 的分配, 然后是 shared_ptr 的控制内存块的分配)
            // 然而如果用 make_shared 则把内存分配组合起来, which is a lot more efficient.
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
            weakEntity = sharedEntity; // 把一个shared_ptr赋值给一个weak_ptr时, 它不会增加引用计数
                                                             // 这很好, 如果你不想要 Entity 的所有权, 就像你可能在排序一个 Entity 列表
                                                             // 你不关心它们是否有效, 你只需要存储它们的一个引用就可以了.
                                                             // 当然你可以检查它是否有效
            !weakEntity.expired() ? std::cout << "weak_ptr is valid.\n" : std::cout << "weak_ptr is expired.\n";
        }
    }
    !weakEntity.expired() ? std::cout << "weak_ptr is valid.\n" : std::cout << "weak_ptr is expired.\n";   


    std::cin.get();
}