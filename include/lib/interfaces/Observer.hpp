//
// Created by arzad on 23/02/2022.
//

#ifndef APP_OBSERVER_HPP
#define APP_OBSERVER_HPP

template <typename T>
class Observer {
public:
    virtual void update(T) = 0;
};

#endif //APP_OBSERVER_HPP
