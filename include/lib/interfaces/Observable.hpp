//
// Created by arzad on 23/02/2022.
//

#ifndef APP_OBSERVABLE_HPP
#define APP_OBSERVABLE_HPP

#include <set>
#include "Observer.hpp"

template <typename T>
class Observable {
public:
    virtual void addObserver(Observer<T> *observer);
    virtual void removeObserver(Observer<T> *observer);

protected:
    virtual void notifyObservers(T);

private:
    std::set<Observer<T> *> observers;
};

template<typename T>
void Observable<T>::addObserver(Observer<T> *observer) {
    this->observers.insert(observer);
}

template<typename T>
void Observable<T>::removeObserver(Observer<T> *observer) {
    this->observers.erase(observer);
}

template<typename T>
void Observable<T>::notifyObservers(T arg) {
    for (auto observer : this->observers) {
        observer->update(arg);
    }
}

#endif //APP_OBSERVABLE_HPP
