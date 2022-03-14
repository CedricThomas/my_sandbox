//
// Created by arzad on 28/02/2022.
//

#include <mutex>
#include "lib/Pool.hpp"
#include "spdlog/spdlog.h"

void Pool::start(int ID) {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(_queue_lock);

            spdlog::debug("[THREAD {}] Waiting...", ID);
            _job_available_condition.wait(lock, [this]() {
                return !_jobs_queue.empty() || _terminate_pool;
            });
            if (_terminate_pool) {
                spdlog::debug("[THREAD {}] Terminating", ID);
                return;
            }
            spdlog::debug("[THREAD {}] Running !", ID);
            job = _jobs_queue.front();
            _jobs_queue.pop();
        }
        {
            std::unique_lock<std::mutex> lock(_workload_lock);
            _workload++;
        }
        job(); // function<void()> type
        {
            std::unique_lock<std::mutex> lock(_workload_lock);
            _workload--;
        }
    }
}

void Pool::addJob(const std::function<void()> &job) {
    {
        std::unique_lock<std::mutex> lock(_queue_lock);
        _jobs_queue.push(job);
    }
    _job_available_condition.notify_one();
}

void Pool::shutdown() {
    {
        std::unique_lock<std::mutex> lock(_queue_lock);
        _terminate_pool = true; // use this flag in condition.wait
    }

    _job_available_condition.notify_all(); // wake up all threads.

    // Join all threads.
    for (std::thread &th: _threads) {
        th.join();
    }

    _threads.clear();
    _stopped = true; // use this flag in destructor, if not set, call shutdown()
}

Pool::Pool(int min_threads, int max_threads)
        : _threads(),
          _queue_lock(),
          _workload_lock(),
          _jobs_queue(),
          _job_available_condition(),
          _terminate_pool(false),
          _stopped(false),
          _workload(0),
          _max_workload(0) {
    auto num_threads = std::thread::hardware_concurrency();
    if (num_threads < min_threads) {
        throw std::runtime_error("Pool::Pool: min_threads is greater than hardware concurrency");
    } else if (num_threads > max_threads && max_threads != MAX_THREADS) {
        num_threads = max_threads;
    }
    _max_workload = num_threads;
    for (int i = 0; i < num_threads; i++) {
        _threads.emplace_back([this, i]() {
            this->start(i);
        });
    }
}

Pool::~Pool() {
    if (!_stopped) {
        this->shutdown();
    }
}
