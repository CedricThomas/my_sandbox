//
// Created by arzad on 01/05/2022.
//

#ifndef GAME_EVENTS_HPP
#define GAME_EVENTS_HPP

#include <variant>
#include <string>
#include <memory>
#include "protocol/Event.hpp"

#define LOCAL_GAME_EVENT_SUBSCRIPTION "local-game-subscription"
#define REMOTE_GAME_EVENT_SUBSCRIPTION "remote-game-subscription"

std::string createRemoteGameSubscription(unsigned int id);

using GameEvent = std::shared_ptr<Event>;

#endif //APP_GAME_EVENTS_CPP
