//
// Created by arzad on 01/05/2022.
//

#ifndef APP_ASYNCSUBSCRIPTION_HPP
#define APP_ASYNCSUBSCRIPTION_HPP

#include <string>
#include <memory>
#include <utility>
#include "lib/containers/blockingconcurrentqueue.h"
#include "ASubscription.hpp"

template<typename T, typename U>
class AsyncSubscription: public ASubscription<T, U> {
public:
    AsyncSubscription(const std::string &name, Topic<T, U> *topic) : ASubscription<T, U>(name, topic), _queue() {}

    bool tryPull(T& item) {
        return _queue.try_dequeue(item);
    }

    void pull(T& item) {
        _queue.wait_dequeue(item);
    }

    // Only used by the topic

    bool push(const T& item) {
        return _queue.enqueue(item);
    }
private:
    moodycamel::BlockingConcurrentQueue<T> _queue;
};


#endif //APP_ASYNCSUBSCRIPTION_HPP
