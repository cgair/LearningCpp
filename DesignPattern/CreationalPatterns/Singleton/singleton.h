#ifndef SINGLETON_H
#define SINGLETON_H
#include <iostream>

// 有缺陷的懒汉式 (Lazy-Initialization)
// 
// 1. not thread safe
// 2. memory leak
class Singleton0
{
private:
    static Singleton0* pInstance;
    Singleton0() {
        std::cout << "constructor called.\n";
    }
    // Singleton0(const Singleton0&) {}
    // Singleton0& operator= (const Singleton0&) {}

    // C++11 引入了 =delete 语法作为更直观和清晰的替代方法
    Singleton0(const Singleton0&) = delete;
    Singleton0& operator= (const Singleton0&) = delete;
public:
    ~Singleton0() {}
    // 1. 线程安全的问题: 多线程获取单例时有可能引发 race condition
    //    第 1 个线程在 if 中判断 `pInstance` 是空的, 于是开始实例化单例;
    //    同时第 2 个线程也尝试获取单例, 这个时候判断 `pInstance` 还是空的, 
    //    所以也开始实例化单例， 这样就会实例化出两个对象。
    //    解决办法: 加锁。
    // 2. 内存泄漏.
    //    注意到类中只负责 new 出对象, 却没有负责 delete 对象, 因此只有构造函数被调用, 析构函数却没有被调用;
    //    会导致内存泄漏.
    //    解决办法: 使用共享指针.
    static Singleton0* getInstance() {
        if (pInstance == nullptr) {
            pInstance = new Singleton0();
        }

        return pInstance;
    }

    void doSth() {
        std::cout << "Singleton0 do something\n";
    }
};

Singleton0* Singleton0::pInstance = nullptr;


// Meyers' Singleton
// 线程安全的
// 利用 C++11 标准的 [Magic Static 特性](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2660.htm)
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton&) = delete;
    static Singleton& getInstance() {   // 注意❗️ 返回引用
        // 静态局部变量的初始化只会在第一次执行到其声明语句时进行一次
        static Singleton instance;  // If control enters the declaration concurrently 
                                    // while the variable is being initialized, 
                                    // the concurrent execution shall 
                                    // wait for completion of the initialization.
        return instance;
    }

    void doSth() {
        std::cout << "Singleton do something\n";
    }
    
private:
    Singleton() {
        std::cout << "constructor called.\n";
    }
};

#endif
