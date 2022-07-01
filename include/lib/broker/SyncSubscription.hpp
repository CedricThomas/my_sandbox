//
// Created by arzad on 01/05/2022.
//

#ifndef APP_SYNCSUBSCRIPTION_HPP
#define APP_SYNCSUBSCRIPTION_HPP

#include <string>
#include <memory>
#include <utility>
#include <functional>
#include "lib/containers/concurrentqueue.h"

template<typename T>
using SyncSubscriptionCallback = std::function<bool(const T &item)>;

template<typename T, typename U>
class SyncSubscription : public ASubscription<T, U> {
public:
    SyncSubscription(const std::string &name, const SyncSubscriptionCallback<T> &callback, Topic<T, U> *topic)
            : ASubscription<T, U>(name, topic),
              _callback(callback) {}

    bool tryPull(T &item) {
        throw std::runtime_error("Can pull from a sync subscription");
    }

    void pull(T &item) {
        throw std::runtime_error("Can pull from a sync subscription");
    }

    // Only used by the topic

    bool push(const T &item) override {
        return _callback(item);
    }

private:
    SyncSubscriptionCallback<T> _callback;
};


#endif //APP_ASYNCSUBSCRIPTION_HPP
