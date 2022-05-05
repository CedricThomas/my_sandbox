//
// Created by arzad on 23/02/2022.
//

#ifndef APP_SERVER_HPP
#define APP_SERVER_HPP

#include <memory>
#include "lib/enet.h"
#include "protocol/world/Events.hpp"
#include "protocol/game/Events.hpp"
#include "lib/broker/Topic.hpp"

#define MAX_CLIENTS 32

class Server {
public:
    Server(std::shared_ptr<Topic<WorldEvent, GameEvent>> worldTopic, int port);
    void start();

private:
    std::shared_ptr<Topic<WorldEvent, GameEvent>> _worldTopic;
    ENetHost *_host;
};


#endif //APP_SERVER_HPP
