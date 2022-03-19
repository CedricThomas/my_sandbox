//
// Created by arzad on 19/03/2022.
//

#ifndef APP_TQUEUE_HPP
#define APP_TQUEUE_HPP

#include <mutex>
#include <optional>
#include <queue>

template<typename T>
class TQueue {
    std::queue<T> _queue;
    std::mutex _mutex;

    // Moved out of public interface to prevent races between this
    // and pop().
    bool empty() const {
        return _queue.empty();
    }

public:
    TQueue() = default;

    virtual ~TQueue() { }

    unsigned long size() const {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.size();
    }

    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(_mutex);
        if (_queue.empty()) {
            return {};
        }
        T tmp = _queue.front();
        _queue.pop();
        return tmp;
    }

    void push(const T &item) {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(item);
    }
};

#endif //APP_TQUEUE_HPP
