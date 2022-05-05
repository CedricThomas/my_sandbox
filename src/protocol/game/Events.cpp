//
// Created by arzad on 05/05/2022.
//
#include "protocol/game/Events.hpp"

std::string createRemoteGameSubscription(unsigned int id) {
    return std::string(std::string(REMOTE_GAME_EVENT_SUBSCRIPTION) + "-" + std::to_string(id));
}
