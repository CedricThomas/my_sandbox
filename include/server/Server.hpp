//
// Created by arzad on 23/02/2022.
//

#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP

#include <memory>
#include "lib/enet.h"
#include "world/Events.hpp"
#include "application/game/Events.hpp"
#include "lib/broker/AsyncSubscription.hpp"

#define MAX_CLIENTS 32

class Server {
public:
    Server(std::shared_ptr<ASubscription<WorldEvent, GameEvent>> subscription, int port);
    void start();

private:
    std::shared_ptr<ASubscription<WorldEvent, GameEvent>> _subscription;
    ENetHost *_host;
};


#endif //APP_SERVER_HPP
