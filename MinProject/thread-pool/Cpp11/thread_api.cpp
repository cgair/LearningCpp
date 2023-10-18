// <https://en.cppreference.com/w/cpp/thread/thread/thread>
#include <thread>
#include <chrono>
#include <iostream>

// pass by value
void f1(int n) {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 1 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// pass by reference
// The arguments to the thread function are moved or copied by value. 
// If a reference argument needs to be passed to the thread function, 
// it has to be wrapped (e.g., with std::ref or std::cref).
void f2(int& n) {
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

class foo {
public:
    int n = 0;
    void bar() {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "Thread 3 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

class baz {
public:
    int n = 0;
    void operator() () {
        for (int i = 0; i < 5; ++i)
        {
            std::cout << "Thread 4 executing\n";
            ++n;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};


int main()
{
    int n = 0;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3));
    
    foo f;
    baz b;

    std::thread t5(foo::bar, &f);
    std::thread t6(b); // t6 runs baz::operator() on a copy of object b

    t2.join();    
    // t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << "Final value of n is " << n << '\n';
    std::cout << "Final value of f.n (foo::n) is " << f.n << '\n';
    std::cout << "Final value of b.n (baz::n) is " << b.n << '\n';

    return 0;
}