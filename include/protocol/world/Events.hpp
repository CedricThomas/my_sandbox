//
// Created by arzad on 01/05/2022.
//

#ifndef WORLD_EVENTS_HPP
#define WORLD_EVENTS_HPP

#include <variant>
#include "LoadChunk.hpp"
#include "UnloadChunk.hpp"

#define WORLD_EVENT_TOPIC "world-topic"

using WorldEvent = std::variant<LoadChunk, UnloadChunk>;

#endif // WORLD_EVENTS_HPP
