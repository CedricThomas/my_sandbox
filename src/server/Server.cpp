//
// Created by arzad on 23/02/2022.
//

#include "server/Server.hpp"

void Server::start() {
    Observable<int>::notifyObservers(12);
    Observable<float>::notifyObservers(12.0);
}
