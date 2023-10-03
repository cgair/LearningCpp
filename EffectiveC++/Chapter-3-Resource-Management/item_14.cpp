// Item 14: Think carefully about copying behavior in resource-managing classes.
// Things to Remember
// ✦ Copying an RAII object entails copying the resource it manages, 
//   so the copying behavior of the resource determines the copying behavior of the RAII object.
// ✦ Common RAII class copying behaviors are disallowing copying and performing reference counting, 
//   but other behaviors are possible.
// 
// A general question that every RAII class author must confront:
// what should happen when an RAII object is copied?
#include <iostream>
#include <mutex>
#include <thread>

static int value = 0; 

// 1. Prohibit copying.
// RAII class for managing std::mutex
class MutexGuard {
    std::mutex& mtx_;
public:
    MutexGuard(std::mutex& mtx) : mtx_(mtx) {
        mtx_.lock();
        std::cout << "Mutex locked." << std::endl;
    }

    ~MutexGuard() {
        mtx_.unlock();
        std::cout << "Mutex unlocked." << std::endl;
    }

    // Prohibit copying to ensure exclusive ownership
    MutexGuard(const MutexGuard&) = delete;
    MutexGuard& operator=(const MutexGuard&) = delete;
};

void foo(std::mutex& mtx) {
    MutexGuard guard(mtx); // Locks the mutex upon construction
    for (int i = 0; i < 10; ++i)
        value ++;
} // Mutex is automatically unlocked upon going out of scope

void prohibit_copying() {
    std::mutex m;
    std::thread t1(foo, std::ref(m));
    std::thread t2(foo, std::ref(m));

    t1.join();
    t2.join();

    std::cout << "Value = " << value << std::endl;
}

// 2. Reference-count the underlying resource.
// RAII class for managing a mutex with reference counting
class MutexWrapper {
    std::shared_ptr<std::mutex> pmtx_;
public:
    MutexWrapper() : pmtx_(std::make_shared<std::mutex>()) {
        std::cout << "Mutex created." << std::endl;
    }

    ~MutexWrapper() {
        std::cout << "Mutex destroyed." << std::endl;
    }

    MutexWrapper(const MutexWrapper& other) : pmtx_(other.pmtx_) {
        std::cout << "Mutex copied." << std::endl;
    }

    void lock() {
        pmtx_->lock();
        std::cout << "Mutex locked." << std::endl;
    }

    void unlock() {
        pmtx_->unlock();
        std::cout << "Mutex unlocked." << std::endl;
    }
};

void reference_count() {
    MutexWrapper m1;
    MutexWrapper m2 = m1;
    
    // It can lead to unexpected behavior if not used carefully, 
    // especially when different code paths access the mutex.
    m1.lock();
    for (int i = 0; i < 10; ++i) value ++;
    // m2.lock();
    m1.unlock();

    m2.lock();
    for (int i = 0; i < 10; ++i) value ++;
    m2.unlock();

    std::cout << "Value = " << value << std::endl;
    // m1 and m2 will be automatically destroyed when they go out of scope,
    // and the underlying mutex will be released when the reference count reaches zero
}

// 3. Copy the underlying resource.
// deep copy: Sometimes you can have as many copies of a resource as you like
// 而我们需要 resource-managing class 的唯一原因是确保在使用完每个副本后都将其释放.
// 在这种情况下, 复制 resource-managing object 也应该复制它所包装的资源.

// 4. Transfer ownership of the underlying resource.
class RAIIResource {
public:
    // Move constructor
    RAIIResource(RAIIResource&& other) noexcept {
        // Transfer ownership of the resource from 'other' to 'this'
    }
    
    // Move assignment operator
    RAIIResource& operator=(RAIIResource&& other) noexcept {
        if (this != &other) {
            // Release current resource, if any, and take ownership of 'other's resource
        }
        return *this;
    }
};

int main()
{
    // 1
    prohibit_copying();

    // 2
    reference_count();

    std::cin.get();
}