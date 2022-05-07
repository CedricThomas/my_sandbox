//
// Created by arzad on 07/05/2022.
//

#include "Topic.hpp"

template<typename T, typename U>
const std::string &ASubscription<T, U>::getName() const {
    return _name;
}

template<typename T, typename U>
const std::shared_ptr<Topic<T, U>> &ASubscription<T, U>::getTopic() const {
    return _topic;
}

template<typename T, typename U>
bool ASubscription<T, U>::pushToTopic(const U &item) {
    return _topic->push(Message<U>{
            _name,
            item
    });
}
