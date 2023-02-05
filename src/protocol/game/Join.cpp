//
// Created by arzad on 05/05/2022.
//

#include <cstring>
#include "protocol/game/Join.hpp"
#include "protocol/game/Types.hpp"
#include "protocol/game/Events.hpp"

Join::Join(const glm::vec3 &position) : position(position) {}

Event::RawEvent Join::serialize() {
    Event::RawEvent event(sizeof(position), static_cast<unsigned int>(GameEventType::JOIN));
    auto eventData = event.getPayload();
    std::memcpy(eventData, &position, sizeof(position));
    return event;
}

void Join::load(const Event::RawEvent &event) {
    auto eventData = event.getPayload();
    std::memcpy(&position, eventData, sizeof(position));
}

EventType Join::getType() const {
    return static_cast<EventType>(GameEventType::JOIN);
}

GameEvent Join::deserialize(const Event::RawEvent &rawEvent) {
    auto *event = new Join();
    event->load(rawEvent);
    return std::shared_ptr<Event>(event);
}
