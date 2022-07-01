
#include "AsyncSubscription.hpp"
#include "SyncSubscription.hpp"
#include "Topic.hpp"


template<typename T, typename U>
std::shared_ptr<AsyncSubscription<T, U>> Topic<T, U>::createAsyncSubscribe(const std::string &subscriptionName) {
    auto subscription = std::make_shared<AsyncSubscription<T, U>>(subscriptionName, this);
    _subscribers[subscriptionName] = subscription;
    return subscription;
}

template<typename T, typename U>
void Topic<T, U>::removeSubscriber(const std::string &subscriptionName) {
    _subscribers.erase(subscriptionName);
}

template<typename T, typename U>
bool Topic<T, U>::push(const Message<U> &item) {
    return _queue.enqueue(item);
}

template<typename T, typename U>
void Topic<T, U>::publishToSubcriber(const std::string &subscriptionName, const T &data) {
    _subscribers[subscriptionName]->push(data);
}

template<typename T, typename U>
void Topic<T, U>::publishToSubcribers(const T &data) {
    for (auto &subscriber : _subscribers) {
        subscriber.second->push(data);
    }
}

template<typename T, typename U>
void Topic<T, U>::pull(Message<U> &item) {
    return _queue.wait_dequeue(item);
}

template<typename T, typename U>
bool Topic<T, U>::tryPull(Message<U> &item) {
    return _queue.try_dequeue(item);
}

template<typename T, typename U>
std::shared_ptr<SyncSubscription<T, U>>
Topic<T, U>::createSyncSubscribe(const std::string &subscriptionName, const SyncSubscriptionCallback<T> &callback) {
    auto subscription = std::make_shared<SyncSubscription<T, U>>(subscriptionName, callback, this);
    _subscribers[subscriptionName] = subscription;
    return subscription;
}

template<typename T, typename U>
const std::string &Topic<T, U>::getName() const {
    return _name;
}

template<typename T, typename U>
void Topic<T, U>::publishToOtherSubcribers(const std::string &subscriptionName, const T &data) {
    for (auto &subscriber : _subscribers) {
        if (subscriber.first != subscriptionName) {
            subscriber.second->push(data);
        }
    }
}
