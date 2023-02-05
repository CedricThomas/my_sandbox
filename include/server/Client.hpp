//
// Created by arzad on 01/05/2022.
//

#ifndef APP_CLIENT_HPP
#define APP_CLIENT_HPP

#include <memory>
#include "lib/enet.h"
#include "lib/broker/Topic.hpp"
#include "protocol/world/Events.hpp"
#include "protocol/game/Events.hpp"

class Client {
public:
    Client(
            std::shared_ptr<Topic<WorldEvent, GameEvent>> worldTopic,
            const std::string &address,
            int port
    );
    virtual ~Client();
    void listenServer();
    void listenGame();
    void disconnect();

private:
    std::shared_ptr<Topic<WorldEvent, GameEvent>> _worldTopic;
    ENetHost *_host;
    ENetPeer *_peer;
    bool _disconnected;
};


#endif //APP_CLIENT_HPP
