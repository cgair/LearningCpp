#ifndef __THREAD_POOL__
#define __THREAD_POOL__
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>

namespace tp
{
class ThreadPool {
public:
    using PoolSeconds = std::chrono::seconds;
    struct ThreadPoolConfig {
        int core_threads;
        PoolSeconds time_out;
    };

    ThreadPool(ThreadPoolConfig config);
    ~ThreadPool();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool start();

    void stop();

    void run();

    template<class F, class... Args>
    auto exec(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using RetType = decltype(f(args...)); // 推导返回值类型
        
    }

    bool is_valid_config(const ThreadPoolConfig& config);
    
    bool is_available();
    
    bool is_shutdowm();

private:
    // C++ 保留标识符的规则中关于下划线的有:
    // 1. 包含两个连续下划线的标识符
    // 2. 以一个下划线加一个大写字母开头的标识符
    // 3. 顶级命名空间内的以一个下划线开头的标识符
    // 使用保留标识符是未定义行为.
    // 比较流行的私有变量命名方式是尾下划线
    ThreadPoolConfig config_;
    std::vector<std::thread*> threads_;
    std::queue<std::function<void()>> tasks;
    std::atomic<bool> is_available_;
    bool is_shutdowm_;
    std::mutex mtx_;
    std::condition_variable task_cv_;
};
} // namespace tp

#endif