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

    std::shared_ptr<Subscription<T, U>> subscribeToTopic(const std::string &topicName, const std::string &subscriptionName) {
        return _topics[topicName]->subscribeAs(subscriptionName);
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Topic<T, U>>> _topics;
};


#endif //APP_MESSAGEBROKER_HPP
