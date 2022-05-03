//
// Created by arzad on 01/05/2022.
//

#ifndef APP_MESSAGEBROKER_HPP
#define APP_MESSAGEBROKER_HPP

#include "Topic.hpp"

template<typename T, typename U>
class MessageBroker {
public:
    MessageBroker() = default;

    std::shared_ptr<Topic<T, U>> createTopic(const std::string &name) {
        auto topic = std::make_shared<Topic<T, U>>(name);
        _topics[name] = topic;
        return topic;
    }

    std::shared_ptr<ASubscription<T, U>> createAsyncSubscription(const std::string &topicName, const std::string &subscriptionName) {
        return _topics[topicName]->createAsyncSubscribe(subscriptionName);
    }

    std::shared_ptr<ASubscription<T, U>> createSyncSubscription(const std::string &topicName, const std::string &subscriptionName, const SyncSubscriptionCallback<U> &callback) {
        return _topics[topicName]->createSyncSubscribe(subscriptionName, callback);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Topic<T, U>>> _topics;
};


#endif //APP_MESSAGEBROKER_HPP
