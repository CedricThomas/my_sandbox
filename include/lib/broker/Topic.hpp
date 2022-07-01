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

    const std::string &getName() const;

    std::shared_ptr<AsyncSubscription<T, U>> createAsyncSubscribe(const std::string &subscriptionName);


    std::shared_ptr<SyncSubscription<T, U>> createSyncSubscribe(const std::string &subscriptionName, const SyncSubscriptionCallback<T> &callback);

    bool tryPull(Message<U> &item);

    void pull(Message<U> &item);

    void publishToSubcribers(const T &data);

    void publishToSubcriber(const std::string &subscriptionName, const T &data);

    void publishToOtherSubcribers(const std::string &subscriptionName, const T &data);

    // Only used by Subscriptions

    bool push(const Message<U> &item);

    void removeSubscriber(const std::string &subscriptionName);

private:
    std::string _name;
    moodycamel::BlockingConcurrentQueue<Message<U>> _queue;
    std::unordered_map<std::string, std::shared_ptr<ASubscription<T, U>>> _subscribers;
};

#include "Topic.tpp"

#endif //APP_TOPIC_HPP
