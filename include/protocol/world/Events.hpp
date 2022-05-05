//
// Created by arzad on 01/05/2022.
//

#ifndef WORLD_EVENTS_HPP
#define WORLD_EVENTS_HPP

#include "protocol/Event.hpp"

#define WORLD_EVENT_TOPIC "world-topic"

using WorldEvent = std::shared_ptr<Event>;

#endif // WORLD_EVENTS_HPP
