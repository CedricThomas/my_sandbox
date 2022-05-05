//
// Created by arzad on 03/05/2022.
//

#ifndef APP_ASUBSCRIPTION_HPP
#define APP_ASUBSCRIPTION_HPP

#include <string>
#include <memory>
#include "lib/containers/concurrentqueue.h"

template<typename T, typename U>
class Topic;

template<typename T>
struct Message {
    std::string origin;
    T data;
};

template<typename T, typename U>
class ASubscription {
public:
    explicit ASubscription(std::string name, Topic<T, U> *topic): _name(std::move(name)), _topic(topic) {}

    const std::string &getName() const {
        return _name;
    }

    const std::shared_ptr<Topic<T, U>> &getTopic() const {
        return _topic;
    }

    bool pushToTopic(const U &item) {
         return _topic->push(Message{
             _name,
             item
         });
    }

    virtual bool tryPull(T& item) = 0;

    // Only use by the topic

    virtual bool push(const T& item) = 0;

protected:
    std::string _name;
    std::shared_ptr<Topic<T, U>> _topic;
};

#endif //APP_ASUBSCRIPTION_HPP
