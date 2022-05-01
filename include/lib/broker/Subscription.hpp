//
// Created by arzad on 01/05/2022.
//

#ifndef APP_SUBSCRIPTION_HPP
#define APP_SUBSCRIPTION_HPP

#include <string>
#include <memory>
#include <utility>
#include "lib/containers/concurrentqueue.h"

template<typename T, typename U>
class Topic;

template<typename T, typename U>
class Subscription {
public:
    explicit Subscription(std::string name, Topic<T, U> *topic): _name(std::move(name)), _topic(topic) {}

    const std::string &getName() const {
        return _name;
    }

    moodycamel::ConcurrentQueue<T> *operator->() {
        return &_queue;
    }
private:
    std::string _name;
    moodycamel::ConcurrentQueue<T> _queue;
    std::shared_ptr<Topic<T, U>> _topic;
};


#endif //APP_SUBSCRIPTION_HPP
