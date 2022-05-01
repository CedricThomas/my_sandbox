//
// Created by arzad on 01/05/2022.
//

#ifndef APP_TOPIC_HPP
#define APP_TOPIC_HPP

#include <unordered_map>
#include "Subscription.hpp"

template<typename T, typename U>
class Topic {
public:
    explicit Topic(const std::string &name) : _name(name), _queue(), _subscribers() {}

    const std::string &getName() const {
        return _name;
    }

    std::shared_ptr<Subscription<T, U>> subscribeAs(const std::string &subscriptionName) {
        auto subscription = std::make_shared<Subscription<T, U>>(subscriptionName, this);
        _subscribers[subscriptionName] = subscription;
        return subscription;
    }

    moodycamel::ConcurrentQueue<U> *operator->() {
        return &_queue;
    }

    void publishToSubcribers(const T &data) {
        for (auto &subscriber : _subscribers) {
            (*subscriber.second)->enqueue(data);
        }
    }

private:
    std::string _name;
    moodycamel::ConcurrentQueue<U> _queue;
    std::unordered_map<std::string, std::shared_ptr<Subscription<T, U>>> _subscribers;
};


#endif //APP_TOPIC_HPP
