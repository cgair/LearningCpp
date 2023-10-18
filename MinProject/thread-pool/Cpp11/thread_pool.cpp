#include "thread_pool.h"

namespace tp {

    ThreadPool::ThreadPool(ThreadPoolConfig config) : config_(config) {
        this->is_shutdowm_ = false;

        if (!is_valid_config(config)) {
            is_available_.store(false);
        }
        is_available_.store(true);
    }

    ThreadPool::~ThreadPool() {
        stop();
    }

    bool ThreadPool::start() {
        // if (!is_available()) return false;
        std::unique_lock<std::mutex> lk(mtx_);
        if (!threads_.empty()) return false;

        for (int i = 0; i < config_.core_threads; ++i) {
            threads_.push_back(new std::thread());
        }
    }

    void ThreadPool::stop() {
        if (!is_available()) return;
        { // 减小锁的粒度
            std::unique_lock<std::mutex> lk(mtx_);
            this->is_shutdowm_ = true;
            this->task_cv_.notify_all();
            this->is_available_.store(false);
        }

        for (int i = 0; i < config_.core_threads; ++i) {
            delete threads_[i];
            this->threads_[i] = nullptr;
        }

        std::unique_lock<std::mutex> lk(mtx_);
        threads_.clear();
    }

    void ThreadPool::run() {
        while (!is_shutdowm()) {

        }
    }

    
    bool ThreadPool::is_valid_config(const ThreadPoolConfig& config) {
        if (config.core_threads < 1 || config.time_out.count() < 1) return false;

        return true;
    }

    bool ThreadPool::is_available() {
        return is_available_.load();
    }

    bool ThreadPool::is_shutdowm() {
        return is_shutdowm_;
    }
}

