//
// Created by arzad on 04/05/2022.
//

#include <cstring>
#include "protocol/world/UnloadChunk.hpp"
#include "protocol/world/Types.hpp"

Event::RawEvent UnloadChunk::serialize() {
    Event::RawEvent event(static_cast<unsigned int>(WorldEventType::UNLOAD_CHUNK), sizeof(position));
    auto eventData = event.getData();
    std::memcpy(eventData, &position, sizeof(position));
    return event;
}

void UnloadChunk::load(const Event::RawEvent &event) {
    auto eventData = event.getData();
    std::memcpy(&position, eventData, sizeof(position));
}

EventType UnloadChunk::getType() const {
    return static_cast<EventType>(WorldEventType::UNLOAD_CHUNK);
}
