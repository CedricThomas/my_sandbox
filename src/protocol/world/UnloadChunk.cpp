//
// Created by arzad on 04/05/2022.
//
#include <cstring>
#include "protocol/world/UnloadChunk.hpp"
#include "protocol/world/Types.hpp"

UnloadChunk::UnloadChunk(glm::vec3 position) : position(position) {}

Event::RawEvent UnloadChunk::serialize() {
    Event::RawEvent event(sizeof(position), static_cast<unsigned int>(WorldEventType::UNLOAD_CHUNK));
    auto eventData = event.getPayload();
    std::memcpy(eventData, &position, sizeof(position));
    return event;
}

void UnloadChunk::load(const Event::RawEvent &event) {
    auto eventData = event.getPayload();
    std::memcpy(&position, eventData, sizeof(position));
}

EventType UnloadChunk::getType() const {
    return static_cast<EventType>(WorldEventType::UNLOAD_CHUNK);
}

WorldEvent UnloadChunk::deserialize(const Event::RawEvent &rawEvent) {
    auto *event = new UnloadChunk();
    event->load(rawEvent);
    return std::shared_ptr<Event>(event);
}
