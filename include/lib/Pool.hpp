//
// Created by arzad on 28/02/2022.
//

#ifndef APP_POOL_HPP
#define APP_POOL_HPP

#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>

#define MAX_THREADS (-1)

class Pool {
public:
    void shutdown();
    void addJob(const std::function<void()> &job);

    explicit Pool(int min_threads, int max_threads = MAX_THREADS);
    virtual ~Pool();

private:
    void start(int ID);

    std::vector<std::thread> _threads;
    std::mutex _queue_lock;
    std::mutex _workload_lock;
    std::queue<std::function<void()>> _jobs_queue;
    std::condition_variable _job_available_condition;
    bool _terminate_pool;
    bool _stopped;
    unsigned int _workload;
    unsigned int _max_workload;
};


#endif //APP_POOL_HPP
