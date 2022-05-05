//
// Created by arzad on 05/05/2022.
//

#include <cstring>
#include "protocol/game/Move.hpp"
#include "protocol/game/Types.hpp"
#include "protocol/game/Events.hpp"

Event::RawEvent Move::serialize() {
    Event::RawEvent event(static_cast<unsigned int>(GameEventType::MOVE), sizeof(position));
    auto eventData = event.getData();
    std::memcpy(eventData, &position, sizeof(position));
    return event;
}

void Move::load(const Event::RawEvent &event) {
    auto eventData = event.getData();
    std::memcpy(&position, eventData, sizeof(position));
}

EventType Move::getType() const {
    return static_cast<EventType>(GameEventType::MOVE);
}

GameEvent Move::deserialize(const Event::RawEvent &rawEvent) {
    auto *event = new Move();
    event->load(rawEvent);
    return std::shared_ptr<Event>(event);
}
