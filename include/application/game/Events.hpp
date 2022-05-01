//
// Created by arzad on 01/05/2022.
//

#ifndef APP_EVENTS_HPP
#define APP_EVENTS_HPP

#include <variant>

#define LOCAL_GAME_EVENT_TOPIC "local-game-topic"
#define REMOTE_GAME_EVENT_TOPIC "remote-game-topic"

using GameEvent = std::variant<int, float>;

#endif //APP_EVENTS_HPP
