//
// Created by arzad on 05/05/2022.
//

#ifndef WORLD_DESERIALIZE_HPP
#define WORLD_DESERIALIZE_HPP

#include <map>
#include "protocol/Event.hpp"
#include "protocol/world/Types.hpp"
#include "LoadChunk.hpp"

static const std::map<EventType, WorldEvent(*)(const Event::RawEvent&)> WorldEventsDeserializer = {
        {static_cast<EventType>(WorldEventType::LOAD_CHUNK), LoadChunk::deserialize},
        {static_cast<EventType>(WorldEventType::UNLOAD_CHUNK), LoadChunk::deserialize},
};

#endif //WORLD_DESERIALIZE_HPP
