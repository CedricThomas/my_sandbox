//
// Created by arzad on 05/05/2022.
//

#include <cstring>
#include "protocol/game/Leave.hpp"
#include "protocol/game/Types.hpp"
#include "protocol/game/Events.hpp"

Event::RawEvent Leave::serialize() {
    Event::RawEvent event(0, static_cast<unsigned int>(GameEventType::LEAVE));
    return event;
}

void Leave::load(const Event::RawEvent &event) {
}

EventType Leave::getType() const {
    return static_cast<EventType>(GameEventType::LEAVE);
}

GameEvent Leave::deserialize(const Event::RawEvent &rawEvent) {
    auto *event = new Leave();
    event->load(rawEvent);
    return std::shared_ptr<Event>(event);
}
