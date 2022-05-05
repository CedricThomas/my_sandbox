//
// Created by arzad on 05/05/2022.
//

#ifndef GAME_DESERIALIZE_HPP
#define GAME_DESERIALIZE_HPP

#include <map>
#include "protocol/Event.hpp"
#include "protocol/game/Types.hpp"
#include "Move.hpp"

static const std::map<EventType, GameEvent(*)(const Event::RawEvent&)> GameEventsDeserializer = {
        {static_cast<EventType>(GameEventType::MOVE), Move::deserialize},
};

#endif //GAME_DESERIALIZE_HPP
