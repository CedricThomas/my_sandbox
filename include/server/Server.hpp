//
// Created by arzad on 23/02/2022.
//

#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP

#include "lib/interfaces/Observable.hpp"

class Server: public Observable<int>, public Observable<float> {
public:
    void start();
};


#endif //APP_SERVER_HPP
