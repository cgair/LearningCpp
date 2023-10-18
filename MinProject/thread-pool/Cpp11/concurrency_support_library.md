# C++ 11
C++ includes built-in support for threads, atomic operations, mutual exclusion, condition variables, and futures.

# C++ Concurrency In Action
基于 C++11 新标准的并发和多线程编程深度指南, 涵盖:
* std::thread, std::mutex, std::future 和 std::async 等基础类的使用
* 内存模型和原子操作
* 基于锁和无锁数据结构的构建
* 并行算法, 线程管理
* 多线程代码的测试工作

# Threads
`// TBD`

# Mutual exclusion
## mutex 使用互斥量保护共享数据
[EXAMPLE - mutex](https://godbolt.org/z/Me3f3bfqK)
* 大多数情况下, 互斥量通常会与保护的数据放在同一个类中 (而不是定义成全局变量).
  * 互斥量和要保护的数据, 在类中都需要定义为 private 成员.
  * 成员函数都会在调用时对数据上锁, 结束时对数据解锁.
  * 也不是总是那么理想: 当其中一个成员函数返回的是保护数据的**指针或引用时** (留后门), 具有访问能力的指针或引用可以访问 (并可能修改) 被保护的数据, 而不会被互斥锁限制.

**Key takeaway**
* 确保成员函数不会传出指针或引用.
* 还不够: [将受保护数据的指针或引用传递到互斥锁作用域之外](https://godbolt.org/z/fPGfzebM6)
  * 切勿将受保护数据的指针或引用传递到互斥锁作用域之外, 无论是函数返回值、存储在外部可见内存、亦或是以参数的形式传递到用户提供的函数中去.

## std::unique_lock
**Key takeaway**
* class unique_lock 是 a mutex ownership wrapper. 允许
  * 有不同的 Lock Strategies
  * time-constrained attempt at locking
  * recursive locking
  * mutex 所有权的传递 (move, not copy)
  * 条件变量都配合 `std::unique_lock` 使用 (因为条件变量在 wait时 需要有手动释放锁的能力)
* 比`std::lock_guard`灵活, 体积大一点, 效率差一点.

## 基于锁的并发数据结构设计

## See also
* [C++ Concurrency In Action - 第3章 线程间共享数据](https://nj.gitbooks.io/c/content/content/chapter3/chapter3-chinese.html)
* [C++ Concurrency In Action - 第6章 基于锁的并发数据结构设计](https://nj.gitbooks.io/c/content/content/chapter6/chapter6-chinese.html)
* [std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
* [std::unique_lock](https://en.cppreference.com/w/cpp/thread/unique_lock)

# Condition variables & Futures
实际情况中, 一个线程完成前可能需要等待另一个线程执行完成 (等待一个特定事件的发生), 线程间需要协作.

C++标准库提供了一些工具可用于同步操作, i.e., 条件变量 (condition variables) 和 futures.

## 同步并发操作 - Condition Variables
1. [生产者消费者问题](https://godbolt.org/z/v8375zssE)


## 同步并发操作 - Futures

## See also
* [C++ Concurrency In Action - 第4章 同步并发操作](https://nj.gitbooks.io/c/content/content/chapter4/chapter4-chinese.html)
* [std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
* [std::future](https://en.cppreference.com/w/cpp/thread/future)


# Memory ordering

## See also
[C++ Concurrency In Action - 第5章 C++内存模型和原子类型操作](https://nj.gitbooks.io/c/content/content/chapter5/chapter5-chinese.html)


# Thread Pool

## C++ 11
### Prerequisite
* [Threads - std::thread](https://en.cppreference.com/w/cpp/thread/thread)
* [Mutual exclusion - std::mutex](https://en.cppreference.com/w/cpp/thread/mutex)
* [Condition variables - std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
* [Futures - std::future](https://en.cppreference.com/w/cpp/thread/future)
* [Futures - std::packaged_task](https://en.cppreference.com/w/cpp/thread/packaged_task)
* [Utilities library - std::forward](https://en.cppreference.com/w/cpp/utility/forward)
* [Utilities library - std::move](https://en.cppreference.com/w/cpp/utility/move)
* [Utilities library - std::function](https://en.cppreference.com/w/cpp/utility/functional/function)
* [Utilities library - std::bind](https://en.cppreference.com/w/cpp/utility/functional/bind)
* [Lambda expressions](https://en.cppreference.com/w/cpp/language/lambda)

### 线程池设计
通过问题来设计:
1. 线程池中需要哪些数据结构?
2. 如何开启/关闭线程池?
3. 如何为线程池添加线程?
4. 何将任务放入线程池中执行?
5. 如何实现多参数任务的支持?
6. 如何等待任务的执行结果?



## See also
[C++ Concurrency In Action - 第9章 高级线程管理](https://nj.gitbooks.io/c/content/content/chapter9/chapter9-chinese.html)