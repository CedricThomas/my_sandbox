//
// Created by arzad on 01/05/2022.
//

#ifndef APP_TOPIC_HPP
#define APP_TOPIC_HPP

#include <unordered_map>
#include "AsyncSubscription.hpp"
#include "SyncSubscription.hpp"

template<typename T, typename U>
class Topic {
public:
    explicit Topic(const std::string &name) : _name(name), _queue(), _subscribers() {}

    const std::string &getName() const {
        return _name;
    }

    std::shared_ptr<AsyncSubscription<T, U>> createAsyncSubscribe(const std::string &subscriptionName) {
        auto subscription = std::make_shared<AsyncSubscription<T, U>>(subscriptionName, this);
        _subscribers[subscriptionName] = subscription;
        return subscription;
    }


    std::shared_ptr<SyncSubscription<T, U>> createSyncSubscribe(const std::string &subscriptionName, const SyncSubscriptionCallback<T> &callback) {
        auto subscription = std::make_shared<SyncSubscription<T, U>>(subscriptionName, callback, this);
        _subscribers[subscriptionName] = subscription;
        return subscription;
    }

    bool tryPull(Message<U> &item) {
        return _queue.try_dequeue(item);
    }

    void publishToSubcribers(const T &data) {
        for (auto &subscriber : _subscribers) {
            subscriber.second->push(data);
        }
    }

    void publishToSubcriber(const std::string &subscriptionName, const T &data) {
        _subscribers[subscriptionName]->push(data);
    }

    // Only used by Subscriptions

    bool push(const Message<U> &item) {
        return _queue.enqueue(item);
    }

    void removeSubscriber(const std::string &subscriptionName) {
        _subscribers.erase(subscriptionName);
    }

private:
    std::string _name;
    moodycamel::ConcurrentQueue<Message<U>> _queue;
    std::unordered_map<std::string, std::shared_ptr<ASubscription<T, U>>> _subscribers;
};


#endif //APP_TOPIC_HPP
