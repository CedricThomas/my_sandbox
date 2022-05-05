//
// Created by arzad on 01/05/2022.
//

#ifndef GAME_EVENTS_HPP
#define GAME_EVENTS_HPP

#include <variant>

#define LOCAL_GAME_EVENT_SUBSCRIPTION "local-game-subscription"
#define REMOTE_GAME_EVENT_SUBSCRIPTION "remote-game-subscription"


using GameEvent = std::variant<int, float>;

#endif //APP_GAME_EVENTS_CPP
