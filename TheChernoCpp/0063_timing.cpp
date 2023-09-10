/**
 * @file 0063_timing.cpp
 * @author cg
 * @brief Timing in C++
 * @version 0.1
 * @date 2023-09-10
 * 
 * @copyright Copyright (c) 2023
 * **Key Takeaways**
 * 1. Timing is useful for so many things: 
 *    You wanna sth to happen at certain time;
 *    Evaluating your performance or benchmarking;
 */
#include <iostream>
#include <thread>
#include <chrono> // c++ 11
// <https://en.cppreference.com/w/cpp/header/chrono>
struct Timer 
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f;
        std::cout << "Timer took " << ms << "ms" << std::endl;
    }
};

// We wanna figure out how long does it take
// `cout` to actually write stuff out to the 
// console 100 times
// 当然可以 copy main 函数中的那一堆代码, 但是太长了我并不想这样做.
// So instead I'm going to set up a very very basic struct
// or class called `Timer`
void Foo() {
    Timer timer;
    for (int i = 0; i < 100; ++i)
        // std::cout << "Hello" << std::endl;
        // std::endl seems to be quite slower for some reason.
        // So we just get rid of that by putting a backslash n
        // into our print.
        std::cout << "Hello\n"; 
}

int main()
{
    using namespace std::literals::chrono_literals; // 有了这个, 才能用下面 1s 中的 's'
    // Give me the current time.
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s); // 休眠 1s, 实际会比 1s 大 (函数本身有开销)
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << " s\n";

    Foo();

    std::cin.get();
}