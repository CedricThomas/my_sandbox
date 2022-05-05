//
// Created by arzad on 04/05/2022.
//

#ifndef WORLD_TYPES_HPP
#define WORLD_TYPES_HPP

#include "protocol/Event.hpp"

enum class WorldEventType : EventType {
    LOAD_CHUNK = 0,
    UNLOAD_CHUNK = 1
};

#endif //WORLD_TYPES_HPP
